/*
 * ex07_uart_baud_divisor.c — Compute an STM32-style USART BRR divisor from clock and baud rate
 * Key concept: BRR packs an integer mantissa and a 4-bit fraction of the clock/baud ratio.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t mantissa;
    uint8_t fraction;
} usart_brr_t;

static usart_brr_t usart_compute_brr(uint32_t pclk_hz, uint32_t baud_rate)
{
    usart_brr_t brr;
    /* USARTDIV = pclk / (16 * baud); scale by 16 first so the fraction survives as an integer. */
    uint32_t scaled_div = (pclk_hz * 16U + baud_rate / 2U) / baud_rate;

    brr.mantissa = (uint16_t)(scaled_div / 16U);
    brr.fraction = (uint8_t)(scaled_div % 16U);
    return brr;
}

static uint16_t usart_pack_brr_register(usart_brr_t brr)
{
    return (uint16_t)((uint16_t)(brr.mantissa << 4U) | (brr.fraction & 0x0FU));
}

int main(void)
{
    uint32_t pclk_hz = 42000000U; /* APB1 clock on e.g. STM32F4 */
    uint32_t baud_rate = 115200U;
    usart_brr_t brr = usart_compute_brr(pclk_hz, baud_rate);
    uint16_t reg = usart_pack_brr_register(brr);

    printf("PCLK=%lu Hz, baud=%lu -> mantissa=%u fraction=%u\n",
           (unsigned long)pclk_hz, (unsigned long)baud_rate, brr.mantissa, brr.fraction);
    printf("BRR register value = 0x%04X\n", reg);
    return 0;
}
