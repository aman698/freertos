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
