/*
 * ex12_uart_register_init.c - Simulate UART register initialization.
 * Key concept: peripheral init writes a small set of control registers.
 */
#include <stdint.h>
#include <stdio.h>

#define USART_CR1_UE (1UL << 0U)
#define USART_CR1_RE (1UL << 2U)
#define USART_CR1_TE (1UL << 3U)

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t BRR;
    volatile uint32_t ISR;
} USART_TypeDef;

int main(void)
{
    USART_TypeDef usart2 = {0};
    usart2.BRR = 0x0683U;
    usart2.CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;

    printf("USART BRR=0x%04lX CR1=0x%08lX\n",
           (unsigned long)usart2.BRR, (unsigned long)usart2.CR1);
    return 0;
}
