/* Example 09 — main_user_code.c */
#include "cmsis_os.h"
extern void Button_ISR_NotifyFromISR(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
    Button_ISR_NotifyFromISR();
  }
}
