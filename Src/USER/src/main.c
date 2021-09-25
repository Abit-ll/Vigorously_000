#include "main.h"

int main()
{
    float distance;
    uint8_t distance_buff[10] = {0x00, };
    uint8_t i = 0;
    // Vigorously_Smart_Car_Direction direction;
    uint16_t speed = 0;
    uint8_t *recv_buff;

    // vigorously_smart_car_mode = Manual_Mode;

    bsp_abit_usart_init(115200);

    bsp_abit_delay_init(168);

    // vigorously_smart_car_ctrl_init((500 - 1), (8400 - 1));
    // vigorously_smart_car_ultrasonic_init((15000 - 1), (84 - 1));
    // vigorously_smart_car_oled_display_init();

    // vigorously_smart_car_oled_display_show_string(0, 0, "VIGOROUSLY", 24);
    // vigorously_smart_car_oled_display_show_string(0, 24, "SMART CAR", 16);
    // vigorously_smart_car_oled_display_show_string(0, 40, "distance:", 12);
    // vigorously_smart_car_oled_display_refresh_gram();
    printf("Hello Smart Car!\r\n");
    bsp_abit_delay_ms(1000);

    vigorously_smart_car_ip = malloc(20 * sizeof(uint8_t));
    memset(vigorously_smart_car_ip, 0, 20 * sizeof(uint8_t));

    recv_buff = malloc(15 * sizeof(uint8_t));
    memset(vigorously_smart_car_ip, 0, 15 * sizeof(uint8_t));

    vigorously_smart_car_wifi_config();

    while(1) 
    {
        /* 先超声波测距，如果距离小于15cm，小车静止不动 */
        // distance = vigorously_smart_car_ultrasonic_get_distance();

        // vigorously_smart_car_double_2_char(distance, distance_buff, 7);
        // vigorously_smart_car_oled_display_show_string(55, 40, distance_buff, 12);
        // vigorously_smart_car_oled_display_show_string(100, 40, "cm", 12);
        // vigorously_smart_car_oled_display_refresh_gram();
        // memset(distance_buff, 0, 10 * sizeof(uint8_t));

        bsp_abit_delay_ms(1000);

        if(wifi_recv_len > 0)
        {
            bsp_abit_string_cpy(wifi_recv_buff, recv_buff, ":", wifi_recv_len);
            printf("%s\r\n", recv_buff);
            bsp_abit_delay_ms(1000);
            memset(vigorously_smart_car_ip, 0, 10 * sizeof(uint8_t));
            vigorously_smart_car_wifi_reset_recv_buff();
        }

        // if(vigorously_smart_car_mode == Manual_Mode)
        // {
        //     /* 手动运行 */
        //     if((direction == go_stop) || (distance <= VIGOROUSLY_SMART_CAR_SAFE_DISTANCE))
        //         vigorously_smart_car_stop(0);
        //     else if((direction == move_forward) && (distance > VIGOROUSLY_SMART_CAR_SAFE_DISTANCE))
        //         vigorously_smart_car_move_forward(speed);
        //     else if(direction == move_back)
        //         vigorously_smart_car_move_back(speed);
        //     else if((direction == move_left) && (distance > VIGOROUSLY_SMART_CAR_SAFE_DISTANCE))
        //         vigorously_smart_car_move_left(speed);
        //     else if((direction == move_right)  && (distance > VIGOROUSLY_SMART_CAR_SAFE_DISTANCE))
        //         vigorously_smart_car_move_right(speed);
        // }
        // else
        // {
        //     /* 自动运行 */
        //     speed = 300;
        //     if(distance <= VIGOROUSLY_SMART_CAR_SAFE_DISTANCE)
        //         vigorously_smart_car_move_back(speed);
            
        // }

    }
    
    return 0;
}