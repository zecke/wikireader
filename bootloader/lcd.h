#ifndef LCD_H
#define LCD_H

void lcd_init(void);
#define LCD_VRAM	(0x10100000)
#define LCD_VRAM_SIZE	((320 * 240) / 2)

#endif /* LCD_H */

