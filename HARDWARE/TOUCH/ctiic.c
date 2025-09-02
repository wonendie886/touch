#include "ctiic.h"
#include "delay.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//WKS STM32F407VET6���İ�
//���ݴ�����-IIC ��������
//�汾��V1.0
////////////////////////////////////////////////////////////////////////////////// 	

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	delay_us(2);
} 
//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{	
    GPIO_InitTypeDef GPIO_Initure;
    
     __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOBʱ��
    
    //PB8,9��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//    CT_IIC_SDA=1;	  	  
//	  CT_IIC_SCL=1;
}
//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda�����
	CT_IIC_SDA=1;	  	  
	CT_IIC_SCL=1;
	delay_us(30);
 	CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda�����
	CT_IIC_SCL=1;
	delay_us(30);
	CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA=1;//����I2C���߽����ź�  
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
	CT_IIC_SDA=1;	    //�ͷ�SDA��
	CT_IIC_SCL=1;     //ʱ����Ϊ�ߵ�ƽ
	CT_Delay();
	while(CT_READ_SDA)     //�ж��Ƿ���յ���Ӧ���źţ��͵�ƽΪ��Ч�ź�
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;         //û���յ�Ӧ���ź�
		} 
		CT_Delay();
	}
	CT_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void CT_IIC_Ack(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();        //SDA����Ϊ���
	CT_Delay();
	CT_IIC_SDA=0;        //����Ӧ���ź�
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();       //SDA����Ϊ���
	CT_Delay();
	CT_IIC_SDA=1;       //��Ӧ���ź�
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	CT_Delay();
	for(t=0;t<8;t++)
    {              
        CT_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	 
    CT_Delay();   			
		CT_IIC_SCL=1;      //��SCL������SDA�ϵ����ݽ��д��д���
		CT_Delay();
		CT_IIC_SCL=0;	
		CT_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
	delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL=0; 	    	   
		CT_Delay();
		CT_IIC_SCL=1;	 
		receive<<=1;
		CT_Delay();   
		if(CT_READ_SDA)receive++;      //SCLΪ�ߵ�ƽ�ڼ䣬��ȡSDA�ϵ�����
		CT_Delay();
	}	  				 
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;    //���ض���������
}





























