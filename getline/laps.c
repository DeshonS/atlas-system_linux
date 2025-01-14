#include "laps.h"

typedef struct Car {
    int id;
    int laps;
} Car;

static Car *cars = NULL;
static size_t num_cars = 0;

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
            cars[num_cars].laps = 1;
            num_cars++;
            printf("Car %d joined the race\n", id[i]);
        }
    }

    printf("Race state:\n"); //shows the current race state
    for (size_t i = 0; i < num_cars; i++) {
        printf("Car %d [%d laps]\n", cars[i].id, cars[i].laps);
    }
}