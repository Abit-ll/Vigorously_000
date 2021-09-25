#ifndef __VIGOROUSLY_SMART_CAR_WIFI_H
#define __VIGOROUSLY_SMART_CAR_WIFI_H

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#include "bsp_abit_sys.h"
#include "bsp_abit_delay.h"

#define VIGOROUSLY_SMART_CAR_WIFI_USART         USART2

typedef enum
{
    Manual_Mode = 1,
    Auto_Mode
} Vigorously_Smart_Car_Mode;

typedef enum
{
    Move = 1,
    Ctrl_Type,
    Camera,
    Speed
}Vigorously_Smart_Car_Cmd_Type;

extern Vigorously_Smart_Car_Mode vigorously_smart_car_mode;

extern uint8_t wifi_send_buff[20];
extern uint8_t wifi_recv_buff[100];
extern uint8_t *vigorously_smart_car_ip;

extern uint8_t wifi_recv_len;

void vigorously_smart_car_wifi_reset_recv_buff();

void vigorously_smart_car_wifi_config();

#endif //__VIGOROUSLY_SMART_CAR_WIFI_H