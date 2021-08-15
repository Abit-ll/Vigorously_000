#ifndef __VIGOROUSLY_SMART_CAR_ULTRASONIC_RANGING_H
#define __VIGOROUSLY_SMART_CAR_ULTRASONIC_RANGING_H

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "bsp_abit_delay.h"

#define HC_SR04_TRIG_PIN        GPIO_Pin_12
#define HC_SR04_ECHO_PIN        GPIO_Pin_13

void vigorously_smart_car_ultrasonic_ranging_init(uint16_t prescaler, uint16_t period);

float vigorously_smart_car_ultrasonic_ranging();

#endif //__VIGOROUSLY_SMART_CAR_ULTRASONIC_RANGING_H