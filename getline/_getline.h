#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 1024

char *_getline(const int fd);

#endif