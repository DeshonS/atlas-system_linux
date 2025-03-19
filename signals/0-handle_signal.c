#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

int handle_signal(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}
