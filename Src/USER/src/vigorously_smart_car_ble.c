#include "vigorously_smart_car_ble.h"

uint16_t recv_buff[100] = {0x00, };
uint8_t recv_len = 0;
uint8_t ble_recv_buff[35] = {0x00, };
uint8_t ble_recv_len = 0;

void vigorously_smart_car_ble_msg_proc(uint8_t *recv)
{
    uint8_t i = 0;
    uint8_t ack = 0;
    uint8_t data_len = 0;

    for(i = 0; i < (ble_recv_len / 2); i++)
    {
        recv[i] = ((bsp_abit_char_2_hex(&ble_recv_buff[2 * i]) << 4) | (bsp_abit_char_2_hex(&ble_recv_buff[2 * i + 1])));
        ack |= recv[i];
        if(i == (ble_recv_len / 2 - 1))
            break;
    }

    if(recv[0] == 0x4C)
    {
        if(recv[1] == 0x58)
        {
            if(ack == recv[ble_recv_len / 2 - 1])
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

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_BLE_STATE_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_BLE_STATE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX, &GPIO_InitStruct);

    while(GPIO_ReadInputDataBit(VIGOROUSLY_SMART_CAR_BLE_STATE_GPIOX, VIGOROUSLY_SMART_CAR_BLE_STATE_PIN) != 1);
}