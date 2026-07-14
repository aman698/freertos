/**
 ******************************************************************************
 * EXAMPLE 14 - main.c USER CODE snippets
 * CAN1 filter/start setup + RX FIFO0 ISR callback (ISR-side of the
 * ISR -> queue -> CanParserTask deferral; see freertos.c for the task).
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
extern CAN_HandleTypeDef hcan1;
extern void Can_ISR_SendFrameFromISR(CAN_RxHeaderTypeDef *rxHeader, uint8_t *rxData);
/* USER CODE END PV */

/* USER CODE BEGIN 2 */
{
  /* Accept every extended ID into FIFO0 - fine for a loopback demo where
   * we control both ends. A real bus listener would narrow this mask to
   * the PGNs it actually cares about. */
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

  (void)HAL_CAN_ConfigFilter(&hcan1, &canFilter);
  (void)HAL_CAN_Start(&hcan1);
  (void)HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}
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
