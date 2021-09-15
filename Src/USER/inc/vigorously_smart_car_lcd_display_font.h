#ifndef __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_FONT_H
#define __VIGOROUSLY_SMART_CAR_LCD_DISPLAY_FONT_H 

#include "stm32f4xx.h"

#define LINE(x) ((x) * (((vigorously_smart_car_font *)vigorously_smart_car_display_get_font())->Height))
#define LINEY(x) ((x) * (((vigorously_smart_car_font *)vigorously_smart_car_display_get_font())->Width))

typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} vigorously_smart_car_font;

extern vigorously_smart_car_font Font24x32;
extern vigorously_smart_car_font Font16x24;
extern vigorously_smart_car_font Font8x16;

extern vigorously_smart_car_font *vigorously_smart_car_display_current_fonts;

void vigorously_smart_car_display_set_font(vigorously_smart_car_font *fonts);

vigorously_smart_car_font *vigorously_smart_car_display_get_font();

#endif //__VIGOROUSLY_SMART_CAR_LCD_DISPLAY_FONT_H