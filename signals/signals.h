#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int handle_signal(void);
void handler(int signum);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);

#endif
