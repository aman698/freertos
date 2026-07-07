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

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 5  
**Level:** L3 RTOS (event groups)

### Breakpoints
| Where | Why |
|-------|-----|
| `xEventGroupSetBits` in each init task | Bit setter |
| `xEventGroupWaitBits` in main task | Blocks until mask satisfied |
| Line after wait returns | All bits ready |

### Watch expressions
```
xEventGroupGetBits(eventGroupHandle)   // use your handle name from freertos.c
xTaskGetTickCount()
```

### Step drill
1. Breakpoint on `xEventGroupWaitBits` — **Step Into** once — see blocking when bits missing
2. **Resume** — as each init task sets bits, re-break at Wait (or use conditional: all bits set)
3. **Expressions:** event bits increment: `0x01`, `0x03`, `0x07` style progression

### Modify + debug
Change wait to **ANY** bit (`pdFALSE` for wait-for-all) — main unblocks after first SetBits; observe with single breakpoint on wake.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Main blocked at boot in Task List | |
| All bits set before main leaves wait | |
