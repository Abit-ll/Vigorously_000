#include "vigorously_smart_car_lcd_display.h"

vigorously_smart_car_lcd_param vigorously_smart_car_lcd;
vigorously_smart_car_fonts *vigorously_smart_car_current_font;

void vigorously_smart_car_lcd_write_cmd(uint16_t cmd)
{
    bsp_abit_delay_us(1);
    *(__IO uint16_t *)(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_CMD) = cmd;
}

uint16_t vigorously_smart_car_lcd_read_data()
{
    return (*(__IO uint16_t *)(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_DATA));
}

void vigorously_smart_car_lcd_write_data(uint16_t data)
{
    bsp_abit_delay_us(1);
    *(__IO uint16_t *)(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_DATA) = data;
}

static uint16_t vigorously_smart_car_lcd_read_id()
{
    uint16_t data;

    vigorously_smart_car_lcd_write_cmd(0xD3);

    data = vigorously_smart_car_lcd_read_data();
    data = vigorously_smart_car_lcd_read_data();
    data = vigorously_smart_car_lcd_read_data();
    data <<= 8;
    data |= vigorously_smart_car_lcd_read_data();

    return data;
}

void vigorously_smart_car_lcd_display_open_window(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_X);
    vigorously_smart_car_lcd_write_data(x >> 8);
    vigorously_smart_car_lcd_write_data(x & 0xFF);
    vigorously_smart_car_lcd_write_data((x + width - 1) >> 8);
    vigorously_smart_car_lcd_write_data((x + width - 1) & 0xFF);

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_Y);
    vigorously_smart_car_lcd_write_data(y >> 8);
    vigorously_smart_car_lcd_write_data(y & 0xFF);
    vigorously_smart_car_lcd_write_data((y + height - 1) >> 8);
    vigorously_smart_car_lcd_write_data((y + height - 1) & 0xFF);
}

static void vigorously_smart_car_dislpay_chr_en(uint16_t x, uint16_t y, uint8_t ch)
{
    uint8_t fsize;
    uint16_t position;
    uint8_t bytecount;
    uint8_t bitcount;
    uint8_t *font;

    /* 对ASCII码表偏移（字模表不包含ASCII表的前32个非图形符号） */
    position = ch - ' ';

    fsize = (vigorously_smart_car_current_font->Width * vigorously_smart_car_current_font->Height) / 8;

    font = (uint8_t *)&vigorously_smart_car_current_font->fonts[position * fsize];

    vigorously_smart_car_lcd_display_open_window(x, y, vigorously_smart_car_current_font->Width, vigorously_smart_car_current_font->Height);

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL);

    for(bytecount = 0; bytecount < fsize; bytecount++)
    {
        for(bitcount = 0; bitcount < 8; bitcount++)
        {
            if(font[bytecount] & (0x80 >> bitcount))
                vigorously_smart_car_lcd_write_data(vigorously_smart_car_lcd.vigorously_smart_car_display_current_text_color);
            else
                vigorously_smart_car_lcd_write_data(vigorously_smart_car_lcd.vigorously_smart_car_display_current_back_color);
        }
    }

}

static void vigorously_smart_car_lcd_config(vigorously_smart_car_fonts *fonts)
{
    vigorously_smart_car_lcd.vigorously_smart_car_display_scan_mode = 6;
    vigorously_smart_car_lcd.vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL;
    vigorously_smart_car_lcd.vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL;
    vigorously_smart_car_lcd.vigorously_smart_car_display_current_text_color = VIGOROUSLY_SMART_CAR_DISPLAY_BLACK;
    vigorously_smart_car_lcd.vigorously_smart_car_display_current_back_color = VIGOROUSLY_SMART_CAR_DISPLAY_BLACK;
    vigorously_smart_car_current_font = fonts;
}

static void vigorously_smart_car_lcd_rgb_config()
{
    vigorously_smart_car_lcd_write_cmd(0xCF);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0xC1);
    vigorously_smart_car_lcd_write_data(0X30);

    vigorously_smart_car_lcd_write_cmd(0xED);
    vigorously_smart_car_lcd_write_data(0x64);
    vigorously_smart_car_lcd_write_data(0x03);
    vigorously_smart_car_lcd_write_data(0X12);
    vigorously_smart_car_lcd_write_data(0X81);

    vigorously_smart_car_lcd_write_cmd(0xE8);
    vigorously_smart_car_lcd_write_data(0x85);
    vigorously_smart_car_lcd_write_data(0x10);
    vigorously_smart_car_lcd_write_data(0x7A);

    vigorously_smart_car_lcd_write_cmd(0xCB);
    vigorously_smart_car_lcd_write_data(0x39);
    vigorously_smart_car_lcd_write_data(0x2C);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x34);
    vigorously_smart_car_lcd_write_data(0x02);

    vigorously_smart_car_lcd_write_cmd(0xF7);
    vigorously_smart_car_lcd_write_data(0x20);

    vigorously_smart_car_lcd_write_cmd(0xEA);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);

    vigorously_smart_car_lcd_write_cmd(0xC0);
    vigorously_smart_car_lcd_write_data(0x1B);

    vigorously_smart_car_lcd_write_cmd(0xC1);
    vigorously_smart_car_lcd_write_data(0x01);

    vigorously_smart_car_lcd_write_cmd(0xC5);
    vigorously_smart_car_lcd_write_data(0x30);
    vigorously_smart_car_lcd_write_data(0x30);

    vigorously_smart_car_lcd_write_cmd(0xC7);
    vigorously_smart_car_lcd_write_data(0XB7);

    vigorously_smart_car_lcd_write_cmd(0x36);
    vigorously_smart_car_lcd_write_data(0x48);

    vigorously_smart_car_lcd_write_cmd(0x3A);
    vigorously_smart_car_lcd_write_data(0x55);

    vigorously_smart_car_lcd_write_cmd(0xB1);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x1A);

    vigorously_smart_car_lcd_write_cmd(0xB6); 
    vigorously_smart_car_lcd_write_data(0x0A);
    vigorously_smart_car_lcd_write_data(0xA2);

    vigorously_smart_car_lcd_write_cmd(0xF2);
    vigorously_smart_car_lcd_write_data(0x00);

    vigorously_smart_car_lcd_write_cmd(0x26);
    vigorously_smart_car_lcd_write_data(0x01);

    vigorously_smart_car_lcd_write_cmd(0xE0); 
    vigorously_smart_car_lcd_write_data(0x0F);
    vigorously_smart_car_lcd_write_data(0x2A);
    vigorously_smart_car_lcd_write_data(0x28);
    vigorously_smart_car_lcd_write_data(0x08);
    vigorously_smart_car_lcd_write_data(0x0E);
    vigorously_smart_car_lcd_write_data(0x08);
    vigorously_smart_car_lcd_write_data(0x54);
    vigorously_smart_car_lcd_write_data(0XA9);
    vigorously_smart_car_lcd_write_data(0x43);
    vigorously_smart_car_lcd_write_data(0x0A);
    vigorously_smart_car_lcd_write_data(0x0F);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);

    vigorously_smart_car_lcd_write_cmd(0XE1); 
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x15);
    vigorously_smart_car_lcd_write_data(0x17);
    vigorously_smart_car_lcd_write_data(0x07);
    vigorously_smart_car_lcd_write_data(0x11);
    vigorously_smart_car_lcd_write_data(0x06);
    vigorously_smart_car_lcd_write_data(0x2B);
    vigorously_smart_car_lcd_write_data(0x56);
    vigorously_smart_car_lcd_write_data(0x3C);
    vigorously_smart_car_lcd_write_data(0x05);
    vigorously_smart_car_lcd_write_data(0x10);
    vigorously_smart_car_lcd_write_data(0x0F);
    vigorously_smart_car_lcd_write_data(0x3F);
    vigorously_smart_car_lcd_write_data(0x3F);
    vigorously_smart_car_lcd_write_data(0x0F);

    vigorously_smart_car_lcd_write_cmd(0x2B);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x01);
    vigorously_smart_car_lcd_write_data(0x3f);

    vigorously_smart_car_lcd_write_cmd(0x2A);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0xef);

    vigorously_smart_car_lcd_write_cmd(0x11);
    bsp_abit_delay_ms(100);

    vigorously_smart_car_lcd_write_cmd(0x29);
}

static void vigorously_smart_car_lcd_bl_cmd(FunctionalState state)
{
    if(state)
        GPIO_SetBits(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_GPIOX, VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_PIN);
    else
        GPIO_ResetBits(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_GPIOX, VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_PIN);
}

static void vigorously_smart_car_lcd_fsmc_config()
{
    FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct;
    FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStruct;
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;

    RCC_AHB3PeriphClockCmd(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_FSMC_CLOCK, ENABLE);

    FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 0xF;
    FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 0x00;
    FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 60;
    FSMC_ReadWriteTimingStruct.FSMC_DataLatency = 0x00;
    FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 0x00;
    FSMC_ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;
    FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;

    FSMC_WriteTimingStruct.FSMC_AddressSetupTime = 3;
    FSMC_WriteTimingStruct.FSMC_AddressHoldTime = 0x00;
    FSMC_WriteTimingStruct.FSMC_DataSetupTime = 2;
    FSMC_WriteTimingStruct.FSMC_DataLatency = 0x00;
    FSMC_WriteTimingStruct.FSMC_CLKDivision = 0x00;
    FSMC_WriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;
    FSMC_WriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;

    FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM4;
    FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct;
    FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = &FSMC_WriteTimingStruct;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
   
}

static void vigorously_smart_car_lcd_gpio_config()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_CLOCK | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_CLOCK |\
                           VIGOROUSLY_SMART_CAR_DISPLAY_LCD_RS_CLOCK | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_CS_TFT_CLOCK |\
                           VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_CLOCK, ENABLE);
    
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource0, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource1, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource4, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource5, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource8, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource9, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, GPIO_PinSource15, GPIO_AF_FSMC);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource7, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource8, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource9, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource11, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource13, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, GPIO_PinSource15, GPIO_AF_FSMC);

    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_RS_GPIOX, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_CS_TFT_GPIOX, GPIO_PinSource12, GPIO_AF_FSMC);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_BL_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D00_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D01_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D02_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D03_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D13_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D14_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D15_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_RD_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_WR_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_RD_WR_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D04_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D05_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D06_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D07_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D08_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D09_PIN |\
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D10_PIN | VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D11_PIN | \
                                VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D12_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_D_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISPLAY_LCD_RS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_RS_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISPLAY_LCD_CS_TFT_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISPLAY_LCD_CS_TFT_GPIOX, &GPIO_InitStruct);
}

vigorously_smart_car_fonts *vigorously_smart_car_dislpay_get_font()
{
    return vigorously_smart_car_current_font;
}

void vigorously_smart_car_dislpay_set_font(vigorously_smart_car_fonts *font)
{
    vigorously_smart_car_current_font = font;
}

void vigorously_smart_car_dislpay_get_color(uint16_t *textcolor, uint16_t *backcolor)
{
    *textcolor = vigorously_smart_car_lcd.vigorously_smart_car_display_current_text_color;
    *backcolor = vigorously_smart_car_lcd.vigorously_smart_car_display_current_back_color;
}

void vigorously_smart_car_dislpay_set_color(uint16_t textcolor, uint16_t backcolor)
{
    vigorously_smart_car_lcd.vigorously_smart_car_display_current_text_color = textcolor;
    vigorously_smart_car_lcd.vigorously_smart_car_display_current_back_color = backcolor;
}

void vigorously_smart_car_lcd_display_fill_color(uint32_t point, uint16_t color)
{
    uint32_t i = 0;

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL);

    for(i = 0; i < point; i++)
        vigorously_smart_car_lcd_write_data(color);
}

void vigorously_smart_car_lcd_display_gram_scan(uint8_t option)
{
    if(option > 7)
        return;
    
    vigorously_smart_car_lcd.vigorously_smart_car_display_scan_mode = option;

    if(option % 2 == 0)
    {
        vigorously_smart_car_lcd.vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL;
        vigorously_smart_car_lcd.vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL;
    }
    else
    {
        vigorously_smart_car_lcd.vigorously_smart_car_display_x_length = VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL;
        vigorously_smart_car_lcd.vigorously_smart_car_display_y_length = VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL;
    }

    vigorously_smart_car_lcd_write_cmd(0x36);
    vigorously_smart_car_lcd_write_data((0x08 | (option << 5)));

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_X);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(((vigorously_smart_car_lcd.vigorously_smart_car_display_x_length - 1) >> 8) & 0xFF);
    vigorously_smart_car_lcd_write_data((vigorously_smart_car_lcd.vigorously_smart_car_display_x_length - 1) & 0xFF);

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_Y);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(0x00);
    vigorously_smart_car_lcd_write_data(((vigorously_smart_car_lcd.vigorously_smart_car_display_y_length - 1) >> 8) & 0xFF);
    vigorously_smart_car_lcd_write_data((vigorously_smart_car_lcd.vigorously_smart_car_display_x_length - 1) & 0xFF);

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL);
}

void vigorously_smart_car_lcd_display_en(uint16_t line, uint8_t *pstr)
{
    uint16_t x = 0;

    while(*pstr != '\0')
    {
        if((x - VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START + vigorously_smart_car_current_font->Width) > vigorously_smart_car_lcd.vigorously_smart_car_display_x_length)
        {
            x = VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START;
            line += vigorously_smart_car_current_font->Height;
        }
        if((line - VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_Y_START + vigorously_smart_car_current_font->Height) > vigorously_smart_car_lcd.vigorously_smart_car_display_y_length)
        {
            x = VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_X_START;
            line = VIGOROUSLY_SMART_CAR_DISPLAY_WINDOW_Y_START;
        }

        vigorously_smart_car_dislpay_chr_en(x, line, *pstr);
        pstr++;
        x += vigorously_smart_car_current_font->Width;
    }
}

void vigorously_smart_car_lcd_display_clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    vigorously_smart_car_lcd_display_open_window(x, y, width, height);
    vigorously_smart_car_lcd_display_fill_color(width * height, color);
}

void vigorously_smart_car_lcd_display_clear_line(uint16_t line, uint16_t color)
{
    vigorously_smart_car_lcd_display_clear(0, line, vigorously_smart_car_lcd.vigorously_smart_car_display_x_length, ((vigorously_smart_car_fonts *)vigorously_smart_car_dislpay_get_font())->Height, color);
}

void vigorously_smart_car_lcd_init(vigorously_smart_car_fonts *font)
{
    uint16_t lcd_id;

    vigorously_smart_car_lcd_config(font);
    vigorously_smart_car_lcd_gpio_config();
    vigorously_smart_car_lcd_fsmc_config();
    vigorously_smart_car_lcd_bl_cmd(ENABLE);
    vigorously_smart_car_lcd_rgb_config();

    lcd_id = vigorously_smart_car_lcd_read_id();
    printf("lcd_id = %x\r\n", lcd_id);
}