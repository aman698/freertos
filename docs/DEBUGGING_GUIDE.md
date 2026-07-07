# STM32CubeIDE Debugger — Full Practice Guide (Basic → Advanced)

**Board:** NUCLEO-F411RE (STM32F411RE)  
**IDE:** STM32CubeIDE (Eclipse + GDB + ST-LINK)  
**Use with:** Every example in this repo — each `examples/XX/README.md` has example-specific debugger drills.

---

## Part 1 — Hardware & Protocol Theory

### What is on-chip debug?

Your MCU has a **Debug Access Port (DAP)** inside the chip. The debugger talks to DAP; DAP reads/writes CPU registers, memory, and flash **while the chip runs or halts**.

```
  PC (STM32CubeIDE) ──USB──► ST-LINK (on Nucleo) ──SWD──► STM32F411 DAP ──► Cortex-M4 core
```

You do **not** need extra wiring on NUCLEO-F411RE — ST-LINK is already connected to the target MCU.

### JTAG vs SWD

| Protocol | Pins | Speed | Use on STM32 |
|----------|------|-------|--------------|
| **JTAG** | 4+ (TCK, TMS, TDI, TDO) | Good | Legacy, boundary scan, multi-chip chains |
| **SWD** | 2 data (SWDIO, SWCLK) + GND | Faster setup | **Default for STM32** — use this |

**SWD (Serial Wire Debug)** is ARM's 2-wire protocol. It is what CubeMX means by **Serial Wire**.

| Signal | Pin on STM32 | Role |
|--------|--------------|------|
| **SWDIO** | PA13 | Data in/out |
| **SWCLK** | PA14 | Clock |
| **SWO** | PB3 (optional) | Trace output (ITM) |

### ST-LINK

ST-LINK is ST's USB debug probe. On Nucleo boards it is **embedded** (ST-LINK/V2-1).

| Function | What it does |
|----------|--------------|
| **Debug** | SWD connection, breakpoints, single-step |
| **Program** | Flash your `.elf` |
| **VCP** | Virtual COM port — USART2 routed to USB (serial printf) |
| **Power** | Can power target from USB |

**Theory:** One USB cable gives you flash + debug + serial terminal. The debug and UART paths are independent — you can halt the CPU in the debugger while UART already sent bytes.

### CubeMX debug setting (mandatory)

| Setting | Value | Why |
|---------|-------|-----|
| **SYS → Debug** | **Serial Wire** | Keeps PA13/PA14 for SWD; disables JTAG |
| **SYS → Trace** | None (basic) or Asynchronous SW (advanced trace) | SWO needs PB3 |

If Debug = **Disable**, SWD pins become GPIO → debugger cannot connect after flash.

---

## Part 2 — First Debug Session (Basic)

### Launch configuration

1. Build project (hammer icon) — must be **Debug** build ( `-g` symbols)
2. **Run → Debug** (or **F11**) — *not* Run (Ctrl+F11)
3. First time: switch to **Debug perspective** → click **Yes**
4. Program downloads; CPU halts at `main()` or `Reset_Handler`

### Debug perspective layout

| View | Purpose |
|------|---------|
| **Debug** | Stack of threads / cores |
| **Editor** | Source with breakpoint markers |
| **Variables** | Locals + globals in current stack frame |
| **Breakpoints** | List of all breakpoints |
| **Registers** | CPU registers (R0–R15, xPSR, PC, SP) |
| **Expressions** | Watch arbitrary C expressions |
| **Memory** | Raw hex dump at any address |

Open any view: **Window → Show View → …**

### Essential controls

| Action | Shortcut | What happens |
|--------|----------|--------------|
| **Resume** | F8 | Run until next breakpoint |
| **Suspend** | (pause btn) | Halt CPU wherever it is |
| **Terminate** | Ctrl+F2 | End debug session |
| **Step Over** | F6 | Execute current line; **do not enter** functions |
| **Step Into** | F5 | Enter function called on current line |
| **Step Return** | F7 | Run until current function returns |
| **Run to Line** | Ctrl+R | Continue to cursor line (right-click) |

### Step Over vs Into vs Return — practice drill

Use **Example 01** (`StartLedTask`):

```c
for (;;) {
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // line A
  osDelay(200);                              // line B
}
```

1. Breakpoint on **line A** → Debug (F11) → hits breakpoint
2. **Step Into** (F5) on `HAL_GPIO_TogglePin` → you land inside HAL driver (GPIO write). **Step Return** (F7) → back to task
3. **Step Over** (F6) on `osDelay(200)` → skips inside `vTaskDelay` — lands on next loop iteration
4. **Step Into** (F5) on `osDelay(200)` → enters RTOS delay code — see how blocking works

**Rule of thumb:**
- **Step Over** — daily debugging; trust the function
- **Step Into** — learn HAL/RTOS internals or find bugs inside callee
- **Step Return** — escape deep HAL after you understood enough

### Breakpoints (basic)

| Type | How | Use |
|------|-----|-----|
| **Line** | Double-click gutter / Ctrl+Shift+B | Halt before that line executes |
| **Enable/disable** | Breakpoints view checkbox | Keep without deleting |
| **Skip count** | Breakpoint properties → **Ignore count** | Skip first N hits |

**Hardware limit:** Cortex-M4 typically supports **4–6 hardware breakpoints** simultaneously. Unlimited *software* breakpoints work in RAM but flash uses hardware slots.

---

## Part 3 — Variables, Watch & Expressions

### Variables view

Shows automatic locals when halted. Expand structs (`GPIO_InitTypeDef`, `osThreadAttr_t`).

If a variable shows **optimized out**:
- Build config: set optimization to `-Og` (Debug) not `-Os`
- Project → Properties → C/C++ Build → Settings → Optimization → **Debug: -Og**

### Expressions view (watch)

**Window → Show View → Expressions** → **Add new expression** (+)

| Expression | Example | Notes |
|------------|---------|-------|
| Global handle | `ledTaskHandle` | CMSIS thread ID |
| HAL peripheral | `huart2.gState` | UART state machine |
| FreeRTOS queue | `uxQueueMessagesWaiting(rawIsrQueue)` | Needs `rawIsrQueue` in scope or global |
| Cast handle | `(uint32_t)xTaskGetCurrentTaskHandle()` | Compare with `ledTaskHandle` |

### Live expressions (advanced)

Right-click expression → **Enable Live Expressions** (or **Continuous Mode** in some versions).

- Updates **while CPU runs** (periodic refresh)
- **Caution with FreeRTOS:** values change mid-instruction; race conditions visible — good for learning, misleading for precise timing
- Best for: `xTickCount`, GPIO IDR bit, queue depth counters

### Memory browser

**Window → Show View → Memory**

Add monitor: address `&rawIsrQueue` or explicit `0x20000000` (SRAM start on F411).

Use to inspect queue storage bytes after `xQueueSend`.

---

## Part 4 — Registers & Fault Debugging

### Registers view

When halted, inspect:

| Register | Meaning |
|----------|---------|
| **PC** | Program counter — next instruction address |
| **SP / PSP / MSP** | Stack pointer (PSP = task stack in FreeRTOS thread mode) |
| **LR** | Link register — return address |
| **xPSR** | Flags + exception number |

### HardFault — find cause fast

1. After fault: debugger may halt in `HardFault_Handler`
2. **Window → Show View → Fault Analyzer** (if available) or check **SCB→CFSR/HFSR** in Registers
3. **Call Stack** view — who called whom before crash

Common FreeRTOS faults:

| Symptom | Likely cause |
|---------|--------------|
| Fault in `prvTaskExitError` | Task function returned (no `for(;;)`) |
| Fault in `xQueueSend` | Queue NULL or scheduler not started |
| Fault in `printf` | Stack too small |
| Fault in ISR | API not `FromISR` variant |

### Stack overflow hook debug

When `vApplicationStackOverflowHook` runs:

```c
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  for (;;);  /* set breakpoint HERE */
}
```

- Inspect `pcTaskName` in **Variables**
- **Expressions:** `uxTaskGetStackHighWaterMark(xTask)`

---

## Part 5 — FreeRTOS-Aware Debugging

### Enable trace in CubeMX

```
configUSE_TRACE_FACILITY     = 1
configUSE_STATS_FORMATTING_FUNCTIONS = 1  (optional, for vTaskList)
```

### FreeRTOS Task List view

**Window → Show View → FreeRTOS Task List**

| Column | Meaning |
|--------|---------|
| Name | Task name from `osThreadAttr_t` |
| State | Running / Ready / Blocked / Suspended |
| Priority | Current priority (inheritance may boost) |
| Stack free | High-water remaining |

**Practice:** Run Example 01 → Suspend when LED task blocked on `osDelay` → `ledTask` shows **Blocked**, `heartbeatTask` **Ready** or **Running**.

### Debug a specific task

1. Suspend CPU
2. In **Debug** view, expand **RTOS** or thread list
3. Select task → **Switch to context** (right-click) — see that task's stack frame

Without RTOS plugin: set breakpoint inside that task's function only; wait for hit.

### Scheduler stopped vs running

| Mode | Behavior |
|------|----------|
| **Halt (suspend)** | Scheduler frozen — good for inspecting state |
| **Resume** | Real-time behavior — queues fill, ISRs fire |

**Tip:** To inspect queue state, halt inside consumer task just after `xQueueReceive` returns.

### APIs safe to call from debugger (GDB expressions)

While halted, in Expressions or GDB console:

```c
uxTaskGetStackHighWaterMark(NULL)
xPortGetFreeHeapSize()
uxQueueMessagesWaiting(debouncedQueue)
```

---

## Part 6 — Intermediate Techniques

### Conditional breakpoint

Right-click breakpoint → **Breakpoint Properties**:

```
Condition: pressId > 5
```

Use in Example 02 — only stops after 5 button presses.

### Logpoint (tracepoint)

Breakpoint → **Action: Log message** (no halt):

```
Button press {pressId}
```

Output in **Console** — minimal intrusion.

### Watch GPIO live

**Expressions:**

```c
GPIOC->IDR & GPIO_PIN_13
GPIOA->ODR & GPIO_PIN_5
```

Bit **0** = LED on (PA5 low on Nucleo depends on wiring; observe toggle).

### Debug ISR path

Example 02 — breakpoint in `HAL_GPIO_EXTI_Callback` or `Button_ISR_SendEventFromISR`:

1. Press button → should hit **only** when EXTI fires
2. **Step Over** `xQueueSendFromISR`
3. **Expressions:** `uxQueueMessagesWaiting(rawIsrQueue)` → should increment
4. **Step Return** to exit ISR → may context-switch to debounce task

**Theory:** ISR must finish quickly. If you **Step Into** HAL calls in ISR, timing stretches — OK for learning, not for production timing tests.

### Mutex state (Example 03)

Breakpoint in `SafePrintf` between Take and Give:

- **Step Into** `xSemaphoreTake` when other task holds mutex → watch task **Block**
- Resume → holder **Gives** → blocked task **Ready**

---

## Part 7 — Advanced Techniques

### SWO / ITM printf trace (optional hardware)

1. CubeMX: **SYS → Trace → Asynchronous SW**, prescaler for 84 MHz or your SYSCLK
2. Debug Config → **SWV** → enable ITM Stimulus Port 0
3. Redirect `ITM_SendChar` for trace printf without UART

**Theory:** ITM is one-way MCU → PC on SWO pin (PB3). Lower overhead than UART; does not use USART2.

### Instruction trace / ETB

STM32F411 has limited trace. For deep timing, use **logic analyzer on GPIO** or **DWT cycle counter**:

```c
DWT->CYCCNT = 0;
DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
// ... code under test ...
uint32_t cycles = DWT->CYCCNT;
```

Read `cycles` in Expressions at breakpoint.

### Data breakpoint (watchpoint)

Right-click variable → **Breakpoint → Hardware Watchpoint**

- **Write** to `pressId` → halts any task that modifies it
- Limited hardware watchpoints (usually 2–4)

### Deadlock inspection (Example 12)

When system hangs:

1. **Suspend** (do not reset)
2. **FreeRTOS Task List** — two tasks **Blocked** on semaphore forever
3. **Call Stack** for each — both stuck in `xSemaphoreTake`
4. **Expressions:** `mutexM1`, `mutexM2` holder state via internal handles (or use UART log + breakpoint strategy)

### Queue corruption debug

Symptoms: random faults in `xQueueReceive`

- **Memory** view at queue storage pointer
- Verify `configASSERT` enabled — failed asserts call `configASSERT()` → halt
- Check **stack overflow** first

### Debug vs Release builds

| Build | Symbols | Optimization | Use |
|-------|---------|--------------|-----|
| Debug | Yes (`-g3`) | `-Og` | Daily development |
| Release | Optional | `-Os` | Shipping — harder to debug |

---

## Part 8 — Connection Troubleshooting

| Problem | Fix |
|---------|-----|
| **No ST-LINK detected** | Replug USB; Device Manager → ST-LINK; try another cable (data, not charge-only) |
| **SWD connection failed** | CubeMX: Debug = Serial Wire; regenerate; full chip erase |
| **Busy target** | Terminate all debug sessions; press Nucleo **BLACK** reset |
| **Variables `<optimized out>`** | Use Debug build, `-Og` |
| **Breakpoints ignored** | Build before debug; clean build; verify `.elf` path in launch config |
| **FreeRTOS task list empty** | `configUSE_TRACE_FACILITY=1`; include FreeRTOS plugin; start scheduler |

### External ST-LINK (if you detach Nucleo ST-LINK)

Wire **SWDIO, SWCLK, GND, 3.3V** to CN4 (SWD) on Nucleo. **Do not** connect 5V to 3.3V target.

---

## Part 9 — Practice Curriculum (map to examples)

Do **Part 2–3** once on Example 01, then add skills per example:

| Level | Skills | Examples |
|-------|--------|----------|
| **L1 Basic** | F5–F8, line breakpoints, Variables | 01, 02 |
| **L2 Intermediate** | Watch, Expressions, FreeRTOS Task List, ISR breakpoints | 02, 03, 04, 05 |
| **L3 RTOS** | Queue depth, mutex block, timer callback step | 04, 05, 08, 09 |
| **L4 Advanced** | Conditional BP, deadlock suspend, stack hook, live expr | 06, 12, capstone |
| **L5 Expert** | SWO, DWT cycles, data watchpoints | Capstone, 07 |

---

## Part 10 — Quick Reference Card

```
F11  Debug (download + halt)
F8   Resume
F6   Step Over    — execute line, skip into functions
F5   Step Into    — enter function
F7   Step Return  — run until function exits
Ctrl+F2  Terminate session

Views: Variables | Expressions | Memory | Registers | Breakpoints | FreeRTOS Task List
CubeMX: SYS → Debug → Serial Wire
```

---

## Per-Example Drills

Each example README contains a **Debugger Practice** section with:

- Breakpoints to set (file + function)
- **Watch expressions** to add
- **Step Into/Over/Return** exercise
- Expected observation when correct

**Start here:** [`examples/01_basic_multi_task/README.md`](../examples/01_basic_multi_task/README.md) → Debugger Practice

---

**Related:** [`THEORY_REFERENCE.md` §12](../THEORY_REFERENCE.md) | [`IMPORT_GUIDE.md`](IMPORT_GUIDE.md) | [`PRACTICE_GUIDE.md`](../PRACTICE_GUIDE.md)
