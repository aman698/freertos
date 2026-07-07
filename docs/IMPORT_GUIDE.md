# How to Import Any Example into STM32CubeIDE

Step-by-step for **every** example in this repo.

---

## Method A — One project for all days (recommended)

Use a single CubeMX project `FreeRTOS_Practice`. Each day, replace `freertos.c` content.

**Pros:** Fast switching, one debug config  
**Cons:** Must backup if you want to keep previous day

---

## Method B — Separate project per example (advanced)

Clone project folder in CubeIDE for capstone (`Advanced_FreeRTOS_Lab`).

---

## Every Import Checklist

### 1. CubeMX generate (once)
- [ ] NUCLEO-F411RE
- [ ] FreeRTOS CMSIS_V2
- [ ] PA5 output
- [ ] PC13 EXTI (if example uses button)
- [ ] USART2 115200 (if example uses UART)
- [ ] Heap 15KB (basic) or 24KB (advanced)

### 2. Copy code files

| Repo file | CubeIDE destination |
|-----------|---------------------|
| `examples/XX/freertos.c` | Merge into `Core/Src/freertos.c` |
| `examples/XX/main_user_code.c` | Paste USER CODE in `Core/Src/main.c` |
| `common/uart_debug.c` | `Core/Src/uart_debug.c` |
| `common/uart_debug.h` | `Core/Inc/uart_debug.h` |
| `common/freertos_utils.c` | `Core/Src/freertos_utils.c` |
| `common/freertos_utils.h` | `Core/Inc/freertos_utils.h` |
| `projects/.../app/*.c` | `App/Src/` |
| `projects/.../app/*.h` | `App/Inc/` |

### 3. Add include path (capstone / app modules)
Project → Properties → C/C++ Build → Settings → MCU GCC Compiler → Include paths:
```
../App/Inc
```

### 4. Refresh and build
- Right-click project → Refresh
- Project → Build All
- Fix: missing `UartDebug_Init` → add `uart_debug.c` to project

### 5. Debug (recommended before serial-only Run)

1. **Run → Debug (F11)** — not Run (Ctrl+F11) on first pass
2. CubeMX must have **SYS → Debug → Serial Wire**
3. Complete **Debugger Practice** section in that example's `README.md`
4. Full theory: [`DEBUGGING_GUIDE.md`](DEBUGGING_GUIDE.md)

| First-time check | Pass? |
|------------------|-------|
| Halts at `main()` or `Reset_Handler` | |
| **FreeRTOS Task List** shows tasks (after `osKernelStart`) | |
| **Step Over (F6)** advances one line | |
| Breakpoint in task hits when code runs | |

Serial terminal: 115200 on ST-LINK COM port (independent of debugger halt).

---

## USER CODE Rule

CubeMX regenerates files. **Only edit between:**
```c
/* USER CODE BEGIN X */
  your code
/* USER CODE END X */
```

For `freertos.c`: CubeMX creates `MX_FREERTOS_Init()` skeleton — put task creation inside `USER CODE BEGIN Init`.

---

## Copy freertos.c the safe way

1. Open CubeIDE `Core/Src/freertos.c`
2. Open repo `examples/XX/freertos.c` side by side
3. Copy **includes** → `USER CODE BEGIN Includes`
4. Copy **variables** → `USER CODE BEGIN Variables`
5. Copy **prototypes** → `USER CODE BEGIN FunctionPrototypes`
6. Copy **MX_FREERTOS_Init body** → `USER CODE BEGIN Init`
7. Copy **task functions** → `USER CODE BEGIN Application` or after Init

Do **not** delete CubeMX copyright header or `#include "cmsis_os.h"` at top.

---

## Common build errors

| Error | Fix |
|-------|-----|
| `undefined reference to UartDebug_Init` | Add `uart_debug.c`, enable USART2 |
| `multiple definition HAL_UART_RxCpltCallback` | Keep callback in ONE file only |
| `configASSERT failed` in ISR | Lower ISR priority in NVIC (use 5+) |
| `osThreadNew returns NULL` | Increase `configTOTAL_HEAP_SIZE` |
| `undefined reference to snprintf` | Enable nano printf in linker or use `-u _printf_float` |

---

## Practice workflow diagram

```
Read THEORY (guide + THEORY_REFERENCE.md)
        │
        ▼
Read example README.md
        │
        ▼
CubeMX configure pins
        │
        ▼
Copy files (this doc)
        │
        ▼
Build → Debug (F11) → DEBUGGER PRACTICE
        │
        ▼
Build → Flash → VERIFY checklist
        │
        ▼
MODIFY experiments
        │
        ▼
Write PRACTICE_LOG.md
```
