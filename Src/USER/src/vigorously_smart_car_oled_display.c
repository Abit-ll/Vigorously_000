#include "vigorously_smart_car_oled_display.h"
#include "vigorously_smart_car_oled_display_font.h"

uint8_t vigorously_smart_car_oled_display_GRAM[128][8];

static void vigorously_smart_car_oled_display_write_byte(uint8_t data, uint8_t cmd)
{
    uint8_t i;

    if(cmd == 1)
        GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RS_PIN); 
    else
        GPIO_ResetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RS_PIN);

    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_CS_PIN);

    for(i = 0; i < 8; i++)
    {
        GPIO_ResetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SCLK_PIN);
    
        if(data & 0x80)
            GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SDA_PIN);
        else
            GPIO_ResetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SDA_PIN);
    
        GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SCLK_PIN);
        data <<= 1;
    }
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_CS_PIN);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RS_PIN);
}

static void vigorously_smart_car_oled_display_draw_point(uint8_t x, uint8_t y, uint8_t t)
{
    uint8_t pos = 0;
    uint8_t bx = 0;
    uint8_t temp = 0;

    if(x > 127 || y > 63)
        return;
    
    pos = 7 - y / 8;
    bx = y % 8;
    temp = 1 << (7 - bx);
    
    if(t)
        vigorously_smart_car_oled_display_GRAM[x][pos] |= temp;
    else
        vigorously_smart_car_oled_display_GRAM[x][pos] &= ~temp;
}

static uint32_t mypow(uint8_t m, uint8_t n)
{
	u32 result = 1;	 
	while(n--)
    {
        result *= m;
    }    
	return result;
}

void vigorously_smart_car_oled_display_show_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode)
{
    uint8_t temp;
    uint8_t t;
    uint8_t tl;
    uint8_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);  //得到字体一个字符对应点阵集所占的字节数

    chr = chr- ' ';    //得到偏移后的值

    for(t = 0; t < csize; t++)
    {
        if(size == 12)
            temp = asc2_1206[chr][t];
        else if(size == 16)
            temp = asc2_1608[chr][t];
        else if(size == 24)
            temp = asc2_2412[chr][t];
        else
            return;
        
        for(tl = 0; tl < 8; tl++)
        {
            if(temp & 0x80)
                vigorously_smart_car_oled_display_draw_point(x, y, mode);
            else
                vigorously_smart_car_oled_display_draw_point(x, y, !mode);
            temp <<= 1;
            y++;
            if((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

void vigorously_smart_car_oled_display_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow = 0;						   
	for(t = 0; t < len; t++)
	{
		temp = (num / mypow(10, len- t - 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			if(temp == 0)
			{
				vigorously_smart_car_oled_display_show_char(x + (size / 2) * t, y, ' ', size, 1);
				continue;
			}
            else
                enshow = 1; 
		 	 
		}
	 	vigorously_smart_car_oled_display_show_char(x + (size / 2) * t, y, temp + '0', size, 1); 
	}
}

void vigorously_smart_car_oled_display_show_string(uint8_t x, uint8_t y, uint8_t *src, uint8_t size)
{
    while((*src <= '~') && (*src >= ' '))
    {
        if(x > (128 - (size / 2)))
        {
            x = 0;
            y += size;
        }
        if(y > (64 - size))
        {
            y = x = 0;
            vigorously_smart_car_oled_display_clear();
        }
        vigorously_smart_car_oled_display_show_char(x, y, *src, size, 1);
        x += size / 2;
        src++;
    }
}

void vigorously_smart_car_oled_display_refresh_gram()
{
    uint8_t i;
    uint8_t n;

    for(i = 0; i < 8; i++)
    {
        vigorously_smart_car_oled_display_write_byte(0xb0 + i, VIGOROUSLY_SMART_CAR_OLED_CMD);
        vigorously_smart_car_oled_display_write_byte(0x00, VIGOROUSLY_SMART_CAR_OLED_CMD);
        vigorously_smart_car_oled_display_write_byte(0x10, VIGOROUSLY_SMART_CAR_OLED_CMD);
        for(n = 0; n < 128; n++)
            vigorously_smart_car_oled_display_write_byte(vigorously_smart_car_oled_display_GRAM[n][i], VIGOROUSLY_SMART_CAR_OLED_DATA);
    }
}

void vigorously_smart_car_oled_display_set_pos(uint8_t x, uint8_t y) 
{ 
	vigorously_smart_car_oled_display_write_byte(0xB0 + y,VIGOROUSLY_SMART_CAR_OLED_CMD);
	vigorously_smart_car_oled_display_write_byte(((x & 0xF0) >> 4) | 0x10,VIGOROUSLY_SMART_CAR_OLED_CMD);
	vigorously_smart_car_oled_display_write_byte((x & 0x0F) | 0x01,VIGOROUSLY_SMART_CAR_OLED_CMD); 
}  

uint8_t vigorously_smart_car_oled_display_clear()
{
    uint8_t i;
    uint8_t n;

    for(i = 0; i < 8; i++)
    {
        for(n = 0; n < 128; n++)
            vigorously_smart_car_oled_display_GRAM[n][i] = 0x00;
    }

    /* 更新显存 */
    vigorously_smart_car_oled_display_refresh_gram();
}

void vigorously_smart_car_oled_display_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_OLED_GPIO_CLOCK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_OLED_SCLK_PIN | VIGOROUSLY_SMART_CAR_OLED_SDA_PIN |\
                               VIGOROUSLY_SMART_CAR_OLED_RST_PIN | VIGOROUSLY_SMART_CAR_OLED_RS_PIN | VIGOROUSLY_SMART_CAR_OLED_CS_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_OLED_GPIOX, &GPIO_InitStruct);

    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SCLK_PIN);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_SDA_PIN);

    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_CS_PIN);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RS_PIN);

    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RST_PIN);
    bsp_abit_delay_ms(100);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_OLED_GPIOX, VIGOROUSLY_SMART_CAR_OLED_RST_PIN);

    /* 关闭显示 */
    vigorously_smart_car_oled_display_write_byte(0xAE, VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置时钟分频因子，振荡频率 */
    vigorously_smart_car_oled_display_write_byte(0xD5,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* [3:0]，分频因子；[7:4]，振荡频率 */
    vigorously_smart_car_oled_display_write_byte(0x80,VIGOROUSLY_SMART_CAR_OLED_CMD);  
    /* 设置驱动路数 */
    vigorously_smart_car_oled_display_write_byte(0xA8,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 默认0x3F(1/64) */
    vigorously_smart_car_oled_display_write_byte(0X3F,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置显示偏移 */
    vigorously_smart_car_oled_display_write_byte(0xD3,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 默认为0 */
    vigorously_smart_car_oled_display_write_byte(0X00,VIGOROUSLY_SMART_CAR_OLED_CMD);

    /* 设置显示开始行[5:0]，行数 */
    vigorously_smart_car_oled_display_write_byte(0x40,VIGOROUSLY_SMART_CAR_OLED_CMD);

    /* 电荷泵设置 */
    vigorously_smart_car_oled_display_write_byte(0x8D,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* bit2，开启/关闭 */
    vigorously_smart_car_oled_display_write_byte(0x14,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置内存地址模式 */
    vigorously_smart_car_oled_display_write_byte(0x20,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* [1:0]，
     *      00，列地址模式
     *      01，行地址模式
     *      10，页地址模式
     *      默认10
     */
    vigorously_smart_car_oled_display_write_byte(0x02,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 段重定义设置，bit0：0，0->0；1，0->127 */
    vigorously_smart_car_oled_display_write_byte(0xA1,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置COM扫描方向；bit3：0，普通模式；1，重定义模式  COM[N-1]->COM0; N：驱动路数*/
    vigorously_smart_car_oled_display_write_byte(0xC0,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置COM硬件引脚配置 */
    vigorously_smart_car_oled_display_write_byte(0xDA,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* [5:4]配置 */
    vigorously_smart_car_oled_display_write_byte(0x12,VIGOROUSLY_SMART_CAR_OLED_CMD);
    
    /* 对比度设置 */
    vigorously_smart_car_oled_display_write_byte(0x81,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 1~255；默认0x7F(亮度设置，越大越亮) */
    vigorously_smart_car_oled_display_write_byte(0xEF,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置预充电周期 */
    vigorously_smart_car_oled_display_write_byte(0xD9,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* [3:0]，PHASE 1；[7:4]，PHASE 2 */
    vigorously_smart_car_oled_display_write_byte(0xF1,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置VCOMH电压倍率 */
    vigorously_smart_car_oled_display_write_byte(0xDB,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* [6:4] 000，0.65 * VCC；001，0.77 * VCC；011，0.83 * VCC */
    vigorously_smart_car_oled_display_write_byte(0x30,VIGOROUSLY_SMART_CAR_OLED_CMD);

    /* 全局显示开启；bit0：1，开启；0，关闭(白屏/黑屏) */
    vigorously_smart_car_oled_display_write_byte(0xA4,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 设置显示方式；bit0：1，反相显示；0：正常显示 */
    vigorously_smart_car_oled_display_write_byte(0xA6,VIGOROUSLY_SMART_CAR_OLED_CMD);
    /* 开启显示 */
    vigorously_smart_car_oled_display_write_byte(0xAF,VIGOROUSLY_SMART_CAR_OLED_CMD);

    vigorously_smart_car_oled_display_clear();
}