# Example 03 — Mutex + Safe UART Printf

**Day:** 6  
**Hardware:** USART2 @ 115200 (ST-LINK virtual COM port)

---

## Theory

### Race condition without mutex
```
Task A: printf("FAST")  →  UART: F
Task B: printf("SLOW")  →  UART: A
Task A: continues        →  UART: S
Result on wire: "FSALT..." garbled
```

### Mutex rules
1. **Take** before accessing shared resource
2. **Give** after done
3. Same task must Give what it Took
4. FreeRTOS enables **priority inheritance** automatically

### Mutex vs binary semaphore
| | Mutex | Binary Semaphore |
|---|-------|------------------|
| Ownership | Yes | No |
| Use for | Protect resource | Signal event |
| Recursive | Optional | N/A |

---

## Practice — Step by Step

### 1. CubeMX
- USART2 → Mode: Asynchronous, 115200 8N1
- Regenerate

### 2. Edit `Core/Src/syscalls.c`
Paste entire `syscalls_snippet.c` into `syscalls.c` (or merge `_write` function).

### 3. Replace `freertos.c`
Copy from this folder's `freertos.c`.

### 4. Open serial terminal
- Port: ST-LINK COM (Device Manager → "STMicroelectronics Virtual COM Port")
- Baud: **115200**
- Build → Run

---

## Verify

| Check | Pass? |
|-------|-------|
| `[FAST]` every ~150 ms | |
| `[SLOW]` every ~800 ms | |
| Lines never mixed mid-string | |

### Prove mutex is needed
Comment out in `SafePrintf`:
```c
// xSemaphoreTake(uartMutex, ...);
// xSemaphoreGive(uartMutex);
```
Rebuild → garbled output → restore mutex.

---

## Modify

- Change both tasks to `osPriorityHigh` — mutex still needed
- Reduce `buf[128]` to `buf[16]` with long format string — truncated output
- Add third task printing — mutex serializes all three

---

## `SafePrintf` pattern (reuse in all projects)

```c
if (xSemaphoreTake(uartMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
    HAL_UART_Transmit(...);
    xSemaphoreGive(uartMutex);
}
```
