#include "vigorously_smart_car_ble.h"

struct Vigorously_Smart_Car_Recv_Info vigorously_ble_info;

void vigorously_smart_car_ble_msg_proc(uint8_t *recv)
{
    uint8_t i = 0;
    uint8_t ack = 0;
    uint8_t data_len = 0;

    for(i = 0; i < (vigorously_ble_info.vigorously_recv_len / 2); i++)
    {
        recv[i] = ((bsp_abit_char_2_hex(&vigorously_ble_info.vigorously_recv_buff[2 * i]) << 4) | (bsp_abit_char_2_hex(&vigorously_ble_info.vigorously_recv_buff[2 * i + 1])));
        ack |= recv[i];
        if(i == (vigorously_ble_info.vigorously_recv_len / 2 - 1))
            break;
    }

    if(recv[0] == 0x4C)
    {
        if(recv[1] == 0x58)
        {
            if(ack == recv[vigorously_ble_info.vigorously_recv_len / 2 - 1])
            {
                data_len = recv[2];
                vigorously_smart_car_set_ap_info((recv + 3), data_len);
            }
            else
            {

            }
        }
        else
        {

        }
    }
    else
    {

    }
}

void vigorously_smart_car_ble_config()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    bsp_abit_set_recv_buff(&vigorously_ble_info, VIGOROUSLY_RECV_LEN);

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_BLE_STATE_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_BLE_STATE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX, &GPIO_InitStruct);

    if(bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_BLE_USARTX, "AT+NAME\r\n", "Smart_Car", VIGOROUSLY_RECV_LEN, &vigorously_ble_info))
    {
        bsp_abit_send_at_cmd(VIGOROUSLY_SMART_CAR_BLE_USARTX, "AT+NAME Smart_Car\r\n", "Smart_Car", VIGOROUSLY_RECV_LEN, &vigorously_ble_info);
    }

    while(GPIO_ReadInputDataBit(VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX, VIGOROUSLY_SMART_CAR_BLE_STATE_PIN) != 1);
}