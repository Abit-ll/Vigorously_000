#ifndef __BSP_ABIT_SCCB_H
#define __BSP_ABIT_SCCB_H

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "bsp_abit_delay.h"

#define BSP_ABIT_SCCB_SCL_SDA_CLOCK                     RCC_AHB1Periph_GPIOD

#define BSP_ABIT_SCCB_SCL_SDA_GPIOX                     GPIOD

#define BSP_ABIT_SCCB_SCL_PIN                           GPIO_Pin_6
#define BSP_ABIT_SCCB_SDA_PIN                           GPIO_Pin_7

#define BSP_ABIT_SCCB_SDA_MODE_IN()                     {BSP_ABIT_SCCB_SCL_SDA_GPIOX->MODER &= ~(3 << (7 * 2)); BSP_ABIT_SCCB_SCL_SDA_GPIOX->MODER |= (((uint32_t)0) << (7 * 2));}
#define BSP_ABIT_SCCB_SDA_MODE_OUT()                    {BSP_ABIT_SCCB_SCL_SDA_GPIOX->MODER &= ~(3 << (7 * 2)); BSP_ABIT_SCCB_SCL_SDA_GPIOX->MODER |= (((uint32_t)1) << (7 * 2));}

#define BSP_ABIT_SCCB_SCL_OUT_HIGHT                     (BSP_ABIT_SCCB_SCL_SDA_GPIOX->BSRRL = BSP_ABIT_SCCB_SCL_PIN)
#define BSP_ABIT_SCCB_SCL_OUT_LOW                       (BSP_ABIT_SCCB_SCL_SDA_GPIOX->BSRRH = BSP_ABIT_SCCB_SCL_PIN)
#define BSP_ABIT_SCCB_SDA_OUT_HIGHT                     (BSP_ABIT_SCCB_SCL_SDA_GPIOX->BSRRL = BSP_ABIT_SCCB_SDA_PIN)
#define BSP_ABIT_SCCB_SDA_OUT_LOW                       (BSP_ABIT_SCCB_SCL_SDA_GPIOX->BSRRH = BSP_ABIT_SCCB_SDA_PIN)

#define BSP_ABIT_SCCB_SDA_IN                            (((BSP_ABIT_SCCB_SCL_SDA_GPIOX->IDR & BSP_ABIT_SCCB_SDA_PIN) != 0) ? 1 : 0)

#define BSP_ABIT_SCCB_ID                                0x60

uint8_t bsp_abit_sccb_read_reg(uint8_t reg);

uint8_t bsp_abit_sccb_write_reg(uint8_t reg, uint8_t data);

void bsp_abit_sccb_init();

#endif //__BSP_ABIT_SCCB_H