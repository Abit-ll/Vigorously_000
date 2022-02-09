#ifndef __VIGOROUSLY_SMART_CAR_BLE_H
#define __VIGOROUSLY_SMART_CAR_BLE_H

#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#include "bsp_aibt_printf.h"

#include "vigorously_smart_car_wifi.h"

#define VIGOROUSLY_SMART_CAR_BLE_STATE_PIN              GPIO_Pin_2
#define VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX            GPIOE
#define VIGOROUSLY_SMART_CAR_BLE_STATE_CLOCK            RCC_AHB1Periph_GPIOE

#define VIGOROUSLY_SMART_CAR_BLE_USARTX                 USART3
#define BLE_RECV_LEN                                    35

extern struct Vigorously_Smart_Car_Recv_Info vigorously_ble_info;

void vigorously_smart_car_ble_msg_proc(uint8_t *recv);

void vigorously_smart_car_ble_config();

#endif //__VIGOROUSLY_SMART_CAR_BLE_H