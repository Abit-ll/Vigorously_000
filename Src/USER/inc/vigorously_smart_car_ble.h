#ifndef __VIGOROUSLY_SMART_CAR_BLE_H
#define __VIGOROUSLY_SMART_CAR_BLE_H

#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#include "bsp_aibt_printf.h"

<<<<<<< HEAD
extern uint16_t recv_buff[100];
extern uint8_t recv_len;

void vigorously_smart_car_ble_send(USART_TypeDef* USARTx, uint16_t *ch);

void vigorously_smart_car_ble_init(uint32_t baud);
=======
#define VIGOROUSLY_SMART_CAR_BLE_STATE_PIN              GPIO_Pin_2
#define VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX            GPIOE
#define VIGOROUSLY_SMART_CAR_BLE_STATE_CLOCK            RCC_AHB1Periph_GPIOE

#define VIGOROUSLY_SMART_CAR_BLE_USARTX                 USART3

extern uint8_t ble_recv_buff[35];
extern uint8_t ble_recv_len;

void vigorously_smart_car_ble_msg_proc(uint8_t *recv);

void vigorously_smart_car_ble_config();
>>>>>>> 5586841... add ble

#endif //__VIGOROUSLY_SMART_CAR_BLE_H