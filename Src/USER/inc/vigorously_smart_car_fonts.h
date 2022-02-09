#ifndef __VIGOROUSLY_SMART_CAR_FONTS_H
#define __VIGOROUSLY_SMART_CAR_FONTS_H

#include "stm32f4xx.h"

#define LINEX(x)     ((x) * (((vigorously_smart_car_fonts *)vigorously_smart_car_dislpay_get_font())->Height))
#define LINEY(x)     ((x) * (((vigorously_smart_car_fonts *)vigorously_smart_car_dislpay_get_font())->Width))

typedef struct _tFont
{
    const uint8_t *fonts;
    uint16_t Width;
    uint16_t Height;
} vigorously_smart_car_fonts;

extern vigorously_smart_car_fonts Font8x16;
extern vigorously_smart_car_fonts Font16x24;
extern vigorously_smart_car_fonts Font24x32;

#endif //__VIGOROUSLY_SMART_CAR_FONTS_H