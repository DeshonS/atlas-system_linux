#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
}

int handle_signal(void)
{
    if (signal(SIGINT, handle_signal) == SIG_ERR)
    {
        return (-1);
    }
    else
    {
        return (0);
    }
}