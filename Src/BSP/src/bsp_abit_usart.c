#include "bsp_abit_usart.h"

void bsp_abit_usart_send(USART_TypeDef* USARTx, uint8_t *ch)
{
    uint32_t i = 0;

    do
    {
        USART_SendData(USARTx, ch[i++]);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    } while (ch[i] != '\0');
}

void bsp_abit_usart_init(uint32_t baud)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /* GPIOX CLOCK */
    RCC_AHB1PeriphClockCmd(ABIT_DEBUG_USART_GPIO_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_BLE_USART3_GPIO_CLOCK, ENABLE);
    // RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_GSM_USART6_GPIO_CLOCK, ENABLE);

    /* USARTX CLOCK */
    RCC_APB2PeriphClockCmd(ABIT_DEBUG_USART_USART_CLOCK, ENABLE);
    RCC_APB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_WIFI_USART2_CLOCK, ENABLE);
    RCC_APB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_BLE_USART3_CLOCK, ENABLE); 
    // RCC_APB2PeriphClockCmd(VIGOROUSLY_SMART_CAR_GSM_USART6_CLOCK, ENABLE);

    GPIO_PinAFConfig(ABIT_DEBUG_USART_GPIOX, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(ABIT_DEBUG_USART_GPIOX, GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_WIFI_USART2_GPIOX, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_WIFI_USART2_GPIOX, GPIO_PinSource3, GPIO_AF_USART2);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_BLE_USART3_GPIOX, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_BLE_USART3_GPIOX, GPIO_PinSource11, GPIO_AF_USART3);

    // GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_GSM_USART6_GPIOX, GPIO_PinSource6, GPIO_AF_USART6);
    // GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_GSM_USART6_GPIOX, GPIO_PinSource7, GPIO_AF_USART6);

    GPIO_InitStruct.GPIO_Pin = ABIT_DEBUG_USART_TX | ABIT_DEBUG_USART_RX;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(ABIT_DEBUG_USART_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_WIFI_USART2_TX | VIGOROUSLY_SMART_CAR_WIFI_USART2_RX;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(VIGOROUSLY_SMART_CAR_WIFI_USART2_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_BLE_USART3_TX | VIGOROUSLY_SMART_CAR_BLE_USART3_RX;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(VIGOROUSLY_SMART_CAR_BLE_USART3_GPIOX, &GPIO_InitStruct);

    // GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_GSM_USART6_TX | VIGOROUSLY_SMART_CAR_GSM_USART6_RX;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_Init(VIGOROUSLY_SMART_CAR_GSM_USART6_GPIOX, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = baud;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;

    USART_Init(ABIT_DEBUG_USARTX, &USART_InitStruct);
    USART_Init(VIGOROUSLY_SMART_CAR_WIFI_USARTX, &USART_InitStruct);
    USART_Init(VIGOROUSLY_SMART_CAR_BLE_USARTX, &USART_InitStruct);
    // USART_Init(VIGOROUSLY_SMART_CAR_GSM_USARTX, &USART_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStruct);

    // NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
    // NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    // NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    // NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(ABIT_DEBUG_USARTX, USART_IT_RXNE, ENABLE);
    USART_ITConfig(VIGOROUSLY_SMART_CAR_WIFI_USARTX, USART_IT_RXNE, ENABLE);
    USART_ITConfig(VIGOROUSLY_SMART_CAR_BLE_USARTX, USART_IT_RXNE, ENABLE);
    USART_ITConfig(VIGOROUSLY_SMART_CAR_BLE_USARTX, USART_IT_IDLE, ENABLE);
    // USART_ITConfig(VIGOROUSLY_SMART_CAR_GSM_USARTX, USART_IT_RXNE, ENABLE);

    USART_Cmd(ABIT_DEBUG_USARTX, ENABLE);
    USART_Cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, ENABLE);
    USART_Cmd(VIGOROUSLY_SMART_CAR_BLE_USARTX, ENABLE);
    // USART_Cmd(VIGOROUSLY_SMART_CAR_GSM_USARTX, ENABLE);
}