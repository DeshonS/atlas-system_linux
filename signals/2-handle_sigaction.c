#include "signals.h"

/**
 * handler - handles the output of custom SIGINT handle
 * @signum: signal number
 */

void handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - assigns custom handler to SIGINT
 * Return: 0 for success, -1 for error
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (-1);
	}
	return (0);
}
