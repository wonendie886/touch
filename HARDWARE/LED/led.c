#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//WKS STM32F407VET6���İ�
//LED��������	   
//�汾��V1.0						  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PA1��PA2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
	
    GPIO_Initure.Pin = GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);	//PA1��1��Ĭ�ϳ�ʼ�������
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);	//PA2��1��Ĭ�ϳ�ʼ�������
}
