# Example 14 — STM32 bxCAN + FreeRTOS (J1939-style Decode)

**Day:** 14 (protocols)
Full source is provided:

| File | Purpose |
|------|---------|
| [`freertos.c`](freertos.c) | Queue, `CanParserTask`, `CanSenderTask`, J1939-style ID encode/decode |
| [`main_user_code.c`](main_user_code.c) | `main.c` USER CODE snippets for CAN1 filter/start + RX ISR callback |

See also: [`automotive_protocols/topic_03_j1939_transport`](../../automotive_protocols/topic_03_j1939_transport) for the portable-C treatment of 29-bit ID pack/unpack and transport, and [`automotive_protocols/topic_05_uds`](../../automotive_protocols/topic_05_uds) for the request/response diagnostic services that typically ride on top of a CAN/J1939 link.

---

## Theory

bxCAN (basic extended CAN) is the CAN peripheral built into the STM32F411. Frames arrive asynchronously and land in one of two hardware RX FIFOs; an interrupt fires per accepted frame. The ISR must:
1. Call `HAL_CAN_GetRxMessage` to pull the header + data out of the FIFO (this is fast, register-level work — safe in ISR context)
2. `xQueueSendFromISR` the frame to a parser task
3. `portYIELD_FROM_ISR`

Parser task:
- `xQueueReceive` frames
- Decode the 29-bit extended ID into J1939-style `{priority, PGN, source address}` fields
- Print a decoded summary for a couple of illustrative well-known PGNs (EEC1 engine speed, DM1 diagnostic trouble codes)

A bare Nucleo-F411RE has **no CAN transceiver fitted** — PA11/PA12 come straight off the MCU with no differential driver, so there is nothing to connect to a real bus. To exercise both TX and RX on the board by itself, CAN1 is configured in **loopback mode** (`CAN_MODE_LOOPBACK`): every frame the peripheral transmits is internally looped straight back into an RX FIFO, so `CanSenderTask`'s periodic TX frame is exactly what `CanParserTask` receives and decodes. To talk to a real bus or an actual J1939 network you would need a transceiver IC (e.g. TJA1050, MCP2551) between PA11/PA12 and the bus, plus 120 Ω termination at each end of the bus — none of that is required for this example.

**Never** call `printf`, `HAL_UART_Transmit` (blocking), or any other slow/blocking call from inside `HAL_CAN_RxFifo0MsgPendingCallback` — decode and print only from the deferred task.

---

## CubeMX setup

- **Connectivity → CAN1**: enable (uses PA11 = CAN1_RX, PA12 = CAN1_TX)
- **Mode** = Loopback (no transceiver on a bare Nucleo board)
- Bit timing for 500 kbit/s at 42 MHz APB1 clock: Prescaler = 6, Time Quantum in Bit Segment 1 = 11 TQ, Time Quantum in Bit Segment 2 = 2 TQ, Resync Jump Width = 1 TQ (1 + 11 + 2 = 14 quanta × 6 prescaler = 84 → 42 MHz / 84 = 500 kHz)
- **NVIC → CAN1 RX0 interrupt** enabled (`CAN1_RX0_IRQn`)
- **FreeRTOS** CMSIS_V2 enabled

---

## Key snippet — main.c USER CODE

```c
/* USER CODE BEGIN 2 */
CAN_FilterTypeDef canFilter;
canFilter.FilterBank = 0;
canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
canFilter.FilterIdHigh = 0x0000U;
canFilter.FilterIdLow = 0x0000U;
canFilter.FilterMaskIdHigh = 0x0000U;
canFilter.FilterMaskIdLow = 0x0000U;
canFilter.FilterFIFOAssignment = CAN_RX_FIFO0;
canFilter.FilterActivation = ENABLE;
canFilter.SlaveStartFilterBank = 14;

HAL_CAN_ConfigFilter(&hcan1, &canFilter);
HAL_CAN_Start(&hcan1);
HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (hcan->Instance == CAN1) {
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK) {
      Can_ISR_SendFrameFromISR(&rxHeader, rxData);
    }
  }
}
/* USER CODE END 4 */
```

## Key snippet — freertos.c

```c
void Can_ISR_SendFrameFromISR(CAN_RxHeaderTypeDef *rxHeader, uint8_t *rxData)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  CanFrameMsg_t frame;

  frame.id = rxHeader->ExtId;
  frame.dlc = (uint8_t)rxHeader->DLC;
  memcpy(frame.data, rxData, sizeof(frame.data));

  (void)xQueueSendFromISR(canRxQueue, &frame, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void StartCanParserTask(void *argument)
{
  CanFrameMsg_t frame;
  for (;;) {
    if (xQueueReceive(canRxQueue, &frame, portMAX_DELAY) == pdTRUE) {
      Can_PrintFrame(&frame);   /* decodes priority/PGN/source addr, prints summary */
    }
  }
}
```

---

## Verify

- [ ] Build and flash — `[CAN] parser task ready` and `[CAN] sender task ready` banners print at boot
- [ ] Every ~1 s, a decoded `[CAN] id=0x... prio=3 pgn=61444(0xF004) sa=0x17 dlc=8` line appears
- [ ] The EEC1 line is followed by `-> EEC1: engine speed ~= NNN rpm`, ramping up and wrapping around
- [ ] No frame is ever printed from inside `HAL_CAN_RxFifo0MsgPendingCallback` itself

---

## If you complete this

You have implemented the ISR → queue → task deferral pattern a third time (GPIO, UART, now CAN), plus a from-scratch J1939-style extended-ID encode/decode pair and a TX path — the same shape of work a real vehicle ECU driver does before handing frames to an application layer like UDS.

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 6 (Debug ISR path)
**Level:** L3–L5

### Breakpoints
| Where | Why |
|-------|-----|
| `HAL_CAN_RxFifo0MsgPendingCallback` | Per-frame ISR entry |
| `Can_ISR_SendFrameFromISR` → `xQueueSendFromISR` | Defer to parser task |
| `Can_SendDemoFrame` → `HAL_CAN_AddTxMessage` | TX path, mirrors back via loopback |
| `Can_PrintFrame` | Consumer-side decode |

### Watch expressions
```
frame.id
frame.dlc
uxQueueMessagesWaiting(canRxQueue)
hcan1.Instance->RF0R
simRpm
```

### Step drill
1. Halt at `Can_SendDemoFrame` right before `HAL_CAN_AddTxMessage` → note `extId`
2. **Step Over** `HAL_CAN_AddTxMessage` — loopback immediately fires the RX0 IRQ
3. **Resume**, halt in `HAL_CAN_RxFifo0MsgPendingCallback` → same `extId` reappears in `rxHeader.ExtId`
4. **Step Over** `Can_ISR_SendFrameFromISR` — `uxQueueMessagesWaiting(canRxQueue)` +1
5. **Resume** → `CanParserTask` wakes, `Can_PrintFrame` prints the decoded PGN/rpm

### Advanced — flood test / stress scenario
Temporarily drop `CAN_SENDER_PERIOD_MS` to a few ms (or call `Can_SendDemoFrame` in a tight loop) → **Suspend** mid-flood → `uxQueueMessagesWaiting(canRxQueue)` should climb toward `CAN_RX_QUEUE_LEN` (16); push past it to observe `xQueueSendFromISR` silently dropping frames (return value `pdFALSE`), the same overflow risk as example 07's UART queue.

### Theory check
**Never Step Into** `HAL_CAN_GetRxMessage` for more than a glance — it's register-level FIFO pop-off, fine to skim once, but stepping through it repeatedly just burns ISR-halted time; the real logic to study is in the deferred task.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| RX0 IRQ fires once per `HAL_CAN_AddTxMessage` in loopback | |
| `extId` round-trips unchanged from TX encode to RX decode | |
| Queue depth returns to 0 shortly after each frame (parser keeps up) | |
