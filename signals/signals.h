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
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
void trace_handler(int sig, siginfo_t *info, void *context);

#endif
