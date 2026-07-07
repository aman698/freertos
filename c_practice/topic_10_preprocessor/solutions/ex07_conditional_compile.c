/*
 * ex07_conditional_compile.c — #if selects chip-specific values
 * Key concept: compare numeric macros for multi-target builds.
 */
#include <stdint.h>
#include <stdio.h>

#define STM32F411 1
#define STM32F103 0

#if STM32F411
#define FLASH_SIZE_KB 512U
#define MAX_FREQ_MHZ  100U
#elif STM32F103
#define FLASH_SIZE_KB 64U
#define MAX_FREQ_MHZ  72U
#else
#error "Unknown target MCU"
#endif

int main(void)
{
    printf("Flash=%u KB, max freq=%u MHz\n", FLASH_SIZE_KB, MAX_FREQ_MHZ);
    return 0;
}
