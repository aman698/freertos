# Example 10 — Stream Buffer + UART Command CLI

**Day 13** | Single-writer single-reader byte stream.

---

## Theory (deep)

### Stream buffer vs Queue of uint8_t
| | Stream Buffer | Queue (1 byte items) |
|---|---------------|----------------------|
| Overhead per byte | Low | High (queue structure) |
| Readers | **1** | Many |
| Writers | **1** | Many |
| Data unit | Raw bytes | Fixed-size copies |

### Trigger levels
`xStreamBufferSend(..., xTriggerLevelBytes)` — reader unblocks when >= N bytes available.

### Typical UART pattern
```
IRQ/DMA writes bytes ──► stream buffer ──► line parser task
```

---

## UART Commands
| Command | Action |
|---------|--------|
| `LED ON` | PA5 high |
| `LED OFF` | PA5 low |
| `STATUS` | Print heap + stack |
| `HELP` | List commands |

Type in serial terminal (115200), end with Enter.

---

## Practice
1. Add `common/uart_debug.c` + `freertos.c`
2. Enable USART2 RX interrupt in CubeMX
3. Paste `main_user_code.c` for RX callback

## Verify
- [ ] `LED ON` / `LED OFF` work
- [ ] `STATUS` prints heap

## Modify
- Stream size 32 → send 64-char line → observe truncation/block

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 6–7  
**Level:** L3–L4 (stream buffer + CLI)

### Breakpoints
| Where | Why |
|-------|-----|
| UART RX callback / byte push to stream | Producer |
| Stream receive in parser task | Consumer |
| Command handler e.g. `LED ON` | Application logic |

### Watch expressions
```
xStreamBufferBytesAvailable(streamHandle)
xStreamBufferSpacesAvailable(streamHandle)
line[0]   // at parser breakpoint
```

### Step drill
1. Type `STATUS` in terminal — halt when bytes enter stream buffer
2. **Step Over** receive loop assembling `line`
3. **Step Into** command strcmp branch — **Step Return** after handler

### Advanced — live expressions
Enable live update on `xStreamBufferBytesAvailable` while typing — see buffer fill (may jitter under RTOS).

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Bytes available > 0 after typing | |
| `line` contains full command at parse | |
