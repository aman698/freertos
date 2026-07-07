# Example 08 — Event Groups

**Day 11** | **Theory:** [`THEORY_REFERENCE.md` §6](../../THEORY_REFERENCE.md)

---

## Theory (deep)

### What problem do event groups solve?
You have **multiple independent init tasks** (sensor, comm, storage). A main task must wait until **all** are ready before starting the control loop.

Without event groups:
```c
// BAD: polling wastes CPU
while (!sensor_ok || !comm_ok) { osDelay(10); }
```

With event groups:
```c
bits = xEventGroupWaitBits(eg, ALL_BITS, pdTRUE, pdTRUE, portMAX_DELAY);
```

### Parameters of `xEventGroupWaitBits`
| Param | Meaning |
|-------|---------|
| `uxBitsToWaitFor` | Bit mask |
| `xClearOnExit` | Clear those bits when wait satisfied |
| `xWaitForAllBits` | pdTRUE=AND, pdFALSE=OR |
| `xTicksToWait` | Timeout |

### ISR note
Use `xEventGroupSetBitsFromISR()` — never `SetBits()` in ISR.

---

## Practice

1. Copy `freertos.c` + `main_user_code.c`
2. USART2 115200 + add `common/uart_debug.c` to project
3. Call `UartDebug_Init()` in `MX_FREERTOS_Init` before tasks

---

## Verify

| Test | Expected |
|------|----------|
| Power on | Main task blocked, UART shows init tasks starting |
| ~3 s later | "ALL READY" message, LED blinks 5× fast |
| Change to wait ANY | Main wakes after first init only |

---

## Architecture

```
  sensorInit ──► SET_BIT_SENSOR ──┐
  commInit   ──► SET_BIT_COMM   ──┼──► EventGroup ──► mainTask
  calInit    ──► SET_BIT_CAL    ──┘
```
