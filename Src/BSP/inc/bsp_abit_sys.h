#ifndef __BSP_ABIT_SYS_H
#define __BSP_ABIT_SYS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stm32f4xx_usart.h"

#include "bsp_abit_delay.h"
#include "bsp_abit_led.h"
#include "bsp_abit_usart.h"

#include "vigorously_smart_car_ble.h"
#include "vigorously_smart_car_wifi.h"
#include "vigorously_smart_car_lcd_display.h"
#include "vigorously_smart_car_camera.h"

#define VIGOROUSLY_RECV_LEN                     40

struct Vigorously_Smart_Car_Recv_Info
{
    uint8_t vigorously_recv_len;
    uint8_t vigorously_recv_flag;
    uint8_t *vigorously_recv_buff;
};

uint8_t bsp_abit_char_2_hex(uint8_t *src);

uint8_t bsp_abit_hex_2_char(uint8_t *src);

void bsp_abit_set_recv_buff(struct Vigorously_Smart_Car_Recv_Info *recv_info, uint8_t size);

void bsp_abit_reset_recv_buff(struct Vigorously_Smart_Car_Recv_Info *recv_info, uint8_t size);

uint8_t bsp_abit_string_cpy(uint8_t *src, uint8_t *desc, uint8_t *obj, uint8_t *end, uint8_t srclen);

uint8_t bsp_abit_string_search(uint8_t *src, uint8_t *obj, uint8_t srclen);

uint8_t bsp_abit_send_at_cmd(USART_TypeDef *usartx, uint8_t *cmd, uint8_t *relay, uint8_t size, struct Vigorously_Smart_Car_Recv_Info *recv_info);

void bsp_abit_sys_init();

#endif //__BSP_ABIT_SYS_H