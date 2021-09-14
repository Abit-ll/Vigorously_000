#ifndef __VIGOROUSLY_SMART_CAR_WIFI_H
#define __VIGOROUSLY_SMART_CAR_WIFI_H

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#define VIGOROUSLY_SMART_CAR_ESP8266_GPIO_CLOCK         RCC_AHB1Periph_GPIOB
#define VIGOROUSLY_SMART_CAR_ESP8266_USART_CLOCK        RCC_APB1Periph_USART3

#define VIGOROUSLY_SMART_CAR_ESP8266_TX_PIN             GPIO_Pin_10
#define VIGOROUSLY_SMART_CAR_ESP8266_RX_PIN             GPIO_Pin_11

#define VIGOROUSLY_SMART_CAR_ESP8266_GPIOX              GPIOB

#define VIGOROUSLY_SMART_CAR_ESP8266_USARTX             USART3

typedef enum
{
    Manual_Mode = 0,
    Auto_Mode
} Smart_Car_Mode;

extern Smart_Car_Mode vigorously_smart_car_mode;

void vigorously_smart_car_wifi_init(uint16_t baudrate);

#endif //__VIGOROUSLY_SMART_CAR_WIFI_H