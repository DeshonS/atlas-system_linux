<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
=======
#include "signals.h"

/**
 * handler - custom function for SIGINT handling
 * @signum: signal number
 * return: void
 */

void handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - sets handle for SIGINT signal
 * Return: 0 for success, -1 for failure
 */

int handle_signal(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}
>>>>>>> d5654ca4f03611074a5ddf116437b4054fb6660a
