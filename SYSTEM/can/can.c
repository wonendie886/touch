/* ============================= can.c ================================= */

#include "can.h"

// internal handle
static CAN_HandleTypeDef hcan;
static CanTxMsgTypeDef txMsg;
static CanRxMsgTypeDef rxMsg;

HAL_StatusTypeDef CAN_Init_IT(uint32_t bitrate_bps)
{
    // Hardcoded configuration for 500kbps on PCLK1 = 42 MHz
    // Prescaler = 4, SJW = 1TQ, BS1 = 16TQ, BS2 = 4TQ -> total TQ = 21
    (void)bitrate_bps; // parameter unused in hardcoded mode

    hcan.Instance = CAN_INSTANCE;
    hcan.Init.Prescaler = 4;
    hcan.Init.Mode = CAN_MODE_NORMAL;

    // SJW: 1 TQ
#ifdef CAN_SJW_1TQ
    hcan.Init.SJW = CAN_SJW_1TQ;
#else
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
#endif

    // BS1 = 16 TQ
#ifdef CAN_BS1_16TQ
    hcan.Init.BS1 = CAN_BS1_16TQ;
#else
    hcan.Init.TimeSeg1 = CAN_BS1_16TQ;
#endif

    // BS2 = 4 TQ
#ifdef CAN_BS2_4TQ
    hcan.Init.BS2 = CAN_BS2_4TQ;
#else
    hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
#endif

    // legacy control flags (CubeMX typical)
#ifdef TTCM
    hcan.Init.TTCM = DISABLE;
#endif
#ifdef ABOM
    hcan.Init.ABOM = DISABLE;
#endif
#ifdef AWUM
    hcan.Init.AWUM = DISABLE;
#endif
#ifdef NART
    hcan.Init.NART = DISABLE; // retransmission enabled
#endif
#ifdef RFLM
    hcan.Init.RFLM = DISABLE;
#endif
#ifdef TXFP
    hcan.Init.TXFP = DISABLE;
#endif

    // link pTx/pRx message buffers expected by legacy HAL
    hcan.pTxMsg = &txMsg;
    hcan.pRxMsg = &rxMsg;

    return HAL_CAN_Init(&hcan);
}

HAL_StatusTypeDef CAN_ConfigFilterAcceptAll(void)
{
    CAN_FilterConfTypeDef sFilterConfig;

    ///set filter id
    uint32_t ExtId = 0x00000061;

    sFilterConfig.FilterNumber = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = (ExtId >> 13) & 0xFFFF;  // 高16位：ID[28:13]
    sFilterConfig.FilterIdLow = ((ExtId & 0x1FFF) << 3) | CAN_ID_EXT; // 低16位：ID[12:0] + 扩展ID标志
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x07F8 | 0x0004; // 低13位全匹配，IDE位必须匹配扩展ID
    sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
#ifdef __HAL_RCC_CAN2_CLK_ENABLE
    sFilterConfig.BankNumber = 14; // harmless default for single CAN
#endif

    return HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
}

HAL_StatusTypeDef CAN_StartReceive_IT(void)
{
    return HAL_CAN_Receive_IT(&hcan, CAN_FIFO0);
}

HAL_StatusTypeDef CAN_Transmit_IT(uint32_t id, uint8_t *data, uint8_t len)
{
    if (len > 8) len = 8;

    // Fill legacy tx message
    hcan.pTxMsg->StdId = id;
    hcan.pTxMsg->ExtId = id;
    hcan.pTxMsg->IDE = CAN_Id_Extended; // legacy macro
    hcan.pTxMsg->RTR = CAN_RTR_DATA;
    hcan.pTxMsg->DLC = len;
    for (uint8_t i = 0; i < len; i++) hcan.pTxMsg->Data[i] = data[i];
    for (uint8_t i = len; i < 8; i++) hcan.pTxMsg->Data[i] = 0x00;

    return HAL_CAN_Transmit_IT(&hcan);
}

/** Minimal MSP init so CubeMX is not required. If you use your own MSP, remove/modify this.
 *  This sets PA11/PA12 as AF9 (CAN1) and enables NVIC for CAN1_RX0 and CAN1_SCE.
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable peripheral clocks
    __HAL_RCC_CAN1_CLK_ENABLE();

    // GPIO clock for PA11/PA12
    if (CAN_GPIO_PORT == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (CAN_GPIO_PORT == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (CAN_GPIO_PORT == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure CAN TX/RX pins (AF PP)
    GPIO_InitStruct.Pin = CAN_TX_PIN | CAN_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = CAN_GPIO_AF;
    HAL_GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStruct);

    // NVIC: FIFO0 RX IRQ
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);

    // NVIC: SCE (status / error) IRQ
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{
    HAL_GPIO_DeInit(CAN_GPIO_PORT, CAN_TX_PIN | CAN_RX_PIN);
    __HAL_RCC_CAN1_CLK_DISABLE();
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
}

void CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}

void CAN1_SCE_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}
void can0SendWeightTestValve(uint16_t data,uint16_t data2)
{
    uint32_t id = (0x000000FF & ((WEIGHTID & 0x0F) << 0)) | ((GRINDID & 0x0F) << 4);
    uint8_t len = 5;
    uint8_t data_send[5] = {0};

    data_send[0] = (uint8_t)(data & 0xFF);
    data_send[1] = (uint8_t)((data >> 8) & 0xFF);
    data_send[2] = 0;
    data_send[3] = (uint8_t)(data2 & 0xFF);
    data_send[4] = (uint8_t)((data2 >> 8) & 0xFF);

    uint8_t crc = 0;
    for(uint8_t i = 0; i < len; i++){
        crc += data_send[i];
    }

    id = id | (FUNC_WEIGHINGDATA << 8 & 0xFF00);
    id = id | ((crc << 16) & 0xFF0000);

    CAN_Transmit_IT(id,data_send,len);
}

// void can0SendWeightTestValve(uint16_t data,uint16_t data2)
// {
//     // 初始化CAN发送消息结构体
//     can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &CanTransmitMsg); 

//     // 构造扩展帧标识符
//     CanTransmitMsg.tx_efid = (0x000000FF & ((WEIGHTID & 0x0F) << 0)) | ((GRINDID & 0x0F) << 4);
    
//     // 设置消息类型为数据帧
//     CanTransmitMsg.tx_ft = CAN_FT_DATA; 
    
//     // 设置帧格式为扩展帧
//     CanTransmitMsg.tx_ff = CAN_FF_EXTENDED; 
    
//     // 设置数据长度为4字节
//     CanTransmitMsg.tx_dlen = 5; 
    
//     // 填充数据字段
//     CanTransmitMsg.tx_data[0] = (uint8_t)(data & 0xFF);
//     CanTransmitMsg.tx_data[1] = (uint8_t)((data >> 8) & 0xFF);
//     CanTransmitMsg.tx_data[2] = 0;
//     CanTransmitMsg.tx_data[3] = (uint8_t)(data2 & 0xFF);
//     CanTransmitMsg.tx_data[4] = (uint8_t)((data2 >> 8) & 0xFF);

//     // 计算CRC校验值
//     uint8_t crc = 0;
//     for(uint8_t i = 0; i < CanTransmitMsg.tx_dlen; i++){
//         crc += CanTransmitMsg.tx_data[i];
//     }
    
//     // 将CRC值加入扩展帧标识符
//     CanTransmitMsg.tx_efid = CanTransmitMsg.tx_efid | (FUNC_WEIGHINGDATA << 8 & 0xFF00);
//     CanTransmitMsg.tx_efid = CanTransmitMsg.tx_efid | ((crc << 16) & 0xFF0000);
    
//     // 发送CAN消息
//     can_message_transmit(CAN0, &CanTransmitMsg);
// }


void sendHeartBeat(uint8_t status)
{
    uint32_t id = (0x000000FF & ((GRIND_HMI_ID & 0x0F) << 0)) | ((HmiId & 0x0F) << 4);
    uint8_t len = 1;
    uint8_t data[1] = {status};

    uint8_t crc = 0;
    for(uint8_t i = 0; i < len; i++){
        crc += data[i];
    }

    id = id | (GRIND_HMI_ID_HEART_BEAT << 8 & 0xFF00);
    id = id | ((crc << 16) & 0xFF0000);

    CAN_Transmit_IT(id,data,len);
}

uint8_t getSrcId(uint32_t canId)
{
    return (canId & 0xF);
}
uint8_t getDestId(uint32_t canId)
{
    return ((canId >> 4) & 0xF);
}

uint8_t getCmdType(uint32_t canId)
{
    return ((canId >>8) & 0xFF);
}
uint8_t getCrc(uint32_t canId)
{
    return ((canId >> 16) & 0xFF);
}