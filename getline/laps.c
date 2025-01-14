#include "laps.h"

typedef struct Car {
    int id;
    int laps;
} Car;

static Car *cars = NULL;
static size_t num_cars = 0;

int carcmp(const void *a, const void *b)
{
    const Car *car_a = (const Car *)a;
    const Car *car_b = (const Car *)b;
    return car_a->id - car_b->id;
}

void race_state(int *id, size_t size) {
    if (size == 0) { //frees all memory and resets the race
        free(cars);
        cars = NULL;
        num_cars = 0;
        return;
    }

    for (size_t i = 0; i < size; i++) { //car laps
        int car_exists = 0;
        for (size_t j = 0; j < num_cars; j++) {
            if (cars[j].id == id[i]) {
                cars[j].laps++;
                car_exists = 1;
                break;
            }
        }

        if (!car_exists) { //adds new car to the race
            cars = realloc(cars, (num_cars + 1) * sizeof(Car));
            cars[num_cars].id = id[i];
            cars[num_cars].laps = 0;
            num_cars++;
            printf("Car %d joined the race\n", id[i]);
        }
    }

    qsort(cars, num_cars, sizeof(Car), carcmp); //sorting cars by ID for output

    printf("Race state:\n"); //shows the current race state
    for (size_t i = 0; i < num_cars; i++) {
        printf("Car %d [%d laps]\n", cars[i].id, cars[i].laps);
    }
}