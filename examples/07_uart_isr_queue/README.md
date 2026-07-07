# Example 07 — UART ISR → Queue (Optional Day 9 Challenge)

**Day:** 9 (advanced optional)  
**Not a full standalone project** — extension after Example 02.

---

## Theory

UART RX interrupt fires per byte (or per IDLE line). ISR should:
1. Read byte from `DR` register
2. `xQueueSendFromISR` to parser task
3. `portYIELD_FROM_ISR`

Parser task:
- `xQueueReceive` bytes
- Build line buffer
- Echo or process command

**Never** call `printf` or `HAL_UART_Receive` (blocking) in ISR.

---

## CubeMX setup

- USART2 → **NVIC USART2 global interrupt** enabled
- Or use `HAL_UART_Receive_IT(&huart2, &byte, 1)` in `main` after init

---

## Skeleton — main.c USER CODE

```c
uint8_t rxByte;
QueueHandle_t uartRxQueue;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(uartRxQueue, &rxByte, &woken);
    portYIELD_FROM_ISR(woken);
    HAL_UART_Receive_IT(&huart2, &rxByte, 1);
  }
}
```

## Skeleton — freertos.c

```c
uartRxQueue = xQueueCreate(32, sizeof(uint8_t));

void StartUartParserTask(void *argument) {
  uint8_t b;
  for (;;) {
    if (xQueueReceive(uartRxQueue, &b, portMAX_DELAY)) {
      HAL_UART_Transmit(&huart2, &b, 1, 100);  /* echo */
    }
  }
}
```

## Start RX in main USER CODE 2

```c
extern uint8_t rxByte;
HAL_UART_Receive_IT(&huart2, &rxByte, 1);
```

---

## Verify

- [ ] Type in serial terminal → characters echo back
- [ ] Flood keys rapidly → no lost chars if queue deep enough

---

## If you complete this

You have implemented the classic **ISR → queue → task** pattern twice (GPIO + UART).
