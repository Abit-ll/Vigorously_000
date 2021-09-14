#include "bsp_abit_usart.h"

void bsp_abit_usart_send(USART_TypeDef* USARTx, uint16_t *ch)
{
    uint32_t i = 0;

    do
    {
        USART_SendData(USARTx, *ch);
    } while (*(ch + 1) != '\0');
}

void bsp_abit_usart_init(uint32_t baud)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_AHB1PeriphClockCmd(ABIT_DEBUG_USART_GPIO_CLOCK, ENABLE);
    RCC_APB2PeriphClockCmd(ABIT_DEBUG_USART_USART_CLOCK, ENABLE);

    GPIO_PinAFConfig(ABIT_DEBUG_USART_GPIOX, GPIO_PinSource9 | GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_InitStruct.GPIO_Pin = ABIT_DEBUG_USART_TX | ABIT_DEBUG_USART_RX;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(ABIT_DEBUG_USART_GPIOX, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = baud;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;

    USART_Init(ABIT_DEBUG_USARTX, &USART_InitStruct);

    USART_Cmd(ABIT_DEBUG_USARTX, ENABLE);
}