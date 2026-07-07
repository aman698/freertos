/*
 * ex05_register_struct_overlay.c - Model a peripheral register map.
 * Key concept: vendor headers use structs for MMIO layout.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
} GPIO_TypeDef;

int main(void)
{
    GPIO_TypeDef gpioa = {0};
    gpioa.MODER = 0x400U;
    gpioa.ODR = 0x20U;
    printf("MODER=0x%08lX ODR=0x%08lX\n",
           (unsigned long)gpioa.MODER, (unsigned long)gpioa.ODR);
    return 0;
}
