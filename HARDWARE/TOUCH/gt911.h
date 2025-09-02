#ifndef __GT911_H__
#define __GT911_H__
#include "sys.h"

#define GT911_RESET_PIN GPIO_PIN_4
#define GT911_INT_PIN GPIO_PIN_5
#define GT911_ADDRESS 0x14
#define GT911_ADDRESS_W 0x28
#define GT911_ADDRESS_R 0x29

//GT911 register
#define GT_CTRL_REG 	0X8040
#define GT_CFGS_REG 	0X8047
#define GT_CHECK_REG 	0X80FF   	
#define GT_PID_REG 		0X8140   	

#define GT_GSTID_REG 	0X814E  

#define GT_TPD_Sta		0X8150
#define GT_TP1_REG 		0X8150
#define GT_TP2_REG 		0X8158
#define GT_TP3_REG 		0X8160
#define GT_TP4_REG 		0X8168
#define GT_TP5_REG 		0X8170

#define GT_TOUCH_MAX	5

typedef enum
{
	X_L = 0,
	X_H = 1,
	Y_L = 2,
	Y_H = 3,
	S_L	= 4,
	S_H = 5
}Data_XYS_P;

typedef enum
{
	TOUCH_NO		= 0x00,	//no touch
	TOUCH_ING		= 0x80	//touch 
}TOUCH_STATE_enum;	//touch state

typedef struct
{
	uint16_t	x;	//X pos
	uint16_t	y;	//Y pos
	uint16_t	s;	//size
}XY_Coordinate;	


typedef struct
{
	uint8_t state;
	uint8_t number;
	uint8_t isTouch;
	XY_Coordinate xy[GT_TOUCH_MAX];
}Touch_Struct;


void gt911_init(void);
void GTP911_Test(void);
void gt911_getId(void);
#endif

