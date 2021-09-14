#ifndef __VIGOROUSLY_SMART_CAR_OLED_DISPLAY_H
#define __VIGOROUSLY_SMART_CAR_OLED_DISPLAY_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "bsp_abit_delay.h"

#define VIGOROUSLY_SMART_CAR_OLED_GPIO_CLOCK        RCC_AHB1Periph_GPIOC

#define VIGOROUSLY_SMART_CAR_OLED_SCLK_PIN          GPIO_Pin_0
#define VIGOROUSLY_SMART_CAR_OLED_SDA_PIN           GPIO_Pin_1
#define VIGOROUSLY_SMART_CAR_OLED_RST_PIN           GPIO_Pin_2
#define VIGOROUSLY_SMART_CAR_OLED_RS_PIN            GPIO_Pin_3
#define VIGOROUSLY_SMART_CAR_OLED_CS_PIN            GPIO_Pin_4

#define VIGOROUSLY_SMART_CAR_OLED_GPIOX             GPIOC

#define VIGOROUSLY_SMART_CAR_OLED_CMD               0
#define VIGOROUSLY_SMART_CAR_OLED_DATA              1

void vigorously_smart_car_oled_display_show_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);

void vigorously_smart_car_oled_display_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);

void vigorously_smart_car_oled_display_show_string(uint8_t x, uint8_t y, uint8_t *src, uint8_t size);

void vigorously_smart_car_oled_display_refresh_gram();

uint8_t vigorously_smart_car_oled_display_clear();

void vigorously_smart_car_oled_display_init();

#endif //__VIGOROUSLY_SMART_CAR_OLED_DISPLAY_H