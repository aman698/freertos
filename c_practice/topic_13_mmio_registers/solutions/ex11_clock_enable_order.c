/*
 * ex11_clock_enable_order.c - Enable peripheral clock before register use.
 * Key concept: STM32 peripheral registers are unavailable until clocked.
 */
#include <stdbool.h>
#include <stdio.h>

static bool gpioa_clock_enabled;

static void rcc_enable_gpioa(void)
{
    gpioa_clock_enabled = true;
    puts("GPIOA clock enabled");
}

static void gpio_config_output(void)
{
    if (!gpioa_clock_enabled) {
        puts("error: GPIOA clock disabled");
        return;
    }
    puts("GPIOA pin configured as output");
}

int main(void)
{
    gpio_config_output();
    rcc_enable_gpioa();
    gpio_config_output();
    return 0;
}
