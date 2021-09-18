#ifndef __VIGOROUSLY_SMART_CAR_WIFI_H
#define __VIGOROUSLY_SMART_CAR_WIFI_H

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

typedef enum
{
    Manual_Mode = 0,
    Auto_Mode
} Smart_Car_Mode;

extern Smart_Car_Mode vigorously_smart_car_mode;

#endif //__VIGOROUSLY_SMART_CAR_WIFI_H