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
