#include "vigorously_smart_car_lcd_display.h"

uint8_t vigorously_smart_car_display_scan_mode = 6;

uint16_t vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISAPLAY_LESS_PIXEL;
uint16_t vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISAPLAY_MORE_PIXEL;

static uint16_t vigorously_smart_car_display_current_text_color   = VIGOROUSLY_SMART_CAR_DISAPLAY_BLACK;//前景色
static uint16_t vigorously_smart_car_display_current_back_color   = VIGOROUSLY_SMART_CAR_DISAPLAY_WHITE;//背景色

/* 向ILI9341写入命令
 * cmd：要写入的命令（表寄存器地址）
 */
static void vigorously_smart_car_display_write_cmd(uint16_t cmd)
{
    *(__IO uint16_t *) (VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD) = cmd;
}

/* 向ILI9341写入数据
 * data：要写入的数据（表寄存器地址）
 */
static void vigorously_smart_car_display_write_data(uint16_t data)
{
    *(__IO uint16_t *) (VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DATA) = data;
}

static uint16_t vigorously_smart_car_display_read_data()
{
    return (*(__IO uint16_t *) (VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DATA));
}

static void vigorously_smart_car_display_gpio_config()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0 | GPIO_PinSource1 | GPIO_PinSource8 | GPIO_PinSource9 | GPIO_PinSource10 | GPIO_PinSource14 | GPIO_PinSource15, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 | GPIO_PinSource8 | GPIO_PinSource9 | GPIO_PinSource10 | GPIO_PinSource11 | GPIO_PinSource12 | GPIO_PinSource13 | GPIO_PinSource14 | GPIO_PinSource15, GPIO_AF_FSMC);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D00_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D01_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D02_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D03_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D13_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D14_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D15_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D04_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D05_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D06_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D07_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D08_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D09_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D10_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D11_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D12_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_D_GPIO, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RD_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_WR_PIN |\
                               VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DC_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CTRL_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_GPIOX, &GPIO_InitStruct);
}

static void vigorously_smart_car_display_fsmc_config()
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
    FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStruct;

    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    FSMC_NORSRAMTimingInitStruct.FSMC_AddressSetupTime = 1;
    FSMC_NORSRAMTimingInitStruct.FSMC_AddressHoldTime = 0;
    FSMC_NORSRAMTimingInitStruct.FSMC_DataSetupTime = 4;
    FSMC_NORSRAMTimingInitStruct.FSMC_BusTurnAroundDuration = 0;
    FSMC_NORSRAMTimingInitStruct.FSMC_CLKDivision = 0;
    FSMC_NORSRAMTimingInitStruct.FSMC_DataLatency = 0;
    FSMC_NORSRAMTimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_B;

    FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStruct;
    FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStruct;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

static void vigorously_smart_car_display_bl_cmd(FunctionalState status)
{
    if(status)
        GPIO_ResetBits(GPIOD, VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_PIN);
    else
        GPIO_SetBits(GPIOD, VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_BL_PIN);
}

static void vigorously_smart_car_display_rst()
{
    /* 低电平复位 */
    GPIO_ResetBits(GPIOE, VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_PIN);
    bsp_abit_delay_ms(100);
    GPIO_SetBits(GPIOE, VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_RES_PIN);
    bsp_abit_delay_ms(100);
}

static void vigorously_smart_car_display_rgb_config()
{
    /* Power control B (CFh) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xCF);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x81);
    vigorously_smart_car_display_write_data(0x30);

    /*  Power on sequence control (EDh) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xED);
    vigorously_smart_car_display_write_data(0x64);
    vigorously_smart_car_display_write_data(0x03);
    vigorously_smart_car_display_write_data(0x12);
    vigorously_smart_car_display_write_data(0x81);

    /* Driver timing control A  (E8h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xE8);
    vigorously_smart_car_display_write_data(0x85);
    vigorously_smart_car_display_write_data(0x10);
    vigorously_smart_car_display_write_data(0x78);

    /* Power control A (CBh) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xCB);
    vigorously_smart_car_display_write_data(0x39);
    vigorously_smart_car_display_write_data(0x2C);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x34);
    vigorously_smart_car_display_write_data(0x02);

    /* Pump ratio control (F7h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xF7);
    vigorously_smart_car_display_write_data(0x20);

    /* Driver timing control B (EAh) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xEA);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);

    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xB1);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x1B);

    /* Display Function Control (B6h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xB6);
    vigorously_smart_car_display_write_data(0x0A);
    vigorously_smart_car_display_write_data(0xA2);

    /* Power Control 1 (C0h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xC0);
    vigorously_smart_car_display_write_data(0x35);

    /* Power Control 2 (C1h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0xC1);
    vigorously_smart_car_display_write_data(0x11);

    /* VCOM Control 1 (C5h) */
    vigorously_smart_car_display_write_cmd(0xC5);
    vigorously_smart_car_display_write_data(0x45);
    vigorously_smart_car_display_write_data(0x45);

    /* VCOM Control 2 (C7h) */
    vigorously_smart_car_display_write_cmd(0xC7);
    vigorously_smart_car_display_write_data(0xA2);

    /* Enable 3G (F2h) */
    vigorously_smart_car_display_write_cmd(0xF2);
    vigorously_smart_car_display_write_data(0x00);

    /* Gamma Set (26h) */
    vigorously_smart_car_display_write_cmd(0x26);
    vigorously_smart_car_display_write_data(0x01);
    
    /* Positive Gamma Correction */
    vigorously_smart_car_display_write_cmd(0xE0);
    vigorously_smart_car_display_write_data(0x0F);
    vigorously_smart_car_display_write_data(0x26);
    vigorously_smart_car_display_write_data(0x24);
    vigorously_smart_car_display_write_data(0x0B);
    vigorously_smart_car_display_write_data(0x0E);
    vigorously_smart_car_display_write_data(0x09);
    vigorously_smart_car_display_write_data(0x54);
    vigorously_smart_car_display_write_data(0xA8);
    vigorously_smart_car_display_write_data(0x46);
    vigorously_smart_car_display_write_data(0x0C);
    vigorously_smart_car_display_write_data(0x17);
    vigorously_smart_car_display_write_data(0x09);
    vigorously_smart_car_display_write_data(0x0F);
    vigorously_smart_car_display_write_data(0x07);
    vigorously_smart_car_display_write_data(0x00);

    /* Negative Gamma Correction (E1h) */
    vigorously_smart_car_display_write_cmd(0xE1);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x19);
    vigorously_smart_car_display_write_data(0x1B);
    vigorously_smart_car_display_write_data(0x04);
    vigorously_smart_car_display_write_data(0x10);
    vigorously_smart_car_display_write_data(0x07);
    vigorously_smart_car_display_write_data(0x2A);
    vigorously_smart_car_display_write_data(0x47);
    vigorously_smart_car_display_write_data(0x39);
    vigorously_smart_car_display_write_data(0x03);
    vigorously_smart_car_display_write_data(0x06);
    vigorously_smart_car_display_write_data(0x06);
    vigorously_smart_car_display_write_data(0x30);
    vigorously_smart_car_display_write_data(0x38);
    vigorously_smart_car_display_write_data(0x0F);

    /* Memory Access Control Set (36h) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0x36);
    vigorously_smart_car_display_write_data(0xC8);   /* 竖屏 左上角（起点）到右下角（终点）扫描方式 */

    /* Column Address Control Set () */
    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_X);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0xEF);

    /* Page Address Control Set () */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_Y);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x01);
    vigorously_smart_car_display_write_data(0x3F);

    /* Pixel Format Set (3Ah) */
    bsp_abit_delay_ms(100);
    vigorously_smart_car_display_write_cmd(0x3A);
    vigorously_smart_car_display_write_data(0x55);

    /* Sleep Out (11h) */
    vigorously_smart_car_display_write_cmd(0x11);
    vigorously_smart_car_display_write_data(0xAFFF << 2);
    bsp_abit_delay_ms(100);

    /* Display On (29h) */
    vigorously_smart_car_display_write_cmd(0x29);
}

static void vigorously_smart_car_display_open_window(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_X);
    vigorously_smart_car_display_write_data(x >> 8);
    vigorously_smart_car_display_write_data(x & 0xFF);
    vigorously_smart_car_display_write_data((x + width - 1) >> 8);
    vigorously_smart_car_display_write_data((x + width - 1) & 0xFF);

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_Y);
    vigorously_smart_car_display_write_data(y >> 8);
    vigorously_smart_car_display_write_data(y & 0xFF);
    vigorously_smart_car_display_write_data((y + height - 1) >> 8);
    vigorously_smart_car_display_write_data((y + height - 1) & 0xFF);
}

static vigorously_smart_car_display_fill_color(uint32_t point, uint16_t color)
{
    uint32_t i = 0;

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_PIXEL);

    for(i = 0; i < point; i++)
        vigorously_smart_car_display_write_data(color);
}

static void vigorously_smart_car_display_chr_en(uint16_t x, uint16_t y, const uint8_t chr)
{
    uint8_t bytecount;
    uint8_t bitcount;
    uint8_t fontlength;
    uint16_t relativeposition;
    uint8_t *font;

    /* 对ascii码表偏移（字模表不包含ASCII表的前32个非图形符号） */
    relativeposition = chr - ' ';

    /* 每个字模的字节数 */
    fontlength = (vigorously_smart_car_display_current_fonts->Width * vigorously_smart_car_display_current_fonts->Height) / 8;

    /* 字模首地址
     * ascii码表偏移值乘以每个字模的字节数，求出字模的偏移位置
     */
    font = (uint8_t *)&vigorously_smart_car_display_current_fonts->table[relativeposition * fontlength];

    /* 设置显示窗口 */
    vigorously_smart_car_display_open_window(x, y, vigorously_smart_car_display_current_fonts->Width, vigorously_smart_car_display_current_fonts->Height);

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_PIXEL);

    /* 按字节读取字模数据
     * 由于前面直接设置了显示窗口，显示数据会自动换行
     */
    for(bytecount = 0; bytecount < fontlength; bytecount++)
    {
        /* 一位一位处理要显示的颜色 */
        for(bitcount = 0; bitcount < 8; bitcount++)
        {
            if(font[bytecount] & (0x80 >> bitcount))
                vigorously_smart_car_display_write_data(vigorously_smart_car_display_current_text_color);
            else
                vigorously_smart_car_display_write_data(vigorously_smart_car_display_current_back_color);
        }
    }
}

void vigorously_smart_car_display_clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    vigorously_smart_car_display_open_window(x, y, width, height);
    vigorously_smart_car_display_fill_color(width * height, vigorously_smart_car_display_current_back_color);
}

void vigorously_smart_car_display_clear_line(uint16_t line)
{
    vigorously_smart_car_display_clear(0, line, vigorously_smart_car_display_x_length, ((vigorously_smart_car_font*) vigorously_smart_car_display_get_font())->Height);
}

void vigorously_smart_car_display_set_color(uint16_t text_color, uint16_t back_color)
{
    vigorously_smart_car_display_current_text_color = text_color;
    vigorously_smart_car_display_current_back_color = back_color;
}

void vigorously_smart_car_display_gram_scan(uint8_t option)
{
    if(option > 7)
        return;
    
    vigorously_smart_car_display_scan_mode = option;

    if(option % 2 == 0)
    {
        /* 0 2 4 6模式下X方向像素宽度位240，Y方向位320 */
        vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISAPLAY_LESS_PIXEL;
        vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISAPLAY_MORE_PIXEL;
    }
    else
    {
        /* 0 2 4 6模式下X方向像素宽度位320，Y方向位240 */
        vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISAPLAY_MORE_PIXEL;
        vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISAPLAY_LESS_PIXEL;
    }

    vigorously_smart_car_display_write_cmd(0x36);
    vigorously_smart_car_display_write_data(0x08 | (option << 5));

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_X);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(((vigorously_smart_car_display_x_length - 1) >> 8) & 0xFF);
    vigorously_smart_car_display_write_data((vigorously_smart_car_display_x_length - 1) & 0xFF);

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_COORDINATE_Y);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(0x00);
    vigorously_smart_car_display_write_data(((vigorously_smart_car_display_y_length - 1) >> 8) & 0xFF);
    vigorously_smart_car_display_write_data((vigorously_smart_car_display_y_length - 1) & 0xFF);

    vigorously_smart_car_display_write_cmd(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD_SET_PIXEL);
}

uint16_t vigorously_smart_car_display_read_id()
{
    uint16_t data;

    vigorously_smart_car_display_write_cmd(0xD3);

    data = vigorously_smart_car_display_read_data();
    data = vigorously_smart_car_display_read_data();
    data = vigorously_smart_car_display_read_data();
    data <<= 8;
    data |= vigorously_smart_car_display_read_data();

    return data;
}

void vigorously_smart_car_display_en(uint16_t line, uint8_t *pstr)
{
    uint16_t x = 0;

    while(*pstr != '\0')
    {
        if((x - VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START + vigorously_smart_car_display_current_fonts->Width) > vigorously_smart_car_display_x_length)
        {
            x = VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START;
            line += vigorously_smart_car_display_current_fonts->Height;
        }
        if((line - VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START + vigorously_smart_car_display_current_fonts->Height) > vigorously_smart_car_display_y_length)
        {
            x = VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START;
            line = VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START;
        }

        vigorously_smart_car_display_chr_en(x, line, *pstr);
        pstr++;
        x += vigorously_smart_car_display_current_fonts->Width;
    }
}

void vigorously_smart_car_display_init()
{
    vigorously_smart_car_display_gpio_config();
    vigorously_smart_car_display_fsmc_config();
    vigorously_smart_car_display_bl_cmd(ENABLE);
    vigorously_smart_car_display_rst();
    vigorously_smart_car_display_rgb_config();

    /* 设置默认扫描方向，其中6模式位大部分液晶例程的默认显示方向 */
    vigorously_smart_car_display_gram_scan(vigorously_smart_car_display_scan_mode);
}