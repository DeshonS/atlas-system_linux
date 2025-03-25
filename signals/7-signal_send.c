#include "signals.h"

int main(char argc, int *argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (pidfd_send_signal())
}