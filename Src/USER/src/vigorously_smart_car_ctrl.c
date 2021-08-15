#include "vigorously_smart_car_ctrl.h"

void vigorously_smart_car_init(uint16_t period, uint16_t prescaler)
{
    // GPIO_InitTypeDef GPIO_InitStruct;
    // TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    // TIM_OCInitTypeDef TIM_OCInitStruct;

    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);

    // GPIO_PinAFConfig(GPIOB, GPIO_PinSource10 | GPIO_PinSource11, GPIO_AF_TIM2);
    // GPIO_PinAFConfig(GPIOB, GPIO_PinSource0 | GPIO_PinSource1, GPIO_AF_TIM3);
    // GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORA_PIN_1 | VIGOROUSLY_MOTORA_PIN_2 |\
    //                             VIGOROUSLY_MOTORB_PIN_1 | VIGOROUSLY_MOTORB_PIN_2);
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    // GPIO_Init(GPIOB, &GPIO_InitStruct);

    // GPIO_PinAFConfig(GPIOC, GPIO_PinSource6 | GPIO_PinSource7, GPIO_AF_TIM3);
    // GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORC_PIN_1 | VIGOROUSLY_MOTORC_PIN_2);
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    // GPIO_Init(GPIOC, &GPIO_InitStruct);

    // GPIO_PinAFConfig(GPIOD, GPIO_PinSource12 | GPIO_PinSource13, GPIO_AF_TIM4);
    // GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORD_PIN_1 | VIGOROUSLY_MOTORD_PIN_2);
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    // GPIO_Init(GPIOD, &GPIO_InitStruct);

    // TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    // TIM_TimeBaseInitStruct.TIM_Period = period;
    // TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    // TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    // TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    // TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    // TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    // TIM_OC3Init(TIM2, &TIM_OCInitStruct);
    // TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    // TIM_OC4Init(TIM2, &TIM_OCInitStruct);
    // TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    // TIM_ARRPreloadConfig(TIM2, ENABLE);
    // TIM_Cmd(TIM2, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORA_PIN_1 | VIGOROUSLY_MOTORA_PIN_2 |\
                            VIGOROUSLY_MOTORB_PIN_1 | VIGOROUSLY_MOTORB_PIN_2);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORC_PIN_1 | VIGOROUSLY_MOTORC_PIN_2);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_MOTORD_PIN_1 | VIGOROUSLY_MOTORD_PIN_2);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void vigorously_smart_car_move_forward()
{
    GPIO_SetBits(GPIOB, (VIGOROUSLY_MOTORA_PIN_1 | VIGOROUSLY_MOTORB_PIN_1));
    GPIO_SetBits(GPIOC, VIGOROUSLY_MOTORC_PIN_2);
    GPIO_SetBits(GPIOD, VIGOROUSLY_MOTORD_PIN_2);
    GPIO_ResetBits(GPIOB, (VIGOROUSLY_MOTORA_PIN_2 | VIGOROUSLY_MOTORB_PIN_2));
    GPIO_ResetBits(GPIOC, VIGOROUSLY_MOTORC_PIN_1);
    GPIO_ResetBits(GPIOD, VIGOROUSLY_MOTORD_PIN_1);
}

void vigorously_smart_car_move_back()
{
    GPIO_SetBits(GPIOB, (VIGOROUSLY_MOTORA_PIN_2 | VIGOROUSLY_MOTORB_PIN_2));
    GPIO_SetBits(GPIOC, VIGOROUSLY_MOTORC_PIN_1);
    GPIO_SetBits(GPIOD, VIGOROUSLY_MOTORD_PIN_1);
    GPIO_ResetBits(GPIOB, (VIGOROUSLY_MOTORA_PIN_1 | VIGOROUSLY_MOTORB_PIN_1));
    GPIO_ResetBits(GPIOC, VIGOROUSLY_MOTORC_PIN_2);
    GPIO_ResetBits(GPIOD, VIGOROUSLY_MOTORD_PIN_2);
}

void vigorously_smart_car_move_left()
{

}

void vigorously_smart_car_move_right()
{

}

void vigorously_smart_car_ctrl()
{

}