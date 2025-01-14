#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Car
{
	int id;
	int laps;
} Car;

void race_state(int *id, size_t size);

#endif
