#ifndef __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H
#define __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_fsmc.h"

#include "bsp_abit_delay.h"

#include "vigorously_smart_car_fonts.h"

typedef struct lcd_display
{
    uint8_t vigorously_smart_car_display_scan_mode;
    uint16_t vigorously_smart_car_display_x_length;
    uint16_t vigorously_smart_car_display_y_length;
    uint16_t vigorously_smart_car_display_current_text_color;
    uint16_t vigorously_smart_car_display_current_back_color;
} vigorously_smart_car_lcd_param;

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD               ((uint32_t)0x6C000000)
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DATA              ((uint32_t)0x6C000000 | (1 << (6 + 1)))

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_CLOCK          RCC_AHB1Periph_GPIOB
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_RD_WR_CLOCK     RCC_AHB1Periph_GPIOD
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_CLOCK           RCC_AHB1Periph_GPIOE
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RS_CLOCK          RCC_AHB1Periph_GPIOF
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CS_TFT_CLOCK      RCC_AHB1Periph_GPIOG
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_FSMC_CLOCK        RCC_AHB3Periph_FSMC

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_GPIOX          GPIOB
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_RD_WR_GPIOX     GPIOD
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_GPIOX           GPIOE
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RS_GPIOX          GPIOF
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CS_TFT_GPIOX      GPIOG

#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D00_PIN          GPIO_Pin_14
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D01_PIN          GPIO_Pin_15
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D02_PIN          GPIO_Pin_0
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D03_PIN          GPIO_Pin_1
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D04_PIN          GPIO_Pin_7
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D05_PIN          GPIO_Pin_8
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D06_PIN          GPIO_Pin_9
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D07_PIN          GPIO_Pin_10
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D08_PIN          GPIO_Pin_11
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D09_PIN          GPIO_Pin_12
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D10_PIN          GPIO_Pin_13
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D11_PIN          GPIO_Pin_14
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D12_PIN          GPIO_Pin_15
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D13_PIN          GPIO_Pin_8
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D14_PIN          GPIO_Pin_9
#define  VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D15_PIN          GPIO_Pin_10

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RD_PIN            GPIO_Pin_4
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_WR_PIN            GPIO_Pin_5
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RS_PIN            GPIO_Pin_12
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CS_TFT_PIN        GPIO_Pin_12
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_PIN            GPIO_Pin_15


#define VIGOROUSLY_SMART_CAR_DISPLAY_WHITE                  0xFFFF
#define VIGOROUSLY_SMART_CAR_DISPLAY_BLACK                  0x0000
#define VIGOROUSLY_SMART_CAR_DISPLAY_GREY                   0xF7DE
#define VIGOROUSLY_SMART_CAR_DISPLAY_BLUE                   0x001F
#define VIGOROUSLY_SMART_CAR_DISPLAY_BLUE2                  0x051F
#define VIGOROUSLY_SMART_CAR_DISPLAY_RED                    0xF800
#define VIGOROUSLY_SMART_CAR_DISPLAY_MAGENTA                0xF81F
#define VIGOROUSLY_SMART_CAR_DISPLAY_GREEN                  0x07E0
#define VIGOROUSLY_SMART_CAR_DISPLAY_CYAN                   0x7FFF
#define VIGOROUSLY_SMART_CAR_DISPLAY_YELLOW                 0xFFE0
#define VIGOROUSLY_SMART_CAR_DISPLAY_BRED                   0xF81F
#define VIGOROUSLY_SMART_CAR_DISPLAY_GRED                   0xFFE0
#define VIGOROUSLY_SMART_CAR_DISPLAY_GBLUE                  0x07FF
#define VIGOROUSLY_SMART_CAR_DISPLAY_BACKGROUND             VIGOROUSLY_SMART_CAR_DISPLAY_BLACK

#define VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_X        0x2A
#define VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_Y        0x2B
#define VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL          0x2C

#define VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL             240     /* 液晶屏幕较短方向的像素宽度 */
#define VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL             320     /* 液晶屏幕较长方向的像素宽度 */

#define VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START        0       /* 起始点坐标 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START        0       /* 起始点坐标 */

extern vigorously_smart_car_lcd_param vigorously_smart_car_lcd;

void vigorously_smart_car_lcd_write_cmd(uint16_t cmd);

uint16_t vigorously_smart_car_lcd_read_data();

void vigorously_smart_car_lcd_write_data(uint16_t data);

void vigorously_smart_car_lcd_display_open_window(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

vigorously_smart_car_fonts *vigorously_smart_car_dislpay_get_font();

void vigorously_smart_car_dislpay_set_font(vigorously_smart_car_fonts *font);

void vigorously_smart_car_dislpay_get_color(uint16_t *textcolor, uint16_t *backcolor);

void vigorously_smart_car_dislpay_set_color(uint16_t textcolor, uint16_t backcolor);

void vigorously_smart_car_lcd_display_fill_color(uint32_t point, uint16_t color);

void vigorously_smart_car_lcd_display_gram_scan(uint8_t option);

void vigorously_smart_car_lcd_display_en(uint16_t line, uint8_t *pstr);

void vigorously_smart_car_lcd_display_clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

void vigorously_smart_car_lcd_display_clear_line(uint16_t line, uint16_t color);

void vigorously_smart_car_lcd_init(vigorously_smart_car_fonts *font);

#endif //__VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H