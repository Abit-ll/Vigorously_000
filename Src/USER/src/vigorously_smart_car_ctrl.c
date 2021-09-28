#include "vigorously_smart_car_ctrl.h"

void vigorously_smart_car_ctrl_init(uint16_t period, uint16_t prescaler)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_MOTOR_GPIO_CLOCK, ENABLE);
    RCC_APB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_MOTOR_TIM_CLOCK, ENABLE);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_GPIOX, GPIO_PinSource6 | GPIO_PinSource7, GPIO_AF_TIM3);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_GPIOX, GPIO_PinSource8 | GPIO_PinSource9, GPIO_AF_TIM3);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_GPIOX, GPIO_PinSource12 | GPIO_PinSource13 | GPIO_PinSource14 | GPIO_PinSource15, GPIO_AF_TIM4);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_MOTORA_PIN_1 | VIGOROUSLY_SMART_CAR_MOTORA_PIN_2);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_MOTORB_PIN_1 | VIGOROUSLY_SMART_CAR_MOTORB_PIN_2 |\
                                VIGOROUSLY_SMART_CAR_MOTORC_PIN_1 | VIGOROUSLY_SMART_CAR_MOTORC_PIN_2 |\
                                VIGOROUSLY_SMART_CAR_MOTORD_PIN_1 | VIGOROUSLY_SMART_CAR_MOTORD_PIN_2);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_GPIOX, &GPIO_InitStruct);

    TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStruct.TIM_Period = period;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, &TIM_TimeBaseInitStruct);
    TIM_TimeBaseInit(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, TIM_OCPreload_Enable);
    TIM_OC2Init(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, TIM_OCPreload_Enable);
    TIM_OC3Init(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, TIM_OCPreload_Enable);
    TIM_OC4Init(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, TIM_OCPreload_Enable);

    TIM_OC1Init(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, TIM_OCPreload_Enable);
    TIM_OC2Init(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, TIM_OCPreload_Enable);
    TIM_OC3Init(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, TIM_OCPreload_Enable);
    TIM_OC4Init(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, ENABLE);
    TIM_ARRPreloadConfig(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, ENABLE);
    TIM_Cmd(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, ENABLE);
    TIM_Cmd(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, ENABLE);
}

void vigorously_smart_car_move_forward(uint16_t speed)
{
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
}

void vigorously_smart_car_move_back(uint16_t speed)
{
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
}

void vigorously_smart_car_move_left(uint16_t speed)
{
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, (speed - 100));
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, (speed - 100));
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
}

void vigorously_smart_car_move_right(uint16_t speed)
{
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, 0);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, (speed - 100));
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, (speed - 100));
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, 0);
}

void vigorously_smart_car_stop(uint16_t speed)
{
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX, speed);
    TIM_SetCompare1(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare2(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare3(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
    TIM_SetCompare4(VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX, speed);
}