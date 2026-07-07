/*
 * ex02_linear_search.c - Find a record by ID.
 * Key concept: linear search is fine for small tables.
 */
#include <stdio.h>

typedef struct {
    unsigned id;
    const char *name;
} Sensor_t;

int main(void)
{
    const Sensor_t sensors[] = {{1U, "temp"}, {2U, "pressure"}, {3U, "humidity"}};
    unsigned wanted = 2U;

    for (size_t i = 0U; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
        if (sensors[i].id == wanted) {
            printf("found %s\n", sensors[i].name);
        }
    }
    return 0;
}
