# Example 13 — Static Allocation

**Day 18** | Zero heap use after boot for queues.

---

## Theory

`xQueueCreateStatic` pre-allocates:
- `StaticQueue_t` control structure
- `uint8_t buffer[length × itemSize]`

Benefits:
- Deterministic memory
- No fragmentation
- Required for some safety certifications

Measure: `xPortGetFreeHeapSize()` identical before/after create.

---

## Practice
Static version of Example 02 (button → debounce → LED).

## Verify
- [ ] Same button behavior as Example 02
- [ ] Heap unchanged after init (print in UART)

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 7  
**Level:** L4 (static vs dynamic memory)

### Breakpoints
| Where | Why |
|-------|-----|
| `xQueueCreateStatic` | No heap alloc |
| After init complete | Compare heap |
| Button pipeline (same as Ex 02) | Behavior unchanged |

### Watch expressions
```
xPortGetFreeHeapSize()
xPortGetMinimumEverFreeHeapSize()
uxQueueMessagesWaiting(staticQueueHandle)
```

### Memory view
Add **Memory** monitor on static queue storage array (symbol from `freertos.c` e.g. `ucQueueStorage`) — see ring buffer bytes change on send/receive without heap movement.

### Step drill
1. Breakpoint before and after static queue create
2. **Expressions:** heap size **identical** — theory: static allocation
3. **Step Over** send/receive — heap still unchanged

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Heap same before/after queue create | |
| Queue depth changes with button press | |
