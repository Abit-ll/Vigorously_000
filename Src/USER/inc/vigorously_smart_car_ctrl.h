#ifndef __VIGOROUSLY_SMART_CAR_CTRL_H
#define __VIGOROUSLY_SMART_CAR_CTRL_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "bsp_abit_delay.h"

#define VIGOROUSLY_MOTORA_PIN_1         GPIO_Pin_10
#define VIGOROUSLY_MOTORA_PIN_2         GPIO_Pin_11
#define VIGOROUSLY_MOTORB_PIN_1         GPIO_Pin_0
#define VIGOROUSLY_MOTORB_PIN_2         GPIO_Pin_1
#define VIGOROUSLY_MOTORC_PIN_1         GPIO_Pin_6
#define VIGOROUSLY_MOTORC_PIN_2         GPIO_Pin_7
#define VIGOROUSLY_MOTORD_PIN_1         GPIO_Pin_12
#define VIGOROUSLY_MOTORD_PIN_2         GPIO_Pin_13

void vigorously_smart_car_init(uint16_t period, uint16_t prescaler);

void vigorously_smart_car_move_forward();

void vigorously_smart_car_move_back();

void vigorously_smart_car_move_left();

void vigorously_smart_car_move_right();

void vigorously_smart_car_ctrl();

#endif //__VIGOROUSLY_SMART_CAR_CTRL_H