#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"  

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430

#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F 
#define LGRAY 			 0XC618 
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12
	    															  
/*  nv3401  */
void nv3401_gpio_init(void);
void nv3401_lcd_init(void);
void lcd_read_id();
#endif  
	 
	 



