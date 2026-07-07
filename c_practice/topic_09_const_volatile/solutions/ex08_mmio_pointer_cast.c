/*
 * ex08_mmio_pointer_cast.c — Cast fixed address to volatile pointer
 * Key concept: CMSIS style — #define REG (*(volatile uint32_t *)addr)
 */
#include <stdint.h>
#include <stdio.h>

#define PERIPH_BASE     0x40020000UL
#define GPIOA_ODR_ADDR  (PERIPH_BASE + 0x14UL)
#define GPIOA_ODR       (*(volatile uint32_t *)GPIOA_ODR_ADDR)

int main(void)
{
    /* Simulated: use local volatile instead of real HW address on PC */
    static volatile uint32_t sim_odr = 0U;
    volatile uint32_t *GPIOA_ODR_SIM = &sim_odr;

    *GPIOA_ODR_SIM = 0x00000020UL;
    printf("ODR via MMIO pointer = 0x%08lX\n", (unsigned long)(*GPIOA_ODR_SIM));
    printf("(Real target: GPIOA_ODR at 0x%08lX)\n", (unsigned long)GPIOA_ODR_ADDR);
    return 0;
}
