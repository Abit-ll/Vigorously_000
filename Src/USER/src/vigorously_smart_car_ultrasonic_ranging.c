#include "vigorously_smart_car_ultrasonic_ranging.h"

void vigorously_smart_car_ultrasonic_ranging_init(uint16_t period, uint16_t prescaler)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    GPIO_InitStruct.GPIO_Pin = HC_SR04_TRIG_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = HC_SR04_ECHO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStruct.TIM_Period = period;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);

    // TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

    // NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
    // NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    // NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    // NVIC_Init(&NVIC_InitStruct);
}

float vigorously_smart_car_ultrasonic_ranging()
{
    uint32_t count;
    float dist;

    GPIO_ResetBits(GPIOB, HC_SR04_TRIG_PIN);
    GPIO_SetBits(GPIOB, HC_SR04_TRIG_PIN);
    bsp_abit_delay_ms(20);
    GPIO_ResetBits(GPIOB, HC_SR04_TRIG_PIN);
    TIM_SetCounter(TIM5, 0);

    while(!GPIO_ReadInputDataBit(GPIOB, HC_SR04_ECHO_PIN));
    TIM_Cmd(TIM5, ENABLE);
    while(GPIO_ReadInputDataBit(GPIOB, HC_SR04_ECHO_PIN));
    TIM_Cmd(TIM5, DISABLE);
    count = TIM_GetCounter(TIM5);
    printf("count = %d\r\n", count);

    dist = (float)count * 0.034 / 2;

    return dist;
}