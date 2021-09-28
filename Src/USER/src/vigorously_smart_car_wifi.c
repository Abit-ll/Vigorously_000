#include "vigorously_smart_car_wifi.h"

Vigorously_Smart_Car_Mode vigorously_smart_car_mode;

uint8_t wifi_send_buff[20] = {0x00, };
uint8_t wifi_recv_buff[100] = {0x00, };
uint8_t *vigorously_smart_car_ip;
uint8_t *wifi_ssid;
uint8_t *wifi_psswd;
uint8_t wifi_recv_len = 0;
uint8_t cwmode = 0;

void vigorously_smart_car_set_ap_info(uint8_t *ap_info, uint8_t size)
{
    uint8_t i = 0;
    uint8_t hight = 0;
    uint8_t low = 0;

    if((ap_info[0] == DN) && (ap_info[1] == ssid))
    {
        for(i = 2; i < size; i++)
        {
            wifi_ssid[i - 2] = ap_info[2];
        }

        printf("wifi ssid: %s\r\n", wifi_ssid);
    }
    else if((ap_info[0] == DN) && (ap_info[1] == psswd))
    {
        for(i = 2; i < size; i++)
        {
            wifi_psswd[i - 2] = ap_info[2];
        }

        printf("wifi psswd: %s\r\n", wifi_psswd);
    }
}

void vigorously_smart_car_wifi_config(uint8_t *connet)
{
    while(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, connet, "WIFI CONNECTED", wifi_recv_buff, 18000, wifi_recv_len) != 0)
    {
        bsp_abit_delay_ms(2000);
        if(bsp_abit_string_search(wifi_recv_buff, "WIFI CONNECTED", wifi_recv_len) == 0)
            break;
    }
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);

    while(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CIPSTA?\r\n", "+CIPSTA:ip:", wifi_recv_buff, 2000, wifi_recv_len) != 0)
    {
        bsp_abit_delay_ms(2000);
        if(bsp_abit_string_search(wifi_recv_buff, "+CIPSTA:ip:", wifi_recv_len) == 0)
        {
            bsp_abit_string_cpy(wifi_recv_buff, vigorously_smart_car_ip, "ip:\"", "\"", wifi_recv_len);
            printf("ip: %s\r\n", vigorously_smart_car_ip);
            break;
        }
    }
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CIPSTART=\"UDP\",\"0.0.0.0\",8080,9090\r\n", "CONNECTED", wifi_recv_buff,10, wifi_recv_len);
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    bsp_abit_delay_ms(1000);
}

uint8_t vigorously_smart_car_wifi_init()
{
    /* 配网操作 */
    while(1)
    {
        if(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len) == 0)
            break;
    }
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "ATE0\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len);
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CWMODE_DEF?\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len);
    bsp_abit_string_cpy(wifi_recv_buff, &cwmode, "+CWMODE_DEF:", "\r", wifi_recv_len);

    printf("+CWMODE_DEF: 0x%x\r\n", cwmode);
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    if((cwmode - 0x30) != 3)
    {
        bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CWMODE_DEF=3\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len);
    }
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CWAUTOCONN=0\r\n", "OK", wifi_recv_buff, 10, wifi_recv_len);
    bsp_abit_reset_recv_buff(&wifi_recv_len, wifi_recv_buff, 100);
    while(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_WIFI_USARTX, "AT+CWJAP_DEF?\r\n", "OK", wifi_recv_buff, 2000, wifi_recv_len) != 0)
    {
        bsp_abit_delay_ms(2000);
        if(bsp_abit_string_search(wifi_recv_buff, "No AP", wifi_recv_len) == 0)
            return 1;
        else if(bsp_abit_string_search(wifi_recv_buff, "+CWJAP_DEF:", wifi_recv_len) == 0)
            return 0;
    }
}