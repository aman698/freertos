# Example 01 — Multi-Task LED + Heartbeat

**Days:** 1, 2, 3  
**Hardware:** PA5 (LED only). USART2 optional from Day 2.

---

## Theory

### What is a FreeRTOS task?
A task is a function that runs in an infinite loop. The scheduler switches between tasks so each appears to run at the same time.

### Task states
```
Running → Blocked (osDelay) → Ready → Running
```

### Why `osDelay` not `HAL_Delay`?
- `HAL_Delay` = busy-wait, blocks **entire CPU**
- `osDelay` = task sleeps, **other tasks run**

### CMSIS_V2 mapping
| CMSIS | FreeRTOS |
|-------|----------|
| `osThreadNew` | `xTaskCreate` |
| `osDelay` | `vTaskDelay` |
| `osKernelStart` | `vTaskStartScheduler` |

---

## Practice — Step by Step

### 1. CubeMX (first time only)
- FREERTOS CMSIS_V2 enabled
- PA5 → GPIO_Output
- (Day 2+) USART2 → 115200

### 2. Edit `Core/Src/freertos.c`
Open your project file and paste code from `freertos.c` in this folder into the `USER CODE` sections. Keep CubeMX-generated `#include` lines at top.

**Minimum you must understand:**

```c
// Task attribute: name, stack bytes, priority
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 256 * 4,    // 256 words × 4 bytes
  .priority = osPriorityNormal,
};

// Create in MX_FREERTOS_Init()
ledTaskHandle = osThreadNew(StartLedTask, NULL, &ledTask_attributes);

// Task body — infinite loop required
void StartLedTask(void *argument) {
  for (;;) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    osDelay(200);
  }
}
```

### 3. Edit `Core/Src/main.c`
Paste from `main_user_code.c` — only the `USER CODE` blocks. Do not replace entire `main.c`.

### 4. Build → Run

---

## Verify

| Check | Pass? |
|-------|-------|
| LD2 blinks ~5 times per second | |
| FreeRTOS Task List shows 2 tasks | |
| No hard fault | |

---

## Modify (Day 2 — add urgent task)

Add to `freertos.c`:

```c
osThreadId_t urgentTaskHandle;
const osThreadAttr_t urgentTask_attributes = {
  .name = "urgent",
  .stack_size = 512 * 4,
  .priority = osPriorityHigh,
};

void StartUrgentTask(void *argument) {
  for (;;) {
    printf("[urgent]\r\n");
    osDelay(100);
  }
}

// In MX_FREERTOS_Init:
urgentTaskHandle = osThreadNew(StartUrgentTask, NULL, &urgentTask_attributes);
```

## Modify (Day 3 — vTaskDelayUntil)

Replace LED task loop:

```c
void StartLedTask(void *argument) {
  TickType_t lastWake = xTaskGetTickCount();
  for (;;) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(300));
  }
}
```

---

## Common mistakes

| Mistake | Symptom |
|---------|---------|
| Code after `osKernelStart()` | Never executes |
| Stack too small with `printf` | Hard fault |
| Forgot `for(;;)` in task | Task exits → crash |
