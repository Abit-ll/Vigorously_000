#include "main.h"

int main()
{
    bsp_abit_led_init();

    bsp_abit_usart_init(115200);

    bsp_abit_delay_init(168);
    
    return 0;
}