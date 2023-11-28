#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H



#include <stdlib.h>
#include "n32g45x.h"





extern void lcd_write_index(uint8_t index);
extern void lcd_write_data(uint8_t data);
extern void lcd_write_data_16bit(uint8_t datah,uint8_t datal);
extern void lcd_write_index_with_data(uint8_t index, uint8_t size, const uint8_t* buffer);

extern void lcd_set_xy(uint16_t x,uint16_t y);


#endif /* LCD_DRIVER_H */
