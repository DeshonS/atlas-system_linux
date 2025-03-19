#include "signals.h"

/**
 * current_handler_sigaction - returns the current handler
 * Return: current handler for SIGINT
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
	{
		return (NULL);
	}
	return (sa.sa_handler);
}
