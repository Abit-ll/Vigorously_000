#ifndef __VIGOROUSLY_SMART_CAR_ULTRASONIC_H
#define __VIGOROUSLY_SMART_CAR_ULTRASONIC_H

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "bsp_abit_delay.h"

#define VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIO_CLOCK      RCC_AHB1Periph_GPIOB
#define VIGOROUSLY_SMART_CAR_ULTRASONIC_TIM_CLOCK       RCC_APB1Periph_TIM5

#define VIGOROUSLY_SMART_CAR_ULTRASONIC_TRIG_PIN        GPIO_Pin_12
#define VIGOROUSLY_SMART_CAR_ULTRASONIC_ECHO_PIN        GPIO_Pin_13

#define VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX           GPIOB

#define VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX            TIM5

void vigorously_smart_car_double_2_char(float num, uint8_t *src, uint8_t len);

float vigorously_smart_car_ultrasonic_get_distance();

void vigorously_smart_car_ultrasonic_init(uint16_t prescaler, uint16_t period);

#endif //__VIGOROUSLY_SMART_CAR_ULTRASONIC_H