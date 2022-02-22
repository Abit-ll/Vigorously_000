#include "bsp_abit_sys.h"

uint8_t bsp_abit_char_2_hex(uint8_t *src)
{
    uint8_t desc;

    if((*src >= '0') && (*src <= '9'))
        desc = *src - 0x30;
    else if((*src >= 'a') && (*src <= 'f'))
        desc = *src - 0x57;
    else if((*src >= 'A') && (*src <= 'F'))
        desc = *src - 0x37;

    return desc;
}

uint8_t bsp_abit_hex_2_char(uint8_t *src)
{
    uint8_t desc;

    if((*src >= 0) && (*src <= 9))
        desc = *src + 0x30;
    else if((*src >= 0xA) && (*src <= 0xF))
        desc = *src + 0x37;
    
    return desc;
}

void bsp_abit_set_recv_buff(struct Vigorously_Smart_Car_Recv_Info *recv_info, uint8_t size)
{
    recv_info->vigorously_recv_len = 0;
    recv_info->vigorously_recv_buff = malloc(size * sizeof(uint8_t));
    memset(recv_info->vigorously_recv_buff, 0, size * sizeof(uint8_t));
    recv_info->vigorously_recv_flag = 0;
}

void bsp_abit_reset_recv_buff(struct Vigorously_Smart_Car_Recv_Info *recv_info, uint8_t size)
{
    recv_info->vigorously_recv_len = 0;
    recv_info->vigorously_recv_flag = 0;
    memset(recv_info->vigorously_recv_buff, 0, size * sizeof(uint8_t));
}

uint8_t bsp_abit_string_cpy(uint8_t *src, uint8_t *desc, uint8_t *obj, uint8_t *end, uint8_t srclen)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    uint8_t relay_size = 0;

    relay_size = strlen(obj);

    if(src == NULL)
        return 1;

    for(i = 0; i < srclen; i++)
    {
        if(src[i] == obj[0])
        {
            for(j = 1; j < relay_size; j++)
            {
                if(src[i + j] != obj[j])
                    break;
            }
            if(j == relay_size)
            {
                while(src[i + j] != *end)
                {
                    k++;
                    j++;
                }
                memcpy(desc, (src + i + relay_size), k);
                return 0;
            }
        }
        if((i + relay_size) > srclen)
            return 1;
    }
}

uint8_t bsp_abit_string_search(uint8_t *src, uint8_t *obj, uint8_t srclen)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t relay_size = 0;

    relay_size = strlen(obj);

    if((src == NULL) || (obj == NULL))
        return 1;
    
    for(i = 0; i < srclen; i++)
    {
        if(src[i] == obj[0])
        {
            for(j = 1; j < relay_size; j++)
            {
                if(src[i + j] != obj[j])
                    break;
            }
            if(j == relay_size)
                return 0;
        }
        if((i + relay_size) > srclen)
            return 1;
    }
}

uint8_t bsp_abit_send_at_cmd(USART_TypeDef *usartx, uint8_t *cmd, uint8_t *relay, uint8_t size, struct Vigorously_Smart_Car_Recv_Info *recv_info)
{
    uint8_t msg[20] = {0x00, };
    uint8_t msg_len = 0;

    bsp_abit_usart_send(usartx, cmd);

    while(1)
    {
        if(recv_info->vigorously_recv_flag == 1)
        {
            memcpy(msg, recv_info->vigorously_recv_buff, 20);
            msg_len = recv_info->vigorously_recv_len;
            bsp_abit_reset_recv_buff(recv_info, size);
            if(bsp_abit_string_search(msg, relay, msg_len) == 0)
                return 0;
            else
                return 1;
        }
    }
}

static void bsp_abit_ble_msg_proc(struct Vigorously_Smart_Car_Wifi_Info *ble_msg, uint8_t *msg)
{
    uint8_t buff[20] = {0x00, };
    uint8_t size = 0;

    for(size = 0; size < (8 / 2); size++)
        buff[size] = ((bsp_abit_char_2_hex(&msg[2 * size]) << 4) | (bsp_abit_char_2_hex(&msg[2 * size + 1])));
    
    if((buff[0] == 0x79) && (buff[1] == 0x69))
    {
        size = buff[3];
        if(buff[2] == 0x01)
        {
            memcpy(ble_msg->vigorously_wifi_ssid, (msg + 8), size);
        }
        else if(buff[2] == 0x02)
        {
            memcpy(ble_msg->vigorously_wifi_passwd, (msg + 8), size);
        }
    }
}

void bsp_abit_sys_init()
{
    uint8_t recv_msg[40] = {0x00, };
    uint8_t recv_len = 0;
    uint8_t i = 0;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    bsp_abit_led_init();
    bsp_abit_delay_init(168);
    bsp_abit_usart_init(115200);

    vigorously_smart_car_lcd_init(&Font8x16);
    vigorously_smart_car_lcd_display_gram_scan(vigorously_smart_car_lcd.vigorously_smart_car_display_scan_mode);
    vigorously_smart_car_lcd_display_clear(VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_WHITE);
    vigorously_smart_car_camera_init();
    // while (1)
    // {
    //     switch(i)
    //     {
    //         case 0:
    //             vigorously_smart_car_dislpay_set_color(VIGOROUSLY_SMART_CAR_DISPLAY_YELLOW, VIGOROUSLY_SMART_CAR_DISPLAY_RED);
    //             break;
    //         case 1:
    //             vigorously_smart_car_dislpay_set_color(VIGOROUSLY_SMART_CAR_DISPLAY_BLUE, VIGOROUSLY_SMART_CAR_DISPLAY_GREEN);
    //             break;
    //     }
    //     i++;
    //     if(i > 1)
    //         i = 0;
    //     vigorously_smart_car_lcd_display_clear(VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL, vigorously_smart_car_lcd.vigorously_smart_car_display_current_back_color);
    //     vigorously_smart_car_lcd_display_en(LINEX(4), "Hello yiyi!");
    //     bsp_abit_delay_ms(2000);
    // }

        vigorously_smart_car_dislpay_set_color(VIGOROUSLY_SMART_CAR_DISPLAY_YELLOW, VIGOROUSLY_SMART_CAR_DISPLAY_RED);
        vigorously_smart_car_lcd_display_clear(VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_RED);
        vigorously_smart_car_lcd_display_en(LINEX(4), "Hello yiyi!");
        bsp_abit_delay_ms(2000);

        // vigorously_smart_car_camera_display_window(0, 0);
        // vigorously_smart_car_lcd_display_fill_color((VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL * VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL), VIGOROUSLY_SMART_CAR_DISPLAY_WHITE);

        vigorously_smart_car_lcd_display_clear(VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_WHITE);

        vigorously_smart_car_camera_start();
        while(1)
        {
            // vigorously_smart_car_camera_stop();
            // bsp_abit_delay_ms(800);
            // vigorously_smart_car_camera_start();
        }
    
        

    // /* ble config */
    // vigorously_smart_car_ble_config();

    // /* wifi config */
    // while(vigorously_wifi_status == vigorously_wifi_disconnect)
    // {
    //     if(vigorously_ble_info.vigorously_recv_flag == 1)
    //     {
    //         memcpy(recv_msg, vigorously_ble_info.vigorously_recv_buff, vigorously_ble_info.vigorously_recv_len);
    //         recv_len = vigorously_ble_info.vigorously_recv_len;
    //         bsp_abit_reset_recv_buff(&vigorously_ble_info, VIGOROUSLY_RECV_LEN);
    //         bsp_abit_ble_msg_proc(&vigorously_wifi_connect_info, recv_msg);
    //     }
    //     wigorously_smart_car_wifi_config(&vigorously_wifi_connect_info);
    // }
}