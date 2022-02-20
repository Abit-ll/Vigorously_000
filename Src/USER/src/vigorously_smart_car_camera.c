#include "vigorously_smart_car_camera.h"

/* 
 * OV2640 SXGA初始化寄存器序列表
 * 此模式下帧率为15帧
 * SXGA(1600 * 1200)
 */
uint8_t vigorously_smart_car_camera_sxga_init_reg_tbl[][2]= 
{
 	0xff, 0x01,
	0x12, 0x80,

	0xff, 0x00,
	0x2c, 0xff,
	0x2e, 0xdf,
	0xff, 0x01,
	0x3c, 0x32,

	0x11, 0x00,//此处01设置为0时，可以提高摄像头帧数，但是，设置高频率帧数时，会导致显示刷新时间不够，显示错位花屏
	0x09, 0x02,
	0x04, 0x20,//水平镜像，垂直翻转 可以通过位配置，来调整扫描方式 Bit[7]：控制水平扫描方式 Bit[6]：控制纵向扫描方式
	0x13, 0xe5,
	0x14, 0x48,
	0x2c, 0x0c,
	0x33, 0x78,
	0x3a, 0x33,
	0x3b, 0xfB,

	0x3e, 0x00,
	0x43, 0x11,
	0x16, 0x10,

	0x39, 0x92,

	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	
	0x48, 0x00,
	0x5B, 0x00,
	0x42, 0x03,

	0x4a, 0x81,
	0x21, 0x99,

	0x24, 0x40,
	0x25, 0x38,
	0x26, 0x82,
	0x5c, 0x00,
	0x63, 0x00,
	0x46, 0x00,
	0x0c, 0x3c,

	0x61, 0x70,
	0x62, 0x80,
	0x7c, 0x05,

	0x20, 0x80,
	0x28, 0x30,
	0x6c, 0x00,
	0x6d, 0x80,
	0x6e, 0x00,
	0x70, 0x02,
	0x71, 0x94,
	0x73, 0xc1, 
	0x3d, 0x34, 
	0x5a, 0x57,

	0x12, 0x00,//UXGA 1600*1200
	
	0x17, 0x11,
	0x18, 0x75,
	0x19, 0x01,
	0x1a, 0x97,
	0x32, 0x36,
	0x03, 0x0f, 
	0x37, 0x40,

	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x6d, 0x38,

	0xff, 0x00,
	0xe5, 0x7f,
	0xf9, 0xc0,
	0x41, 0x24,
	0xe0, 0x14,
	0x76, 0xff,
	0x33, 0xa0,
	0x42, 0x20,
	0x43, 0x18,
	0x4c, 0x00,
	0x87, 0xd5,
	0x88, 0x3f,
	0xd7, 0x03,
	0xd9, 0x10,
	0xd3, 0x82,

	0xc8, 0x08,
	0xc9, 0x80,

	0x7c, 0x00,
	0x7d, 0x00,
	0x7c, 0x03,
	0x7d, 0x48,
	0x7d, 0x48,
	0x7c, 0x08,
	0x7d, 0x20,
	0x7d, 0x10,
	0x7d, 0x0e,

	0x90, 0x00,
	0x91, 0x0e,
	0x91, 0x1a,
	0x91, 0x31,
	0x91, 0x5a,
	0x91, 0x69,
	0x91, 0x75,
	0x91, 0x7e,
	0x91, 0x88,
	0x91, 0x8f,
	0x91, 0x96,
	0x91, 0xa3,
	0x91, 0xaf,
	0x91, 0xc4,
	0x91, 0xd7,
	0x91, 0xe8,
	0x91, 0x20,

	0x92, 0x00,
	0x93, 0x06,
	0x93, 0xe3,
	0x93, 0x05,
	0x93, 0x05,
	0x93, 0x00,
	0x93, 0x04,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,

	0x96, 0x00,
	0x97, 0x08,
	0x97, 0x19,
	0x97, 0x02,
	0x97, 0x0c,
	0x97, 0x24,
	0x97, 0x30,
	0x97, 0x28,
	0x97, 0x26,
	0x97, 0x02,
	0x97, 0x98,
	0x97, 0x80,
	0x97, 0x00,
	0x97, 0x00,

	0xc3, 0xef,
	
	0xa4, 0x00,
	0xa8, 0x00,
	0xc5, 0x11,
	0xc6, 0x51,
	0xbf, 0x80,
	0xc7, 0x10,
	0xb6, 0x66,
	0xb8, 0xA5,
	0xb7, 0x64,
	0xb9, 0x7C,
	0xb3, 0xaf,
	0xb4, 0x97,
	0xb5, 0xFF,
	0xb0, 0xC5,
	0xb1, 0x94,
	0xb2, 0x0f,
	0xc4, 0x5c,

	0xc0, 0xc8,
	0xc1, 0x96,
	0x8c, 0x00,
	0x86, 0x3d,
	0x50, 0x00,
	0x51, 0x90,
	0x52, 0x2c,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x88,
	
	0x5a, 0x90,
	0x5b, 0x2C,
	0x5c, 0x05,
	
	0xd3, 0x02,//auto设置要小心

	0xc3, 0xed,
	0x7f, 0x00,
	
	0xda, 0x09,
	
	0xe5, 0x1f,
	0xe1, 0x67,
	0xe0, 0x00,
	0xdd, 0x7f,
	0x05, 0x00,
};

/* 
 * OV2640 SVGA初始化寄存器序列表
 * 此模式下，帧率可以达到30帧
 * SVGA 800*600
 */
uint8_t vigorously_smart_car_camera_svga_init_reg_tbl[][2]= 
{    
	0xff, 0x00,
	0x2c, 0xff,
	0x2e, 0xdf,
	0xff, 0x01,
	0x3c, 0x32,

	0x11, 0x00,
	0x09, 0x02,
	0x04, 0x20,//水平镜像，垂直翻转 可以通过位配置，来调整扫描方式 Bit[7]：控制水平扫描方式 Bit[6]：控制纵向扫描方式
	0x13, 0xe5,
	0x14, 0x48,
	0x2c, 0x0c,
	0x33, 0x78,
	0x3a, 0x33,
	0x3b, 0xfB,

	0x3e, 0x00,
	0x43, 0x11,
	0x16, 0x10,

	0x39, 0x92,

	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0x48, 0x00,
	0x5B, 0x00,
	0x42, 0x03,

	0x4a, 0x81,
	0x21, 0x99,

	0x24, 0x40,
	0x25, 0x38,
	0x26, 0x82,
	0x5c, 0x00,
	0x63, 0x00,
	0x46, 0x22,
	0x0c, 0x3c,

	0x61, 0x70,
	0x62, 0x80,
	0x7c, 0x05,

	0x20, 0x80,
	0x28, 0x30,
	0x6c, 0x00,
	0x6d, 0x80,
	0x6e, 0x00,
	0x70, 0x02,
	0x71, 0x94,
	0x73, 0xc1,
	
	0x3d, 0x34, 
	0x5a, 0x57,
	//根据分辨率不同而设置
	0x12, 0x40,//SVGA 800*600
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x37, 0xc0,

	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x3d, 0x38,

	0xff, 0x00,
	0xe5, 0x7f,
	0xf9, 0xc0,
	0x41, 0x24,
	0xe0, 0x14,
	0x76, 0xff,
	0x33, 0xa0,
	0x42, 0x20,
	0x43, 0x18,
	0x4c, 0x00,
	0x87, 0xd5,
	0x88, 0x3f,
	0xd7, 0x03,
	0xd9, 0x10,
	0xd3, 0x82,

	0xc8, 0x08,
	0xc9, 0x80,

	0x7c, 0x00,
	0x7d, 0x00,
	0x7c, 0x03,
	0x7d, 0x48,
	0x7d, 0x48,
	0x7c, 0x08,
	0x7d, 0x20,
	0x7d, 0x10,
	0x7d, 0x0e,

	0x90, 0x00,
	0x91, 0x0e,
	0x91, 0x1a,
	0x91, 0x31,
	0x91, 0x5a,
	0x91, 0x69,
	0x91, 0x75,
	0x91, 0x7e,
	0x91, 0x88,
	0x91, 0x8f,
	0x91, 0x96,
	0x91, 0xa3,
	0x91, 0xaf,
	0x91, 0xc4,
	0x91, 0xd7,
	0x91, 0xe8,
	0x91, 0x20,

	0x92, 0x00,
	0x93, 0x06,
	0x93, 0xe3,
	0x93, 0x05,
	0x93, 0x05,
	0x93, 0x00,
	0x93, 0x04,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,

	0x96, 0x00,
	0x97, 0x08,
	0x97, 0x19,
	0x97, 0x02,
	0x97, 0x0c,
	0x97, 0x24,
	0x97, 0x30,
	0x97, 0x28,
	0x97, 0x26,
	0x97, 0x02,
	0x97, 0x98,
	0x97, 0x80,
	0x97, 0x00,
	0x97, 0x00,

	0xc3, 0xed,
	0xa4, 0x00,
	0xa8, 0x00,
	0xc5, 0x11,
	0xc6, 0x51,
	0xbf, 0x80,
	0xc7, 0x10,
	0xb6, 0x66,
	0xb8, 0xA5,
	0xb7, 0x64,
	0xb9, 0x7C,
	0xb3, 0xaf,
	0xb4, 0x97,
	0xb5, 0xFF,
	0xb0, 0xC5,
	0xb1, 0x94,
	0xb2, 0x0f,
	0xc4, 0x5c,
	//根据分辨率不同而设置
	0xc0, 0x64,
	0xc1, 0x4B,
	0x8c, 0x00,
	0x86, 0x3D,
	0x50, 0x00,
	0x51, 0xC8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x5a, 0xC8,
	0x5b, 0x96,
	0x5c, 0x00,
	
	0xd3, 0x02,//auto设置要小心

	0xc3, 0xed,
	0x7f, 0x00,
	
	0xda, 0x09,
	
	0xe5, 0x1f,
	0xe1, 0x67,
	0xe0, 0x00,
	0xdd, 0x7f,
	0x05, 0x00,
};

uint8_t vigorously_smart_car_camera_jpeg_reg_tbl[][2]=
{
	0xff, 0x01, 
	0xe0, 0x14,
	0xe1, 0x77,
	0xe5, 0x1f,
	0xd7, 0x03,
	0xda, 0x10,
	0xe0, 0x00, 
};

uint8_t vigorously_smart_car_camera_rgb565_reg_tbl[][2]=
{
	0xFF, 0x00,
	0xDA, 0x09,
	0xD7, 0x03,
	0xDF, 0x02,
	0x33, 0xa0,
	0x3C, 0x00,
	0xe1, 0x67,
	
	0xff, 0x01, 
	0xe0, 0x00,
	0xe1, 0x00,
	0xe5, 0x00,
	0xd7, 0x00, 
	0xda, 0x00,
	0xe0, 0x00,  
};

uint8_t vigorously_smart_car_camera_yuv422_reg_tbl[][2]= 
{
	0xFF, 0x00, 
	0xDA, 0x10,
	0xD7, 0x03,
	0xDF, 0x00,
	0x33, 0x80,
	0x3C, 0x40,
	0xe1, 0x77,
	0x00, 0x00,
};

static void vigorously_smart_car_camera_dcmi_config()
{
    DCMI_InitTypeDef DCMI_InitStruct;
    DMA_InitTypeDef DMA_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_AHB2PeriphClockCmd(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_DCMI_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_DMA_CLOCK, ENABLE);

    DCMI_InitStruct.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
    DCMI_InitStruct.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
    DCMI_InitStruct.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
    DCMI_InitStruct.DCMI_VSPolarity = DCMI_VSPolarity_Low;
    DCMI_InitStruct.DCMI_HSPolarity = DCMI_HSPolarity_Low;
    DCMI_InitStruct.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
    DCMI_InitStruct.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
    DCMI_Init(&DCMI_InitStruct);
    
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);

    DCMI_Cmd(ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = DCMI_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStruct);

    DMA_InitStruct.DMA_Channel = DMA_Channel_1;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&DCMI->DR;
    DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&(*(__IO uint16_t *)VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_DATA);
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_BufferSize = 1;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;
    DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream1, &DMA_InitStruct);
}

static void vigorously_smart_car_camera_jpeg_mode()
{
    uint16_t i;

    for(i = 0; i < (sizeof(vigorously_smart_car_camera_yuv422_reg_tbl) / 2); i++)
        bsp_abit_sccb_write_reg(vigorously_smart_car_camera_yuv422_reg_tbl[i][0], vigorously_smart_car_camera_yuv422_reg_tbl[i][1]);
    
    for(i = 0; i < (sizeof(vigorously_smart_car_camera_jpeg_reg_tbl) / 2); i++)
        bsp_abit_sccb_write_reg(vigorously_smart_car_camera_jpeg_reg_tbl[i][0], vigorously_smart_car_camera_jpeg_reg_tbl[i][1]);
}

static void vigorously_smart_car_camera_rgb565_mode()
{
    uint16_t i;

    for(i = 0; i < (sizeof(vigorously_smart_car_camera_rgb565_reg_tbl) / 2); i++)
        bsp_abit_sccb_write_reg(vigorously_smart_car_camera_rgb565_reg_tbl[i][0], vigorously_smart_car_camera_rgb565_reg_tbl[i][1]);
}

static void vigorously_smart_car_camera_gpio_config()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PCLK_XCLK_CLOCK | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_VSYNC_D5_CLOCK |\
                           VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_CLOCK | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D6_D7_CLOCK |\
                           VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_CH1_CLOCK | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_CLOCK, ENABLE);
    
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PCLK_XCLK_GPIOX, GPIO_PinSource4, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PCLK_XCLK_GPIOX, GPIO_PinSource6, GPIO_AF_DCMI);
    // GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PCLK_XCLK_GPIOX, GPIO_PinSource8, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_VSYNC_D5_GPIOX, GPIO_PinSource7, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_VSYNC_D5_GPIOX, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, GPIO_PinSource7, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, GPIO_PinSource8, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, GPIO_PinSource9, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, GPIO_PinSource11, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D6_D7_GPIOX, GPIO_PinSource5, GPIO_AF_DCMI);
    GPIO_PinAFConfig(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D6_D7_GPIOX, GPIO_PinSource6, GPIO_AF_DCMI);
    
    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PCLK_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_HREF_PCLK_XCLK_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_VSYNC_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D5_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_VSYNC_D5_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D1_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D2_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D3_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D4_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D0_D1_D2_D3_D4_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D6_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D7_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_D6_D7_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_CH1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_CH1_GPIOX, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = (VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_PIN | VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_RESET_PIN);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_RESET_GPIOX, &GPIO_InitStruct);

    VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_CH1_LOW;
}

static uint8_t vigorously_smart_car_camera_set_outsize(uint16_t width, uint16_t height)
{
    uint16_t outwidth;
    uint16_t outheight;
    uint8_t ret;

    if(width % 4)
        return 1;
    if(height % 4)
        return 2;
    
    outwidth = width / 4;
    outheight = height / 4;

    bsp_abit_sccb_write_reg(0xFF, 0x00);
    bsp_abit_sccb_write_reg(0xE0, 0x04);
    bsp_abit_sccb_write_reg(0x5A, (outwidth & 0xFF));
    bsp_abit_sccb_write_reg(0x5B, (outheight & 0xFF));
    ret = (outwidth >> 8) & 0x03;
    ret |= (outheight >> 6) & 0x04;
    bsp_abit_sccb_write_reg(0x5C, ret);
    bsp_abit_sccb_write_reg(0xE0, 0x00);

    return 0;
}

static void vigorously_smart_car_camera_display_window(uint16_t x, uint16_t y)
{
    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_X);
    vigorously_smart_car_lcd_write_data(x >> 8);
    vigorously_smart_car_lcd_write_data(x & 0xFF);

    vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_CASET_Y);
    vigorously_smart_car_lcd_write_data(y >> 8);
    vigorously_smart_car_lcd_write_data(y & 0xFF);
}

void vigorously_camera_info_process()
{
    // vigorously_smart_car_camera_display_window(0, 0);
	vigorously_smart_car_lcd_display_open_window(VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL);
    // *(__IO uint16_t *)(VIGOROUSLY_SMART_CAR_DISAPLAY_LCD_CMD) = VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL;
	vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL);
}

void vigorously_smart_car_camera_stop()
{
    DCMI_CaptureCmd(DISABLE);
    while(DCMI->CR & 0x01);
    DMA_Cmd(DMA2_Stream1, DISABLE);
}

void vigorously_smart_car_camera_start()
{
    // vigorously_smart_car_camera_display_window(0, 0);
	vigorously_smart_car_lcd_display_open_window(VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_X_START, VIGOROUSLY_SMART_CAR_DISAPLAY_WINDOW_Y_START, VIGOROUSLY_SMART_CAR_DISPLAY_LESS_PIXEL, VIGOROUSLY_SMART_CAR_DISPLAY_MORE_PIXEL);
    
	vigorously_smart_car_lcd_write_cmd(VIGOROUSLY_SMART_CAR_DISPLAY_CMD_SET_PIXEL);
    DMA_Cmd(DMA2_Stream1, ENABLE);
    DCMI_CaptureCmd(ENABLE);
}

uint8_t  vigorously_smart_car_camera_init()
{
    uint16_t i = 0; 
    uint16_t reg;

    vigorously_smart_car_camera_gpio_config();

    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_RESET_GPIOX, VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_PIN);
    bsp_abit_delay_ms(10);
    GPIO_ResetBits(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_RESET_GPIOX, VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_RESET_PIN);
    bsp_abit_delay_ms(10);
    GPIO_SetBits(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PWDN_RESET_GPIOX, VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_RESET_PIN);

    bsp_abit_sccb_init();
    bsp_abit_sccb_write_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_DSP_RA_DLMT, 0x01);
    bsp_abit_sccb_write_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_SENSOR_COM7, 0x80);
    bsp_abit_delay_ms(50);
    reg = bsp_abit_sccb_read_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_SENSOR_MIDH);
    reg <<= 8;
    reg |= bsp_abit_sccb_read_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_SENSOR_MIDL);
    printf("MID: %x\r\n", reg);
    if(reg != VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_MID)
    {
        printf("reg1: %x\r\n", reg);
        return 1;
    }
    reg = bsp_abit_sccb_read_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_SENSOR_PIDH);
    reg <<= 8;
    reg |= bsp_abit_sccb_read_reg(VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_SENSOR_PIDL);
    printf("PID: %x\r\n", reg);
    if((reg != VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PID1) & (reg != VIGOROUSLY_SMART_CAR_DISAPLAY_CAMERA_PID2))
    {
        printf("reg2: %x\r\n", reg);
        return 2;
    }

    for(i = 0; i < (sizeof(vigorously_smart_car_camera_sxga_init_reg_tbl) / 2); i++)
    {
        bsp_abit_sccb_write_reg(vigorously_smart_car_camera_sxga_init_reg_tbl[i][0], vigorously_smart_car_camera_sxga_init_reg_tbl[i][1]);
        if(i < 10)
            bsp_abit_delay_ms(5);
    }

    vigorously_smart_car_camera_rgb565_mode();

    vigorously_smart_car_camera_dcmi_config();

    vigorously_smart_car_camera_set_outsize(vigorously_smart_car_lcd.vigorously_smart_car_display_x_length, vigorously_smart_car_lcd.vigorously_smart_car_display_y_length);

    return 0;
}