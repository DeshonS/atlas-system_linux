#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>
#include "syscalls.h" 

#define SYSCALL_MAX 548  // Adjust if your syscall list is longer

const char *get_syscall_name(long syscall_num)
{
	for (size_t i = 0; i < sizeof(syscalls_64_g) / sizeof(syscall_t); i++)
	{
		if ((long)syscalls_64_g[i].nr == syscall_num)
			return syscalls_64_g[i].name;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return 1;
	}

	pid_t child = fork();
	if (child == -1)
	{
		perror("fork");
		return 1;
	}

	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		kill(getpid(), SIGSTOP);
		execv(argv[1], &argv[1]);
		perror("execv");
		exit(1);
	}
	else
	{
		int status;
		waitpid(child, &status, 0);

		ptrace(PTRACE_SYSCALL, child, NULL, NULL);

		while (1)
		{
			waitpid(child, &status, 0);
			if (WIFEXITED(status))
				break;

			struct user_regs_struct regs;
			ptrace(PTRACE_GETREGS, child, NULL, &regs);

			const char *name = get_syscall_name(regs.orig_rax);
			if (name)
				printf("%s\n", name);
				fflush(stdout);
			else
				printf("unknown_syscall_%lld\n", regs.orig_rax);

			ptrace(PTRACE_SYSCALL, child, NULL, NULL);

			waitpid(child, &status, 0);
			if (WIFEXITED(status))
				break;
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		}
	}

	return 0;
}