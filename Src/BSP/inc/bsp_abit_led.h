#ifndef __BSP_ABIT_LED_H
#define __BSP_ABIT_LED_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define ABIT_LED_GPIO_CLOCK         RCC_AHB1Periph_GPIOF

#define ABIT_LED_GPIOX              GPIOF
#define ABIT_LED1_GPIO_PIN          GPIO_Pin_9
#define ABIT_LED2_GPIO_PIN          GPIO_Pin_10

#define ABIT_LED1_ON                GPIO_ResetBits(ABIT_LED_GPIOX, ABIT_LED1_GPIO_PIN)
#define ABIT_LED1_OFF               GPIO_SetBits(ABIT_LED_GPIOX, ABIT_LED1_GPIO_PIN)

#define ABIT_LED2_ON                GPIO_ResetBits(ABIT_LED_GPIOX, ABIT_LED2_GPIO_PIN)
#define ABIT_LED2_OFF               GPIO_SetBits(ABIT_LED_GPIOX, ABIT_LED2_GPIO_PIN)

void bsp_abit_led_init();

#endif //__BSP_ABIT_LED_H