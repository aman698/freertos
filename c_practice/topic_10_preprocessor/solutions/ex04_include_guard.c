/*
 * ex04_include_guard.c — Include guard prevents double inclusion
 * Key concept: #ifndef/#define/#endif wraps header contents.
 */
#include <stdint.h>
#include <stdio.h>
#include "ex04_demo_config.h"
#include "ex04_demo_config.h"  /* second include — guarded, no redefinition error */

int main(void)
{
    printf("Board: %s, LED pin: %u\n", BOARD_NAME, LED_PIN);
    return 0;
}
