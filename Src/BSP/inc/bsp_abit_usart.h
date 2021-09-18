#ifndef __BSP_ABIT_USART_H
#define __BSP_ABIT_USART_H

#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"

/* DEBUG */
#define ABIT_DEBUG_USART_GPIO_CLOCK                             RCC_AHB1Periph_GPIOA
#define ABIT_DEBUG_USART_USART_CLOCK                            RCC_APB2Periph_USART1

/* ESP8266 */
#define VIGOROUSLY_SMART_CAR_WIFI_USART2_CLOCK                  RCC_APB1Periph_USART2

/* BLE */
#define VIGOROUSLY_SMART_CAR_BLE_USART3_GPIO_CLOCK              RCC_AHB1Periph_GPIOB
#define VIGOROUSLY_SMART_CAR_BLE_USART3_CLOCK                   RCC_APB1Periph_USART3

/* GSM */
#define VIGOROUSLY_SMART_CAR_GSM_USART6_GPIO_CLOCK              RCC_AHB1Periph_GPIOC
#define VIGOROUSLY_SMART_CAR_GSM_USART6_CLOCK                   RCC_APB2Periph_USART6

#define ABIT_DEBUG_USART_TX                                     GPIO_Pin_9
#define ABIT_DEBUG_USART_RX                                     GPIO_Pin_10
#define ABIT_DEBUG_USART_GPIOX                                  GPIOA
#define ABIT_DEBUG_USARTX                                       USART1

/* ESP8266 */
#define VIGOROUSLY_SMART_CAR_WIFI_USART2_TX                     GPIO_Pin_2
#define VIGOROUSLY_SMART_CAR_WIFI_USART2_RX                     GPIO_Pin_3
#define VIGOROUSLY_SMART_CAR_WIFI_USART2_GPIOX                  GPIOA
#define VIGOROUSLY_SMART_CAR_WIFI_USARTX                        USART2

/* BLE */
#define VIGOROUSLY_SMART_CAR_BLE_USART3_TX                      GPIO_Pin_10
#define VIGOROUSLY_SMART_CAR_BLE_USART3_RX                      GPIO_Pin_11
#define VIGOROUSLY_SMART_CAR_BLE_USART3_GPIOX                   GPIOB
#define VIGOROUSLY_SMART_CAR_BLE_USARTX                         USART3

/* GSM */
#define VIGOROUSLY_SMART_CAR_GSM_USART6_TX                      GPIO_Pin_6
#define VIGOROUSLY_SMART_CAR_GSM_USART6_RX                      GPIO_Pin_7
#define VIGOROUSLY_SMART_CAR_GSM_USART6_GPIOX                   GPIOC
#define VIGOROUSLY_SMART_CAR_GSM_USARTX                         USART6

void bsp_abit_usart_send(USART_TypeDef* USARTx, uint16_t *ch);

void bsp_abit_usart_init(uint32_t baud);

#endif //__BSP_ABIT_USART_H