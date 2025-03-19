#include "signals.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	switch(atoi(argv[1]))
	{
		case 1:  printf("1: Hangup\n"); break;
        case 2:  printf("2: Interrupt\n"); break;
        case 3:  printf("3: Quit\n"); break;
        case 9:  printf("9: Killed\n"); break;
        case 20: printf("20: Stopped\n"); break;
        default: printf("%s: Unknown signal %s\n", argv[1], argv[1]); break;
    }
    return EXIT_SUCCESS;
}