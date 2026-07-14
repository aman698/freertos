/**
 ******************************************************************************
 * EXAMPLE 14 - STM32 bxCAN + FreeRTOS (J1939-style decode)
 * Day 14 (protocols): bxCAN RX ISR -> queue -> parser task, plus a periodic
 * TX task, exercised entirely in CAN1 loopback mode (no transceiver needed).
 ******************************************************************************
 *
 * CubeMX requirements:
 * - CAN1 enabled (Connectivity -> CAN1), pins PA11 (CAN1_RX) / PA12 (CAN1_TX)
 * - CAN1 Mode = Loopback (bare Nucleo-F411RE has no on-board transceiver;
 *   loopback lets TX frames be received back on FIFO0 with just the MCU)
 * - Bit timing: Prescaler=6, BS1=11TQ, BS2=2TQ, SJW=1TQ -> 500 kbit/s @ 42 MHz APB1
 * - NVIC -> CAN1 RX0 interrupt enabled (CAN1_RX0_IRQn)
 * - FreeRTOS CMSIS_V2 enabled
 *
 * See also: automotive_protocols/topic_03_j1939_transport (29-bit ID pack/unpack
 * theory in portable C) and automotive_protocols/topic_05_uds (request/response
 * diagnostic services) for the deeper, hardware-free treatment of these ideas.
 *
 * Copy this file into Core/Src/freertos.c USER CODE sections or merge manually.
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "uart_debug.h"
#include <stdint.h>
#include <string.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
#define CAN_RX_QUEUE_LEN        16U
#define CAN_SENDER_SOURCE_ADDR  0x17U   /* illustrative J1939 source address */
#define CAN_SENDER_PERIOD_MS    1000U

/* Well-known illustrative PGNs (Parameter Group Numbers) used only to pick a
 * demo decode branch. Real PGN tables live in
 * automotive_protocols/topic_03_j1939_transport. */
#define J1939_PGN_EEC1  61444U  /* 0xF004 - Electronic Engine Controller 1 (engine speed) */
#define J1939_PGN_DM1   65226U  /* 0xFECA - Active Diagnostic Trouble Codes            */

extern CAN_HandleTypeDef hcan1;

typedef struct {
  uint32_t id;      /* 29-bit extended CAN identifier              */
  uint8_t  dlc;      /* data length, 0..8                            */
  uint8_t  data[8];  /* payload bytes                                */
} CanFrameMsg_t;

QueueHandle_t canRxQueue;
osThreadId_t canParserHandle;
osThreadId_t canSenderHandle;

const osThreadAttr_t canParser_attributes = {
  .name = "canParser",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t canSender_attributes = {
  .name = "canSender",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartCanParserTask(void *argument);
void StartCanSenderTask(void *argument);
void Can_ISR_SendFrameFromISR(CAN_RxHeaderTypeDef *rxHeader, uint8_t *rxData);
static void Can_DecodeJ1939Id(uint32_t extId, uint8_t *priority, uint16_t *pgn, uint8_t *sourceAddr);
static void Can_EncodeJ1939Id(uint8_t priority, uint16_t pgn, uint8_t sourceAddr, uint32_t *extId);
static void Can_PrintFrame(const CanFrameMsg_t *frame);
static void Can_SendDemoFrame(uint16_t simRpm);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */
  UartDebug_Init();

  canRxQueue = xQueueCreate(CAN_RX_QUEUE_LEN, sizeof(CanFrameMsg_t));
  configASSERT(canRxQueue != NULL);

  canParserHandle = osThreadNew(StartCanParserTask, NULL, &canParser_attributes);
  configASSERT(canParserHandle != NULL);

  canSenderHandle = osThreadNew(StartCanSenderTask, NULL, &canSender_attributes);
  configASSERT(canSenderHandle != NULL);
  /* USER CODE END Init */
}

/* Called from HAL_CAN_RxFifo0MsgPendingCallback (see main_user_code.c). Copies
 * the already-read frame into the queue and defers all decoding/printing to
 * CanParserTask - identical ISR-deferral pattern to example 07's UART ISR. */
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
  (void)argument;

  CanFrameMsg_t frame;

  UartDebug_Printf("\r\n[CAN] parser task ready (CAN1 loopback demo)\r\n");

  for (;;) {
    if (xQueueReceive(canRxQueue, &frame, portMAX_DELAY) != pdTRUE) {
      continue;
    }

    Can_PrintFrame(&frame);
  }
}

void StartCanSenderTask(void *argument)
{
  (void)argument;

  uint16_t simRpm = 800U;

  UartDebug_Printf("[CAN] sender task ready - TX EEC1-style frame every %lu ms\r\n",
                    (unsigned long)CAN_SENDER_PERIOD_MS);

  for (;;) {
    osDelay(CAN_SENDER_PERIOD_MS);

    simRpm += 50U;
    if (simRpm > 3000U) {
      simRpm = 800U;
    }

    Can_SendDemoFrame(simRpm);
  }
}

/* Unpack a 29-bit J1939-style extended CAN ID into {priority, PGN, source
 * address}. Same bit layout as automotive_protocols/topic_03_j1939_transport
 * (priority = bits 28:26, PGN = bits 25:8, source addr = bits 7:0). This demo
 * only exercises PGNs that fit in 16 bits, which covers every commonly-used
 * J1939 PGN (EDP/DP extension bits of the full 18-bit field are ignored). */
static void Can_DecodeJ1939Id(uint32_t extId, uint8_t *priority, uint16_t *pgn, uint8_t *sourceAddr)
{
  if ((priority == NULL) || (pgn == NULL) || (sourceAddr == NULL)) {
    return;
  }

  *priority = (uint8_t)((extId >> 26) & 0x7U);
  *pgn = (uint16_t)((extId >> 8) & 0xFFFFU);
  *sourceAddr = (uint8_t)(extId & 0xFFU);
}

/* Inverse of Can_DecodeJ1939Id - packs {priority, PGN, source address} back
 * into a 29-bit extended ID for transmission. */
static void Can_EncodeJ1939Id(uint8_t priority, uint16_t pgn, uint8_t sourceAddr, uint32_t *extId)
{
  if (extId == NULL) {
    return;
  }

  *extId = ((uint32_t)(priority & 0x7U) << 26)
         | ((uint32_t)pgn << 8)
         | (uint32_t)sourceAddr;
}

static void Can_PrintFrame(const CanFrameMsg_t *frame)
{
  uint8_t priority = 0U;
  uint16_t pgn = 0U;
  uint8_t sourceAddr = 0U;

  Can_DecodeJ1939Id(frame->id, &priority, &pgn, &sourceAddr);

  UartDebug_Printf("[CAN] id=0x%08lX prio=%u pgn=%u(0x%04X) sa=0x%02X dlc=%u\r\n",
                    (unsigned long)frame->id, priority, pgn, pgn, sourceAddr, frame->dlc);

  switch (pgn) {
    case J1939_PGN_EEC1: {
      /* SPN 190 Engine Speed lives in bytes 3-4, 0.125 rpm/bit, no offset */
      uint16_t rawSpeed = (uint16_t)(frame->data[3] | ((uint16_t)frame->data[4] << 8));
      UartDebug_Printf("       -> EEC1: engine speed ~= %lu rpm\r\n",
                        (unsigned long)(rawSpeed / 8U));
      break;
    }
    case J1939_PGN_DM1:
      UartDebug_Printf("       -> DM1: active diagnostic trouble code frame\r\n");
      break;
    default:
      UartDebug_Printf("       -> PGN not decoded in this demo (see automotive_protocols/topic_03_j1939_transport)\r\n");
      break;
  }
}

/* Builds a small illustrative J1939-style EEC1 frame (priority 3, our demo
 * source address) carrying a fake, ramping engine speed value and transmits
 * it via HAL_CAN_AddTxMessage. In loopback mode this frame is looped straight
 * back into RX FIFO0, so CanParserTask above prints the decoded result. */
static void Can_SendDemoFrame(uint16_t simRpm)
{
  CAN_TxHeaderTypeDef txHeader;
  uint8_t txData[8] = { 0 };
  uint32_t txMailbox = 0U;
  uint32_t extId = 0U;
  uint16_t rawSpeed = (uint16_t)(simRpm * 8U);

  Can_EncodeJ1939Id(3U, (uint16_t)J1939_PGN_EEC1, CAN_SENDER_SOURCE_ADDR, &extId);

  txData[3] = (uint8_t)(rawSpeed & 0xFFU);
  txData[4] = (uint8_t)((rawSpeed >> 8) & 0xFFU);

  txHeader.ExtId = extId;
  txHeader.IDE = CAN_ID_EXT;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 8U;
  txHeader.TransmitGlobalTime = DISABLE;

  (void)HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox);
}
