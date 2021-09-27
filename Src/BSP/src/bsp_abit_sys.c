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

void bsp_abit_reset_recv_buff(uint8_t *recv_len, uint8_t *recv_buff, uint8_t size)
{
    *recv_len = 0;
    memset(recv_buff, 0, size * sizeof(uint8_t));
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

uint8_t bsp_abit_send_at_cmd(USART_TypeDef *usartx, uint8_t *cmd, uint8_t *relay, uint8_t *msg, uint8_t delay, uint8_t msg_len)
{
    bsp_abit_usart_send(usartx, cmd);
    bsp_abit_delay_ms(delay);

    if(bsp_abit_string_search(msg, relay, msg_len) == 0)
        return 0;
    else
        return 1;
}