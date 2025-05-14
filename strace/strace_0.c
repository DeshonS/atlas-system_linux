#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
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
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
            perror("ptrace TRACEME");
            exit(1);
        }
        kill(getpid(), SIGSTOP);
        execv(argv[1], &argv[1]);
        perror("execv");
        exit(1);
    } else {
        int status;
        int in_syscall = 0;
        struct user_regs_struct regs;

        waitpid(child, &status, 0);
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);

		waitpid(child, &status, 0);
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);

        while (1) {
            waitpid(child, &status, 0);
            if (WIFEXITED(status))
                break;

            ptrace(PTRACE_GETREGS, child, NULL, &regs);

            if (in_syscall == 0) {
#if defined(__x86_64__)
				fprintf(stderr, "%llu\n", regs.orig_rax);
#elif defined(__i386__)
				fprintf(stderr, "%lu\n", regs.orig_eax);
#else
#error Unsupported architecture
#endif
                in_syscall = 1;
            } else {
                in_syscall = 0;
            }

            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }

    return 0;
}