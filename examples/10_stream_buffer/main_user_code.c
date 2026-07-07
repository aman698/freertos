/* Example 10 — main_user_code.c */
#include "cmsis_os.h"

extern void Uart_CLI_StartRx(void);

void main_user_after_uart_init(void) {
  Uart_CLI_StartRx();
}

/* In main() USER CODE 2 after MX_USART2_UART_Init(): */
/* Uart_CLI_StartRx(); */

/* Move HAL_UART_RxCpltCallback to main.c if linker duplicate — keep one copy */
