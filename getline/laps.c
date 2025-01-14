#include "laps.h"

static Car *cars;
static size_t num_cars;

/**
 * sort_cars - sorts cars in order based on their ID
 */

void sort_cars(void)
{
	for (size_t i = 0; i < num_cars - 1; i++)
	{
		for (size_t j = 0; j < num_cars - i - 1; j++)
		{
			if (cars[j].id > cars[j + 1].id)
			{
				Car temp = cars[j];

				cars[j] = cars[j + 1];
				cars[j + 1] = temp;
			}
		}
	}
}

/**
 * race_state - updates the race using vehicle IDs and number of cars
 * @id: Vehicle IDs
 * @size: number of racers in the race, if 0, frees all memory
 */

void race_state(int *id, size_t size)
{
	if (size == 0)
	{
		free(cars);
		cars = NULL;
		num_cars = 0;
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		int car_exists = 0;

		for (size_t j = 0; j < num_cars; j++)
		{
			if (cars[j].id == id[i])
			{
				cars[j].laps++;
				car_exists = 1;
				break;
			}
		}

		if (!car_exists)
		{
			cars = realloc(cars, (num_cars + 1) * sizeof(Car));
			cars[num_cars].id = id[i];
			cars[num_cars].laps = 0;
			num_cars++;
			printf("Car %d joined the race\n", id[i]);
		}
	}

	sort_cars();

	printf("Race state:\n");
	for (size_t i = 0; i < num_cars; i++)
	{
		printf("Car %d [%d laps]\n", cars[i].id, cars[i].laps);
	}
}
