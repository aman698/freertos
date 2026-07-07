# Example 11 — Queue Set (Event Dispatcher)

**Day 14** | One task waits on multiple queues.

---

## Theory

`xQueueSelectFromSet()` returns handle of queue that received data.

### Limitation
A queue in a set cannot also be read directly — must go through select.

### Use case
Supervisor task:
- Button queue
- UART command queue  
- Sensor alert queue

Without queue set: poll each queue with 0 timeout — wastes CPU.

---

## Practice
Copy files, enable button EXTI + UART RX (or simulate sensor queue in software).

## Verify
- [ ] Button press → dispatcher logs "BTN"
- [ ] Software timer injects sensor event every 3 s → logs "SENSOR"

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 5–6  
**Level:** L3 RTOS (queue set)

### Breakpoints
| Where | Why |
|-------|-----|
| `xQueueSelectFromSet` | Multiplex wait |
| Branch handling button queue | BTN path |
| Branch handling sensor queue | SENSOR path |

### Watch expressions
```
uxQueueMessagesWaiting(btnQueue)      // names from your freertos.c
uxQueueMessagesWaiting(sensorQueue)
```

### Step drill
1. Halt on `xQueueSelectFromSet` — task **Blocked** until any member queue has data
2. Press button → **Resume** → returns button queue handle
3. Wait 3 s for timer → returns sensor queue handle
4. **Step Into** dispatch `if` chain — map handle to log message

### Theory check
Queues in a set must not be read directly — breakpoint only in select loop or member send paths.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Select unblocks on button OR sensor | |
| Correct branch for each source | |
