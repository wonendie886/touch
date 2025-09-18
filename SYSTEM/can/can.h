/*
 * can.h / can.c for STM32F4 (STM32F407VET6)
 * HAL library compatible with legacy HAL CAN driver (STM32CubeF4 HAL v1.7.0)
 * Mode: Interrupt-based (HAL_CAN_Receive_IT / HAL_CAN_Transmit_IT)
 * Default pins: PA11 = CAN_RX, PA12 = CAN_TX (CAN1 AF9)
 * Does NOT require CubeMX. Drop these two files into your project and include "can.h".
 *
 * Features:
 *  - Auto computes Prescaler using HAL_RCC_GetPCLK1Freq() for requested bitrate (best-effort).
 *  - Uses legacy HAL APIs available in HAL v1.7.0: HAL_CAN_Init, HAL_CAN_ConfigFilter,
 *    HAL_CAN_Start, HAL_CAN_Receive_IT, HAL_CAN_Transmit_IT.
 *  - Implements HAL_CAN_MspInit to initialize GPIO & NVIC (can be commented out if you
 *    use your own MSP init).
 *  - Provides weak user callbacks: CAN_UserRxCb(...) and CAN_UserTxCb(void) to override.
 *
 * Notes / Caveats:
 *  - This code uses the legacy CanTxMsgTypeDef / CanRxMsgTypeDef and sets hcan.pTxMsg / pRxMsg
 *    because older HAL versions expect these to be non-NULL.
 *  - HAL_CAN_Transmit_IT / HAL_CAN_Receive_IT use HAL internal locking; if you encounter
 *    HAL_BUSY on rearming, consider using a small queue and rearming from main context.
 *  - Ensure you have a CAN transceiver on the board (e.g. MCP2551 / TJA104x) and 120Ω
 *    terminators on the bus ends.
 */

#ifndef _CAN_H_
#define _CAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdint.h>

// ----- Change these if your hardware differs -----
#ifndef CAN_INSTANCE
#define CAN_INSTANCE             CAN1
#endif

#ifndef CAN_GPIO_PORT
#define CAN_GPIO_PORT            GPIOA
#endif
#ifndef CAN_RX_PIN
#define CAN_RX_PIN               GPIO_PIN_11
#endif
#ifndef CAN_TX_PIN
#define CAN_TX_PIN               GPIO_PIN_12
#endif
#ifndef CAN_GPIO_AF
#define CAN_GPIO_AF              GPIO_AF9_CAN1
#endif

#ifndef CAN_Id_Standard
#define CAN_Id_Standard   ((uint8_t)0x00U)  /* 标准帧标识（IDE = 0） */
#endif

#ifndef CAN_Id_Extended
#define CAN_Id_Extended   ((uint8_t)0x04U)  /* 扩展帧标识（IDE = 1 -> 用 0x04 表示在老版定义里） */
#endif

// ----- API -----
/** Initialize CAN peripheral for interrupt mode at requested bitrate.
 *  Attempts to auto-select Prescaler based on PCLK1 and chosen sample point
 *  (uses SJW=1, BS1=13TQ, BS2=2TQ -> total 16 TQ). Returns HAL_OK on success.
 *  Note: actual bitrate may differ slightly due to integer prescaler rounding.
 */
HAL_StatusTypeDef CAN_Init_IT(uint32_t bitrate_bps);

/** Configure a permissive filter (accept all into FIFO0). */
HAL_StatusTypeDef CAN_ConfigFilterAcceptAll(void);

/** Start CAN and enable receive interrupt on FIFO0. */
HAL_StatusTypeDef CAN_StartReceive_IT(void);

/** Transmit a standard 11-bit frame via interrupt. Returns HAL status. */
HAL_StatusTypeDef CAN_TransmitStd_IT(uint16_t stdId, uint8_t *data, uint8_t len);

/** User-overridable callback for received frames.
 *  Override this function in your application to handle incoming frames.
 *  Parameters:
 *    is_ext: 1 if extended ID (29-bit), 0 if standard (11-bit)
 *    id: ID value (stdId or extId)
 *    dlc: data length (0..8)
 *    data: pointer to 8-byte buffer
 */
__weak void CAN_UserRxCb(uint8_t is_ext, uint32_t id, uint8_t dlc, uint8_t data[8]);

/** User-overridable callback called when TX completes (interrupt mode).
 *  Override in your app if you want TX completion notification.
 */
__weak void CAN_UserTxCb(void);

#ifdef __cplusplus
}
#endif

#endif // _CAN_LEGACY_H_



