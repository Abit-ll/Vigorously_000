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

extern struct Vigorously_Smart_Car_Recv_Info vigorously_wifi_info;

struct Vigorously_Smart_Car_Wifi_Info
{
    uint8_t vigorously_wifi_ssid[20];
    uint8_t vigorously_wifi_passwd[20];
};

typedef enum
{
    vigorously_wifi_disconnect = 0,
    vigorously_wifi_connect
} Vigorously_Wifi_Status;


extern struct Vigorously_Smart_Car_Wifi_Info vigorously_wifi_connect_info;
extern Vigorously_Wifi_Status vigorously_wifi_status;

void wigorously_smart_car_wifi_config(struct Vigorously_Smart_Car_Wifi_Info *wifi_connect_info);

#endif //__VIGOROUSLY_SMART_CAR_WIFI_H