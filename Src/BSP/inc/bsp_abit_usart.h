#ifndef __BSP_ABIT_USART_H
#define __BSP_ABIT_USART_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"

#define ABIT_DEBUG_USART_GPIO_CLOCK             RCC_AHB1Periph_GPIOA
#define ABIT_DEBUG_USART_USART_CLOCK            RCC_APB2Periph_USART1

#define ABIT_DEBUG_USART_TX                     GPIO_Pin_9
#define ABIT_DEBUG_USART_RX                     GPIO_Pin_10
#define ABIT_DEBUG_USART_GPIOX                  GPIOA
#define ABIT_DEBUG_USARTX                       USART1

void bsp_abit_usart_send(USART_TypeDef* USARTx, uint16_t *ch);

void bsp_abit_usart_init(uint32_t baud);

#endif //__BSP_ABIT_USART_H