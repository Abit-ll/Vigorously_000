#include "bsp_abit_sccb.h"

static uint8_t bsp_abit_sccb_read_byte()
{
    uint8_t ret;
    uint8_t i;

    BSP_ABIT_SCCB_SDA_MODE_IN();
    for(i = 0; i < 8; i++)
    {
        bsp_abit_delay_us(50);
        BSP_ABIT_SCCB_SCL_OUT_HIGHT;
        ret <<= 1;
        if(BSP_ABIT_SCCB_SDA_IN)
            ret++;
        bsp_abit_delay_us(50);
        BSP_ABIT_SCCB_SCL_OUT_LOW;
    }
    BSP_ABIT_SCCB_SDA_MODE_OUT();

    return ret;
}

static uint8_t bsp_abit_sccb_write_byte(uint8_t data)
{
    uint8_t i;
    uint8_t ret;

    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
            BSP_ABIT_SCCB_SDA_OUT_HIGHT;
        else
            BSP_ABIT_SCCB_SDA_OUT_LOW;

        data <<= 1;
        bsp_abit_delay_us(50);
        BSP_ABIT_SCCB_SCL_OUT_HIGHT;
        bsp_abit_delay_us(50);
        BSP_ABIT_SCCB_SCL_OUT_LOW;
    }

    BSP_ABIT_SCCB_SDA_MODE_IN();
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SCL_OUT_HIGHT;
    bsp_abit_delay_us(50);
    if(BSP_ABIT_SCCB_SDA_IN)
        ret = 1;
    else
        ret = 0;
    BSP_ABIT_SCCB_SCL_OUT_LOW;
    BSP_ABIT_SCCB_SDA_MODE_OUT();

    return ret;
}

static void bsp_abit_sccb_no_ack()
{
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SDA_OUT_HIGHT;
    BSP_ABIT_SCCB_SCL_OUT_HIGHT;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SCL_OUT_LOW;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SDA_OUT_LOW;
    bsp_abit_delay_us(50);
}

static void bsp_abit_sccb_stop()
{
    BSP_ABIT_SCCB_SDA_OUT_LOW;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SCL_OUT_HIGHT;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SDA_OUT_HIGHT;
    bsp_abit_delay_us(50);
}

static void bsp_abit_sccb_start()
{
    BSP_ABIT_SCCB_SDA_OUT_HIGHT;
    BSP_ABIT_SCCB_SCL_OUT_HIGHT;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SDA_OUT_LOW;
    bsp_abit_delay_us(50);
    BSP_ABIT_SCCB_SCL_OUT_LOW;
}

uint8_t bsp_abit_sccb_read_reg(uint8_t reg)
{
    uint8_t data = 0;

    bsp_abit_sccb_start();
    bsp_abit_sccb_write_byte(BSP_ABIT_SCCB_ID);
    bsp_abit_delay_us(100);
    bsp_abit_sccb_write_byte(reg);
    bsp_abit_delay_us(100);
    bsp_abit_sccb_stop();
    bsp_abit_delay_us(100);

    bsp_abit_sccb_start();
    bsp_abit_sccb_write_byte(BSP_ABIT_SCCB_ID | 0x01);
    bsp_abit_delay_us(100);
    data = bsp_abit_sccb_read_byte();
    bsp_abit_sccb_no_ack();
    bsp_abit_sccb_stop();
    
    return data;
}

uint8_t bsp_abit_sccb_write_reg(uint8_t reg, uint8_t data)
{
    uint8_t ret = 0;

    bsp_abit_sccb_start();
    if(bsp_abit_sccb_write_byte(BSP_ABIT_SCCB_ID))
        ret = 1;
    bsp_abit_delay_us(100);
    if(bsp_abit_sccb_write_byte(reg))
        ret = 1;
    bsp_abit_delay_us(100);
    if(bsp_abit_sccb_write_byte(data))
        ret = 1;
    bsp_abit_sccb_stop();

    return ret;
}

void bsp_abit_sccb_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(BSP_ABIT_SCCB_SCL_SDA_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = (BSP_ABIT_SCCB_SCL_PIN | BSP_ABIT_SCCB_SDA_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BSP_ABIT_SCCB_SCL_SDA_GPIOX, &GPIO_InitStruct);

    GPIO_SetBits(BSP_ABIT_SCCB_SCL_SDA_GPIOX, (BSP_ABIT_SCCB_SCL_PIN | BSP_ABIT_SCCB_SDA_PIN));

    BSP_ABIT_SCCB_SDA_MODE_OUT();
}