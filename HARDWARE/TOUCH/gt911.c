#include "gt911.h"
#include "ctiic.h"

static I2C_HandleTypeDef hi2c1;

Touch_Struct TouchDev;

#if  0
const uint8_t CTP_CFG_GT911[] =  {
0x41,0x20,0x03,0xE0,0x01,0x05,0x3D,0x00,0x01,0x08,
0x1E,0x05,0x3C,0x3C,0x03,0x05,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1A,0x1C,0x1E,0x14,0x8A,0x2A,0x0C,
0x2A,0x28,0xEB,0x04,0x00,0x00,0x01,0x61,0x03,0x2C,
0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x14,0x3C,0x94,0xC5,0x02,0x08,0x00,0x00,0x04,
0xB7,0x16,0x00,0x9F,0x1B,0x00,0x8B,0x22,0x00,0x7B,
0x2B,0x00,0x70,0x36,0x00,0x70,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x24,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,
0x18,0x16,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0A,0x00
};
#endif

static uint8_t GT911_WriteReg(uint16_t reg,uint8_t *buf,uint8_t len);
static void GT911_ReadReg(uint16_t reg,uint8_t *buf,uint8_t len);

void gt911_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    CT_IIC_Init();

    GPIO_InitTypeDef gpio_initure = {0};
	
	gpio_initure.Pin = GT911_RESET_PIN;
	gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
	gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
	gpio_initure.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA,&gpio_initure); 

    gpio_initure.Pin = GT911_INT_PIN;
    gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &gpio_initure);
    
    HAL_GPIO_WritePin(GPIOA, GT911_RESET_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GT911_INT_PIN, GPIO_PIN_RESET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(GPIOA, GT911_INT_PIN, GPIO_PIN_SET);

    HAL_Delay(50);
    
    HAL_GPIO_WritePin(GPIOA, GT911_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(50);

    gpio_initure.Pin = GT911_INT_PIN;
    gpio_initure.Mode = GPIO_MODE_IT_FALLING;
    gpio_initure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio_initure);

    // HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
    // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    HAL_Delay(50);

    uint8_t _temp=0;
/*
    uint8_t crc = 0;

	for(uint32_t i = 0; i < sizeof(GT911_CFG_TBL) - 2; i++)
        crc += GT911_CFG_TBL[i];

    GT911_CFG_TBL[sizeof(GT911_CFG_TBL)-2] = (~crc) + 1;
    GT911_CFG_TBL[sizeof(GT911_CFG_TBL)-1] = 0xff;
    // 转换为软复位模式
    _temp=2;	//中间变量
    GT911_WriteReg(GT_CTRL_REG, &_temp, 1);
    HAL_Delay(10);
   
    // 写入配置表
    GT911_WriteReg(GT_CFGS_REG,(uint8_t*)GT911_CFG_TBL,sizeof(GT911_CFG_TBL));//发送寄存器配置
   
   //GT911_WriteReg(GT_CFGS_REG, (uint8_t *)GT911_CFG_TBL, sizeof(GT911_CFG_TBL));
   HAL_Delay(10);
*/
    _temp=0;
    GT911_WriteReg(GT_CTRL_REG, &_temp, 1);

    TouchDev.isTouch = 0;
    TouchDev.number = 0;
    TouchDev.state = 0;
}


void gt911_scanf(void)
{
	uint8_t _temp = 0;	

	GT911_ReadReg(GT_GSTID_REG, &_temp, 1);

    TouchDev.state = _temp;

	TouchDev.number = (TouchDev.state & 0x0f);
	TouchDev.state = (TouchDev.state & 0x80);
    TouchDev.isTouch = 0;

	switch(TouchDev.state) {
		case TOUCH_NO:
			break;
		case TOUCH_ING:
			for(uint8_t i = 0; i < TouchDev.number; i++) {
                TouchDev.isTouch = 1;

				GT911_ReadReg((GT_TPD_Sta + i*8 + X_L), &_temp, 1);	//read x pos low 8 bit
				TouchDev.xy[i].x  = _temp;
				GT911_ReadReg((GT_TPD_Sta + i*8 + X_H), &_temp, 1);	//read x pos high 8 bit
				TouchDev.xy[i].x |= (_temp <<8 );

				GT911_ReadReg((GT_TPD_Sta + i*8 + Y_L), &_temp, 1);	//read y pos low 8 bit
				TouchDev.xy[i].y  = _temp;
				GT911_ReadReg((GT_TPD_Sta + i*8 + Y_H), &_temp, 1);	//read y pos high 8 bit
				TouchDev.xy[i].y |= (_temp << 8);

				GT911_ReadReg((GT_TPD_Sta + i*8 + S_L), &_temp, 1);	//read size low 8 bit
				TouchDev.xy[i].s  = _temp;
				GT911_ReadReg((GT_TPD_Sta + i*8 + S_H), &_temp, 1);	//read size high 8 bit
				TouchDev.xy[i].s |= (_temp << 8);
			}

			_temp=0;
			GT911_WriteReg(GT_GSTID_REG, &_temp, 1);
		break;
	}
}

void GTP911_Test(void)
{
	gt911_scanf();
	if(TouchDev.isTouch == 1) {
		for(uint8_t i = 0; i < TouchDev.number; i++) {
			printf("X : %d  ", TouchDev.xy[i].x);
			printf("Y : %d  ", TouchDev.xy[i].y);
			printf("S : %d\r\n\r\n", TouchDev.xy[i].s);
		}
	}
}

void gt911_getId(void)
{
    uint8_t pid[4] = {0};

    GT911_ReadReg(0x8140, pid, 4);

    printf("PID:%c%c%cr\n", pid[0], pid[1], pid[2], pid[3]);
}

/// @brief GT911 INI CALLBACK
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_5) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5); 
    }
}

static uint8_t GT911_WriteReg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;

	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT911_ADDRESS_W);	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8); 
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);
	CT_IIC_Wait_Ack();  

	for(i=0;i<len;i++) {	   
    	CT_IIC_Send_Byte(buf[i]);
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();

	return ret; 
}
	  
static void GT911_ReadReg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i; 

 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT911_ADDRESS_W);   
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT911_ADDRESS_R);  	   
	CT_IIC_Wait_Ack();	  

	for(i=0;i<len;i++) {	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1);
	} 

    CT_IIC_Stop();  
} 
