/*
 * ex09_obd2_connector_pinout.c — Print the OBD-II J1962 diagnostic connector pinout
 * Key concept: SAE J1962 fixes CAN, K/L-Line, and power pins at the same physical locations across vehicles.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    uint8_t pin;
    const char *signal;
} j1962_pin_t;

int main(void)
{
    const j1962_pin_t pins[] = {
        { 4U,  "Chassis Ground" },
        { 5U,  "Signal Ground" },
        { 6U,  "CAN High (J2284)" },
        { 7U,  "K-Line (ISO 9141-2 / ISO 14230)" },
        { 14U, "CAN Low (J2284)" },
        { 15U, "L-Line (ISO 9141-2, optional)" },
        { 16U, "Battery Positive (+12V)" },
    };
    size_t i;

    printf("J1962 OBD-II connector pinout:\n");
    for (i = 0U; i < sizeof(pins) / sizeof(pins[0]); i++) {
        printf("  Pin %2u : %s\n", pins[i].pin, pins[i].signal);
    }
    return 0;
}
