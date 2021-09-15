#ifndef __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H
#define __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_fsmc.h"

#include "bsp_abit_delay.h"

#include "vigorously_smart_car_lcd_display_font.h"
#include "vigorously_smart_car_ultrasonic.h"

/* 
 * FSMC分为4个BANK，每个BANK有4 * 64MB = 256MB
 * FSMC_Bank1_NORSRAM1: 0x60000000 ~ 0x63FFFFFFF
 * FSMC_Bank1_NORSRAM2: 0x64000000 ~ 0x67FFFFFFF
 * FSMC_Bank1_NORSRAM3: 0x68000000 ~ 0x6BFFFFFFF
 * FSMC_Bank1_NORSRAM4: 0x6C000000 ~ 0x6FFFFFFFF
 * FSMC_Bank1_NORSRAM1连接TFT，地址范围为0x60000000 ~ 0x63FFFFFF
 * FSMC_A16连接LCD的DC引脚
 * 寄存器基地址为0x60000000
 * 16位的数据访问方式，HADDR与FSMC_A的地址线连接关系会左移一位，
 * 如HADDR1与FSMC_A0对应，HADDR2与FSMC_A1对应，
 * 要使FSMC_A16地址线为高电平，实际访问内部HADDR地址的第（16 + 1）位，0x60000000 | (1 << (16 + 1))
 * 要使FSMC_A16地址线位低电平，实际访问内部HADDR地址的第（16 + 1）位，0x60000000 & (~(1 << (16 + 1)))
 */

/* FSCM_Bank1_NORSRAM1命令操作 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD                               ((uint32_t)0x60000000)
/* FSCM_Bank1_NORSRAM1数据操作 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DATA                              ((uint32_t)0x60000000 | (1 << (16 + 1)))

/* 数据 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D00_PIN                           GPIO_Pin_14
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D01_PIN                           GPIO_Pin_15
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D02_PIN                           GPIO_Pin_0
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D03_PIN                           GPIO_Pin_1
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D04_PIN                           GPIO_Pin_7
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D05_PIN                           GPIO_Pin_8
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D06_PIN                           GPIO_Pin_9
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D07_PIN                           GPIO_Pin_10
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D08_PIN                           GPIO_Pin_11
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D09_PIN                           GPIO_Pin_12
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D10_PIN                           GPIO_Pin_13
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D11_PIN                           GPIO_Pin_14
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D12_PIN                           GPIO_Pin_15
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D13_PIN                           GPIO_Pin_8
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D14_PIN                           GPIO_Pin_9
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D15_PIN                           GPIO_Pin_10

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_GPIOX                           GPIOD
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_GPIO                            GPIOE
/* 控制信号线 */
/* 读使能 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RD_PIN                            GPIO_Pin_4
/* 写使能 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_WR_PIN                            GPIO_Pin_5
/* DC引脚，使用FSMC的地址信号控制，本引脚决定了访问LCD时使用的地址 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DC_PIN                            GPIO_Pin_11
/* 片选，选择NOR/SRAM块 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CS_PIN                            GPIO_Pin_7

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CTRL_GPIOX                        GPIOD

/* 复位 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_PIN                           GPIO_Pin_1

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_GPIOX                         GPIOE

/* 背光 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_PIN                            GPIO_Pin_12

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_GPIOX                          GPIOD

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_X              0x2A    /* 设置X坐标 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_Y              0x2B    /* 设置Y坐标 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_PIXEL                     0x2C    /* 填充像素 */

#define VIGOROUSLY_SMART_CAR_DISAPLAY_LESS_PIXEL                            240     /* 液晶屏较短方向的像素宽度 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_MORE_PIXEL                            320     /* 液晶屏较长方向的像素宽度 */

#define VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START                        0       /* 起始点的X坐标 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START                        0       /* 起始点的Y坐标 */

/* 定义ILI934显示屏常用颜色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_WHITE                                 0xFFFF  /* 白色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_BLACK                                 0x0000  /* 黑色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_GREY                                  0xF7DE  /* 灰色 */ 
#define VIGOROUSLY_SMART_CAR_DISAPLAY_BLUE                                  0x001F  /* 蓝色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_BLUE2                                 0x051F  /* 浅蓝色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_RED                                   0xF800  /* 红色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_MAGENTA                               0xF81F  /* 红紫色，洋红色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_GREEN                                 0x07E0  /* 绿色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_CYAN                                  0x7FFF  /*蓝绿色，青色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_YELLOW                                0xFFE0  /*黄色 */
#define VIGOROUSLY_SMART_CAR_DISAPLAY_BRED                                  0xF81F
#define VIGOROUSLY_SMART_CAR_DISAPLAY_GRED                                  0xFFE0
#define VIGOROUSLY_SMART_CAR_DISAPLAY_GBLUE                                 0x07FF
#define VIGOROUSLY_SMART_CAR_DISAPLAY_BACKGROUND                            VIGOROUSLY_SMART_CAR_DISAPLAY_BLACK   /* 默认背景颜色 */

extern double distance;

extern void vigorously_smart_car_display_set_font(vigorously_smart_car_font *fonts);

extern vigorously_smart_car_font *vigorously_smart_car_display_get_font();

void vigorously_smart_car_display_clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void vigorously_smart_car_display_clear_line(uint16_t line);

void vigorously_smart_car_display_set_color(uint16_t text_color, uint16_t back_color);

void vigorously_smart_car_display_gram_scan(uint8_t option);

uint16_t vigorously_smart_car_display_read_id();

void vigorously_smart_car_display_en(uint16_t line, uint8_t *pstr);

void vigorously_smart_car_display_init();

#endif //__VIGOROUSLY_SMART_CAR_LCD_DISPLAY_H