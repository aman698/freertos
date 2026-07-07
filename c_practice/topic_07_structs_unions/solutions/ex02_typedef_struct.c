/*
 * ex02_typedef_struct.c — typedef creates alias for struct type
 * Key concept: typedef struct { ... } name_t avoids repeating 'struct'.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t pin;
    uint32_t mode;
    uint32_t speed;
} gpio_config_t;

int main(void)
{
    gpio_config_t led = { .pin = 5U, .mode = 1U, .speed = 2U };

    printf("GPIO config: pin=PA%lu mode=%lu speed=%lu\n",
           (unsigned long)led.pin,
           (unsigned long)led.mode,
           (unsigned long)led.speed);
    return 0;
}
