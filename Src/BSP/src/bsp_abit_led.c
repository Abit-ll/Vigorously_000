#include "bsp_abit_led.h"

void bsp_abit_led_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(ABIT_LED_GPIO_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = ABIT_LED1_GPIO_PIN | ABIT_LED2_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(ABIT_LED_GPIOX, &GPIO_InitStruct);

    ABIT_LED1_OFF;
    ABIT_LED2_OFF;
}