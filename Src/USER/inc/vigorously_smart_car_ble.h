#ifndef __VIGOROUSLY_SMART_CAR_BLE_H
#define __VIGOROUSLY_SMART_CAR_BLE_H

#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#include "bsp_aibt_printf.h"

extern uint16_t recv_buff[100];
extern uint8_t recv_len;

void vigorously_smart_car_ble_send(USART_TypeDef* USARTx, uint16_t *ch);

void vigorously_smart_car_ble_init(uint32_t baud);

#endif //__VIGOROUSLY_SMART_CAR_BLE_H