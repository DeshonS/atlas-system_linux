#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include "syscalls.h"

static const char *get_syscall_name(long syscall_nr) {
#if defined(__x86_64__)
    size_t n = sizeof(syscalls_64_g) / sizeof(syscalls_64_g[0]);
    if (syscall_nr >= 0 && (size_t)syscall_nr < n)
        return syscalls_64_g[syscall_nr].name;
#elif defined(__i386__)
    size_t n = sizeof(syscalls_32_g) / sizeof(syscalls_32_g[0]);
    if (syscall_nr >= 0 && (size_t)syscall_nr < n)
        return syscalls_32_g[syscall_nr].name;
#else
#error Unsupported architecture
#endif
    return "unknown";
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return 1;
    }

    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        execv(argv[1], &argv[1]);
        perror("execv");
        exit(1);
    } else {
        int status;
        struct user_regs_struct regs;
        int in_syscall = 0;

        waitpid(child, &status, 0);
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);

        while (1) {
            waitpid(child, &status, 0);
            if (WIFEXITED(status))
                break;

            ptrace(PTRACE_GETREGS, child, NULL, &regs);

            if (in_syscall == 0) {
                in_syscall = 1;
                const char *name = get_syscall_name(regs.orig_rax);
                printf("%s", name);
                fflush(stdout);
            } else {
                in_syscall = 0;
                if (regs.orig_rax == SYS_exit_group)
                    printf(" = ?\n");
                else
                    printf(" = %#llx\n", (long long)regs.rax);
            }

            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }

    return 0;
}
