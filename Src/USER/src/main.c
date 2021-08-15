#include "main.h"

int main()
{
    float distance;

    bsp_abit_led_init();

    bsp_abit_usart_init(115200);

    bsp_abit_delay_init(168);

    vigorously_smart_car_init(200 - 1, 8400 - 1);

    vigorously_smart_car_ultrasonic_ranging_init((15000 - 1), (84 - 1));

    while(1)
    {
        printf("Hello Vigorously_000!\r\n");
        bsp_abit_delay_ms(2000);
        vigorously_smart_car_ctrl();
        distance = vigorously_smart_car_ultrasonic_ranging();
        printf("distance = %f\r\n", distance);
        bsp_abit_delay_ms(2000);
    }
    
    return 0;
}