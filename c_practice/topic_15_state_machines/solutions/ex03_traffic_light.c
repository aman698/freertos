/*
 * ex03_traffic_light.c - Timed traffic light state cycle.
 * Key concept: next state depends on current state.
 */
#include <stdio.h>

typedef enum {
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_YELLOW
} Light_t;

static Light_t next_light(Light_t state)
{
    switch (state) {
    case LIGHT_RED: return LIGHT_GREEN;
    case LIGHT_GREEN: return LIGHT_YELLOW;
    case LIGHT_YELLOW: return LIGHT_RED;
    default: return LIGHT_RED;
    }
}

int main(void)
{
    Light_t state = LIGHT_RED;
    const char *names[] = {"RED", "GREEN", "YELLOW"};
    for (int i = 0; i < 5; i++) {
        puts(names[state]);
        state = next_light(state);
    }
    return 0;
}
