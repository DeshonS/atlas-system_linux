#include "signals.h"

/**
 * current_handler_signal - gets the current SIGINT handler
 * Return: Pointer to the handler function or NULL if fail
 */

 void (*current_handler_signal(void))(int)
 {
    void (*handler)(int);

    handler = signal(SIGINT, SIG_IGN);
    if (handler == SIG_ERR)
    {
        return (NULL);
    }
    signal(SIGINT, handler);
    return (handler);
 }