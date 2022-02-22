#ifndef __VIGOROUSLY_SMART_CAR_CAMERA_H
#define __VIGOROUSLY_SMART_CAR_CAMERA_H

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma.h"

#include "bsp_abit_sccb.h"

#include "vigorously_smart_car_lcd_display.h"

#define VIGOROUSLY_SMART_CAR_CAMERA_HREF_PCLK_XCLK_CLOCK           RCC_AHB1Periph_GPIOA
#define VIGOROUSLY_SMART_CAR_CAMERA_VSYNC_D5_CLOCK                 RCC_AHB1Periph_GPIOB
#define VIGOROUSLY_SMART_CAR_CAMERA_D0_D1_D2_D3_D4_CLOCK           RCC_AHB1Periph_GPIOC
#define VIGOROUSLY_SMART_CAR_CAMERA_D6_D7_CLOCK                    RCC_AHB1Periph_GPIOE
#define VIGOROUSLY_SMART_CAR_CAMERA_CH1_CLOCK                      RCC_AHB1Periph_GPIOF
#define VIGOROUSLY_SMART_CAR_CAMERA_PWDN_CLOCK                     RCC_AHB1Periph_GPIOG

#define VIGOROUSLY_SMART_CAR_CAMERA_DCMI_CLOCK                     RCC_AHB2Periph_DCMI
#define VIGOROUSLY_SMART_CAR_CAMERA_DMA_CLOCK                      RCC_AHB1Periph_DMA2

#define VIGOROUSLY_SMART_CAR_CAMERA_HREF_PCLK_XCLK_GPIOX           GPIOA
#define VIGOROUSLY_SMART_CAR_CAMERA_VSYNC_D5_GPIOX                 GPIOB
#define VIGOROUSLY_SMART_CAR_CAMERA_D0_D1_D2_D3_D4_GPIOX           GPIOC
#define VIGOROUSLY_SMART_CAR_CAMERA_D6_D7_GPIOX                    GPIOE
#define VIGOROUSLY_SMART_CAR_CAMERA_CH1_GPIOX                      GPIOF
#define VIGOROUSLY_SMART_CAR_CAMERA_PWDN_RESET_GPIOX               GPIOG

#define VIGOROUSLY_SMART_CAR_CAMERA_VSYNC_PIN                      GPIO_Pin_7
#define VIGOROUSLY_SMART_CAR_CAMERA_HREF_PIN                       GPIO_Pin_4
#define VIGOROUSLY_SMART_CAR_CAMERA_RESET_PIN                      GPIO_Pin_15
#define VIGOROUSLY_SMART_CAR_CAMERA_D0_PIN                         GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_CAMERA_D1_PIN                         GPIO_Pin_7
#define VIGOROUSLY_SMART_CAR_CAMERA_D2_PIN                         GPIO_Pin_8
#define VIGOROUSLY_SMART_CAR_CAMERA_D3_PIN                         GPIO_Pin_9
#define VIGOROUSLY_SMART_CAR_CAMERA_D4_PIN                         GPIO_Pin_11
#define VIGOROUSLY_SMART_CAR_CAMERA_D5_PIN                         GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_CAMERA_D6_PIN                         GPIO_Pin_5
#define VIGOROUSLY_SMART_CAR_CAMERA_D7_PIN                         GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_CAMERA_PCLK_PIN                       GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_CAMERA_XCLK_PIN                       GPIO_Pin_8
#define VIGOROUSLY_SMART_CAR_CAMERA_PWDN_PIN                       GPIO_Pin_9
#define VIGOROUSLY_SMART_CAR_CAMERA_CH1_PIN                        GPIO_Pin_8

#define VIGOROUSLY_SMART_CAR_CAMERA_CH1_LOW                        (VIGOROUSLY_SMART_CAR_CAMERA_CH1_GPIOX->BSRRH = VIGOROUSLY_SMART_CAR_CAMERA_CH1_PIN)
#define VIGOROUSLY_SMART_CAR_CAMERA_CH1_HIGHT                      (VIGOROUSLY_SMART_CAR_CAMERA_CH1_GPIOX->BSRRL = VIGOROUSLY_SMART_CAR_CAMERA_CH1_PIN)

#define VIGOROUSLY_SMART_CAR_CAMERA_MID                            0X7FA2
#define VIGOROUSLY_SMART_CAR_CAMERA_PID1                           0X2642
#define VIGOROUSLY_SMART_CAR_CAMERA_PID2                           0X2641

/* 当选择DSP地址（0xFF = 0x00）时，OV2640的DSP寄存器地址映射表 */
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_R_BYPASS                   0x05
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_Qs                         0x44
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_CTRL                       0x50
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_HSIZE1                     0x51
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_VSIZE1                     0x52
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_XOFFL                      0x53
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_YOFFL                      0x54
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_VHYX                       0x55
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_DPRP                       0x56
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_TEST                       0x57
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_ZMOW                       0x5A
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_ZMOH                       0x5B
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_ZMHH                       0x5C
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_BPADDR                     0x7C
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_BPDATA                     0x7D
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_CTRL2                      0x86
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_CTRL3                      0x87
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_SIZEL                      0x8C
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_HSIZE2                     0xC0
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_VSIZE2                     0xC1
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_CTRL0                      0xC2
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_CTRL1                      0xC3
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_R_DVP_SP                   0xD3
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_IMAGE_MODE                 0xDA
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_RESET                      0xE0
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_MS_SP                      0xF0
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_SS_ID                      0x7F
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_SS_CTRL                    0xF8
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_MC_BIST                    0xF9
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_MC_AL                      0xFA
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_MC_AH                      0xFB
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_MC_D                       0xFC
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_P_STATUS                   0xFE
#define VIGOROUSLY_SMART_CAR_CAMERA_DSP_RA_DLMT                    0xFF 

/* 当选择传感器地址（0xFF = 0x01）时，OV2640的DSP寄存器地址映射表 */
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_GAIN                    0x00
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM1                    0x03
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG04                   0x04
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG08                   0x08
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM2                    0x09
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_PIDH                    0x0A
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_PIDL                    0x0B
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM3                    0x0C
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM4                    0x0D
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_AEC                     0x10
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_CLKRC                   0x11
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM7                    0x12
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM8                    0x13
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM9                    0x14
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM10                   0x15
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_HREFST                  0x17
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_HREFEND                 0x18
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_VSTART                  0x19
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_VEND                    0x1A
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_MIDH                    0x1C
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_MIDL                    0x1D
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_AEW                     0x24
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_AEB                     0x25
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_W                       0x26
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG2A                   0x2A
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_FRARL                   0x2B
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_ADDVSL                  0x2D
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_ADDVHS                  0x2E
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_YAVG                    0x2F
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG32                   0x32
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_ARCOM2                  0x34
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG45                   0x45
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_FLL                     0x46
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_FLH                     0x47
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM19                   0x48
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_ZOOMS                   0x49
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM22                   0x4B
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_COM25                   0x4E
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_BD50                    0x4F
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_BD60                    0x50
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG5D                   0x5D
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG5E                   0x5E
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG5F                   0x5F
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_REG60                   0x60
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_HISTO_LOW               0x61
#define VIGOROUSLY_SMART_CAR_CAMERA_SENSOR_HISTO_HIGH              0x62

/* 
 * OV2640 SXGA初始化寄存器序列表
 * 此模式下帧率为15帧
 * SXGA(1600 * 1200)
 */
extern  uint8_t vigorously_smart_car_camera_sxga_init_reg_tbl[][2];

/* 
 * OV2640 SVGA初始化寄存器序列表
 * 此模式下，帧率可以达到30帧
 * SVGA 800*600
 */
extern  uint8_t vigorously_smart_car_camera_svga_init_reg_tbl[][2];

extern  uint8_t vigorously_smart_car_camera_jpeg_reg_tbl[][2];

extern  uint8_t vigorously_smart_car_camera_rgb565_reg_tbl[][2];

extern uint8_t vigorously_smart_car_camera_yuv422_reg_tbl[][2];

void vigorously_camera_info_process();

void vigorously_smart_car_camera_stop();

void vigorously_smart_car_camera_start();

uint8_t  vigorously_smart_car_camera_init();

#endif //__VIGOROUSLY_SMART_CAR_CAMERA_H