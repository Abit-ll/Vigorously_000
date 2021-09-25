#ifndef __VIGOROUSLY_SMART_CAR_CTRL_H
#define __VIGOROUSLY_SMART_CAR_CTRL_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "bsp_abit_delay.h"

#include "vigorously_smart_car_wifi.h"

typedef enum
{
    go_stop = 0,
    move_forward,
    move_back,
    move_left,
    move_right
} Vigorously_Smart_Car_Direction;

#define VIGOROUSLY_SMART_CAR_MOTOR_GPIO_CLOCK          (RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB)
#define VIGOROUSLY_SMART_CAR_MOTOR_TIM_CLOCK           (RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4)
/* MOTORA */
#define VIGOROUSLY_SMART_CAR_MOTORA_PIN_1               GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_MOTORA_PIN_2               GPIO_Pin_7

#define VIGOROUSLY_SMART_CAR_MOTOR_LEFT_GPIOX           GPIOA

/* MOTORB */
#define VIGOROUSLY_SMART_CAR_MOTORB_PIN_1               GPIO_Pin_0
#define VIGOROUSLY_SMART_CAR_MOTORB_PIN_2               GPIO_Pin_1

#define VIGOROUSLY_SMART_CAR_MOTOR_LEFT_TIMX            TIM3

/* MOTORC */
#define VIGOROUSLY_SMART_CAR_MOTORC_PIN_1               GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_MOTORC_PIN_2               GPIO_Pin_7
/* MOTORD */
#define VIGOROUSLY_SMART_CAR_MOTORD_PIN_1               GPIO_Pin_8
#define VIGOROUSLY_SMART_CAR_MOTORD_PIN_2               GPIO_Pin_9

#define VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_GPIOX          GPIOB

#define VIGOROUSLY_SMART_CAR_MOTOR_RIGHT_TIMX           TIM4

void vigorously_smart_car_ctrl_init(uint16_t period, uint16_t prescaler);

void vigorously_smart_car_move_forward(uint16_t speed);

void vigorously_smart_car_move_back(uint16_t speed);

void vigorously_smart_car_move_left(uint16_t speed);

void vigorously_smart_car_move_right(uint16_t speed);

void vigorously_smart_car_stop(uint16_t speed);

#endif //__VIGOROUSLY_SMART_CAR_CTRL_H