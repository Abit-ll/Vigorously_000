#include "vigorously_smart_car_wifi.h"

struct Vigorously_Smart_Car_Recv_Info vigorously_wifi_info;

struct Vigorously_Smart_Car_Wifi_Info vigorously_wifi_connect_info;
Vigorously_Wifi_Status vigorously_wifi_status = vigorously_wifi_disconnect;

uint8_t wifi_send_buff[20] = {0x00, };
uint8_t wifi_recv_buff[100] = {0x00, };
uint8_t *vigorously_smart_car_ip;
uint8_t *wifi_ssid;
uint8_t *wifi_psswd;
uint8_t wifi_recv_len = 0;
uint8_t cwmode = 0;

void wigorously_smart_car_wifi_config(struct Vigorously_Smart_Car_Wifi_Info *wifi_connect_info)
{

}