#include "signals.h"

/**
 * handler - custom handler
 * @signum: sender process ID
 */

void handler(int signum)
{
	pid_t sent = getpid();
	(void)signum;
	printf("^\nSIGQUIT sent by %d\n", sent);
}

/**
 * trace_signal_sender - traces signal to source
 * Return: 0 on success, -1 on error
 */

int trace_signal_sender(void)
{
	if (signal(SIGQUIT, handler) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}
