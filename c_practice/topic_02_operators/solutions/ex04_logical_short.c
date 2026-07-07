/*
 * ex04_logical_short.c — Short-circuit evaluation of && and ||
 * Key concept: second operand not evaluated if result is already determined.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static int check_sensor(void)
{
    printf("  [check_sensor called]\n");
    return 1; /* OK */
}

static int check_bus(void)
{
    printf("  [check_bus called]\n");
    return 0; /* fault */
}

int main(void)
{
    bool bus_ok = false;

    printf("Test A: bus_ok && check_sensor()\n");
    if (bus_ok && check_sensor()) {
        printf("  both OK\n");
    } else {
        printf("  skipped sensor check (short-circuit)\n");
    }

    printf("\nTest B: bus_ok || check_bus()\n");
    bus_ok = true;
    if (bus_ok || check_bus()) {
        printf("  bus already OK — check_bus skipped\n");
    }

    return 0;
}
