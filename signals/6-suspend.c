#include "signals.h"

/**
 * handler - custom handler
 * @signum: signal number
 */

void handler(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal received\n");
	raise(SIGQUIT);
}

/**
 * main - entry point
 * Return: 0 for success, 1 for error
 */

int main(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		return (1);
	}
	pause();
	return (0);
}
