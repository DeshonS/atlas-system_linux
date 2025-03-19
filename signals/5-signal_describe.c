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
		case 4:  printf("4: Illegal instruction\n"); break;
		case 5:  printf("5: Trace/breakpoint trap\n"); break;
		case 6:  printf("6: Aborted\n"); break;
		case 7:  printf("7: Bus error\n"); break;
		case 8:  printf("8: Floating point exception\n"); break;
        case 9:  printf("9: Killed\n"); break;
		case 10: printf("10: User defined signal 1\n"); break;
        default: printf("%s: Unknown signal %s\n", argv[1], argv[1]); break;
    }
    return EXIT_SUCCESS;
}