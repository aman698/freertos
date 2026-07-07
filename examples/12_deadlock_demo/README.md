# Example 12 — Priority Inversion & Deadlock

**Day 15** | Intentional bugs + fixes.

---

## Theory (deep)

### Priority inversion scenario (this lab)
1. `lowTask` takes `mutexL`
2. `highTask` tries `mutexL` → blocks
3. `mediumTask` runs (no mutex need) → **blocks highTask indirectly**

With `configUSE_MUTEXES` and priority inheritance, `lowTask` temporarily runs at `highTask` priority.

### Deadlock scenario
```
taskA: Take(M1) → wait(M2)
taskB: Take(M2) → wait(M1)
```
**Fix:** Global lock ordering — always M1 then M2.

### Detection
- `xSemaphoreTake(m, timeout)` — never infinite wait in debug
- Watchdog timer
- GPIO heartbeat stops

---

## Practice

**Part A — Inversion:** Run `USE_DEADLOCK_DEMO = 0` in freertos.c  
**Part B — Deadlock:** Set `USE_DEADLOCK_DEMO = 1`, observe hang, then apply fix.

## Verify
- [ ] Part A: UART shows high task completes
- [ ] Part B: hang; after lock ordering fix, runs

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 7 (deadlock)  
**Level:** L4 Advanced

### Part A — Priority inversion (`USE_DEADLOCK_DEMO = 0`)

**Breakpoints:** `xSemaphoreTake` in low and high tasks  
**Watch:** Task List priorities — `low` may temporarily inherit high priority  
**Step:** High blocks on Take while low holds `mutexL` — med runs — observe inheritance when enabled

### Part B — Deadlock (`USE_DEADLOCK_DEMO = 1`)

1. Run until UART stops (hang)
2. **Suspend** CPU (do not reset)
3. **FreeRTOS Task List** — `taskA` and `taskB` both **Blocked**
4. **Call Stack** — each in `xSemaphoreTake` waiting for the other mutex
5. **Expressions:** inspect which mutex each task already holds (from local flow / UART log)

### Fix verification
Apply lock ordering (M1 then M2 everywhere) → same breakpoints → no permanent Blocked pair.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Part A: high eventually completes | |
| Part B: two blocked tasks on suspend | |
| After fix: Resume runs without manual reset | |
