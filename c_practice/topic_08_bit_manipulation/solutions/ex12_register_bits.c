/*
 * ex12_register_bits.c — Configure multiple bits in control register
 * Key concept: combine set/clear/field ops for peripheral init.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

#define USART_CR1_UE   BIT(0)
#define USART_CR1_RE   BIT(2)
#define USART_CR1_TE   BIT(3)

int main(void)
{
    uint32_t cr1 = 0UL;

    cr1 |= USART_CR1_UE;   /* Enable USART */
    cr1 |= USART_CR1_TE;   /* Transmitter enable */
    cr1 |= USART_CR1_RE;   /* Receiver enable */

    printf("USART CR1 = 0x%08lX\n", (unsigned long)cr1);
    printf("  UE=%lu TE=%lu RE=%lu\n",
           (unsigned long)((cr1 & USART_CR1_UE) != 0UL),
           (unsigned long)((cr1 & USART_CR1_TE) != 0UL),
           (unsigned long)((cr1 & USART_CR1_RE) != 0UL));

    return 0;
}
