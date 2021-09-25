#include "vigorously_smart_car_wifi.h"

Vigorously_Smart_Car_Mode vigorously_smart_car_mode;

uint8_t wifi_send_buff[20] = {0x00, };
uint8_t wifi_recv_buff[100] = {0x00, };
uint8_t *vigorously_smart_car_ip;

uint8_t wifi_recv_len = 0;

void vigorously_smart_car_wifi_reset_recv_buff()
{
    wifi_recv_len = 0;
    memset(wifi_recv_buff, 0, 100 * sizeof(uint8_t));
}

void vigorously_smart_car_wifi_config()
{
    /* 配网操作 */
    while(1)
    {
        if(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USART, "AT\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len) == 0)
            break;
    }
    vigorously_smart_car_wifi_reset_recv_buff();
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USART, "ATE0\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len);
    vigorously_smart_car_wifi_reset_recv_buff();
    while(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USART, "AT+CWJAP=\"TP-LINK_2E7E\",\"03770321\"\r\n", "WIFI CONNECTED", wifi_recv_buff, 18000, wifi_recv_len) != 0)
    {
        bsp_abit_delay_ms(2000);
        if(bsp_abit_string_search(wifi_recv_buff, "WIFI CONNECTED", wifi_recv_len) == 0)
            break;
    }
    vigorously_smart_car_wifi_reset_recv_buff();
    while(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USART, "AT+CIPSTA?\r\n", "+CIPSTA:ip:", wifi_recv_buff, 2000, wifi_recv_len) != 0)
    {
        bsp_abit_delay_ms(2000);
        if(bsp_abit_string_search(wifi_recv_buff, "+CIPSTA:ip:", wifi_recv_len) == 0)
        {
            bsp_abit_string_cpy(wifi_recv_buff, vigorously_smart_car_ip, "ip:\"", wifi_recv_len);
            printf("ip: %s\r\n", vigorously_smart_car_ip);
            break;
        }
    }
    vigorously_smart_car_wifi_reset_recv_buff();
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USART, "AT+CIPSTART=\"UDP\",\"0.0.0.0\",8080,9090\r\n", "CONNECTED", wifi_recv_buff,10, wifi_recv_len);
    vigorously_smart_car_wifi_reset_recv_buff();
    bsp_abit_delay_ms(1000);
}