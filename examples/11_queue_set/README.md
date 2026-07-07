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
