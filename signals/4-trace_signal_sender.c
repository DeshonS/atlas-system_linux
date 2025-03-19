#include "signals.h"

/**
 * trace_handler - custom handler
 * @sig: signal number
 * @info: pointer to siginfo_t
 * @context: pointer to context
 * @signum: sender process ID
 */

void trace_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	printf("^\nSIGQUIT sent by %d\n", info->si_pid);
}

/**
 * trace_signal_sender - traces signal to source
 * Return: 0 on success, -1 on error
 */

int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = trace_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		return (-1);
	}
	return (0);
}
