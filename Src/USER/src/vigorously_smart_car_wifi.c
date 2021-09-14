#include "vigorously_smart_car_wifi.h"

Smart_Car_Mode vigorously_smart_car_mode;

void vigorously_smart_car_wifi_init(uint16_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_ESP8266_GPIO_CLOCK, ENABLE);
    RCC_APB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_ESP8266_USART_CLOCK, ENABLE);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_ESP8266_GPIOX, GPIO_PinSource10 | GPIO_PinSource11, GPIO_AF_USART3);
    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_ESP8266_TX_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_ESP8266_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_ESP8266_RX_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_ESP8266_GPIOX, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = baudrate;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(VIGOROUSLY_SMART_CAR_ESP8266_USARTX, &USART_InitStruct);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(VIGOROUSLY_SMART_CAR_ESP8266_USARTX, USART_IT_RXNE, ENABLE);
    USART_Cmd(VIGOROUSLY_SMART_CAR_ESP8266_USARTX, ENABLE);
}