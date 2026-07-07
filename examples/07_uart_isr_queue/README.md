# Example 07 — UART ISR → Queue (Optional Day 9 Challenge)

**Day:** 9 (advanced optional)  
Full source is provided:

| File | Purpose |
|------|---------|
| [`freertos.c`](freertos.c) | Queue, parser task, and command handling |
| [`main_user_code.c`](main_user_code.c) | `main.c` USER CODE snippets for UART RX interrupt |

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

## Key snippet — main.c USER CODE

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

## Key snippet — freertos.c

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

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 6 (ISR)  
**Level:** L3–L5 (UART ISR + queue)

### Breakpoints
| Where | Why |
|-------|-----|
| `HAL_UART_RxCpltCallback` | Per-byte ISR |
| `xQueueSendFromISR` for `uartRxQueue` | Defer to parser |
| Parser task `xQueueReceive` | Consumer |

### Watch expressions
```
rxByte
uxQueueMessagesWaiting(uartRxQueue)
huart2.RxState
```

### Step drill
1. Type one character in serial terminal → halt in RX callback
2. **Step Over** `xQueueSendFromISR` — queue depth +1
3. **Step Over** `HAL_UART_Receive_IT` re-arm
4. **Resume** → parser task receives `rxByte`

### Advanced — flood test
Rapid typing → **Suspend** during flood → `uxQueueMessagesWaiting` near queue length → risk of drop if full.

### Theory check
**Never Step Into** `printf` from ISR — if you added one by mistake, see block time stretch (bad practice demo).

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| One ISR hit per byte | |
| Parser `rxByte` matches typed key | |
