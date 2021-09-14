#include "vigorously_smart_car_ultrasonic.h"

void vigorously_smart_car_double_2_char(float num, uint8_t *src, uint8_t len)
{
    uint8_t chr[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    uint16_t temp = num;
    float temp1 = 0.000;
    int8_t i = 0;
    uint8_t t = 0;

    if(num >= 400)
        return;

    temp1 = num - temp;

    if(temp / 100)
        t = 2;
    else if(temp / 10)
        t = 1;
    else
        t = 0;

    for(i = t; i >= 0; i--)
    {
        src[i] = chr[temp % 10];
        temp = temp / 10;
    }
    t += 1;
    src[t++] = chr[10];

    for(; t < len; t++)
    {
        temp1 *= 10;
        temp = temp1;
        src[t] = chr[temp];
        temp1 -= temp;
    }

    src[t] = '\0';
}

float vigorously_smart_car_ultrasonic_get_distance()
{
    uint32_t count;
    float dist;

    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, VIGOROUSLY_SMART_CAR_ULTRASONIC_TRIG_PIN);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, VIGOROUSLY_SMART_CAR_ULTRASONIC_TRIG_PIN);
    bsp_abit_delay_ms(20);
    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, VIGOROUSLY_SMART_CAR_ULTRASONIC_TRIG_PIN);
    TIM_SetCounter(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX, 0);

    while(!GPIO_ReadInputDataBit(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, VIGOROUSLY_SMART_CAR_ULTRASONIC_ECHO_PIN));
    TIM_Cmd(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX, ENABLE);
    while(GPIO_ReadInputDataBit(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, VIGOROUSLY_SMART_CAR_ULTRASONIC_ECHO_PIN));
    TIM_Cmd(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX, DISABLE);
    count = TIM_GetCounter(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX);
    printf("count = %d\r\n", count);

    dist = (float)count * 0.034 / 2;

    return dist;
}

void vigorously_smart_car_ultrasonic_init(uint16_t period, uint16_t prescaler)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIO_CLOCK, ENABLE);
    RCC_APB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIM_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_ULTRASONIC_TRIG_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_ULTRASONIC_ECHO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(VIGOROUSLY_SMART_CAR_ULTRASONIC_GPIOX, &GPIO_InitStruct);

    TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStruct.TIM_Period = period;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(VIGOROUSLY_SMART_CAR_ULTRASONIC_TIMX, &TIM_TimeBaseInitStruct);
}