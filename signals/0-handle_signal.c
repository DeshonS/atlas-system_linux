#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
}

int handle_signal(void)
{
    if (signal(SIGINT, handler) == SIG_ERR)
    {
        return (-1);
    }
    return (0);
}

int main(void)
{
    int i;

    if (handle_signal() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}