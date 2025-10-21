#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"
#include "touch.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "gui_guider.h"
#include "events_init.h"
#include "ad7793.h"
#include "math.h"

lv_ui guider_ui;
/************************************************
 WKS STM32F407VET6���İ�
 ������ʵ��-HAL�⺯����
************************************************/

//�����Ļ�������Ͻ���ʾ"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}////////////////////////////////////////////////////////////////////////////////
/**
 * ����Ļ�ϻ���ʵ��������
 * @param x0 ���������Ͻ�X����
 * @param y0 ���������Ͻ�Y����
 * @param size �����α߳�
 * @param color ��������ɫ
 */
void gui_fill_square(u16 x0, u16 y0, u16 size, u16 color)
{
    // ʹ��LCD_Fill�������һ������������ʵ��ʵ��������
    LCD_Fill(x0, y0, x0 + size - 1, y0 + size - 1, color);
}

//���ݴ�����ר�в���
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//��ʵ��Բ
//x0,y0:����
//r:�뾶
//color:��ɫ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
/**
 * ����Ļ�ϻ�����Բ
 * @param x0 Բ��X����
 * @param y0 Բ��Y����
 * @param r  Բ�İ뾶
 */
void draw_hollow_circle_on_screen(u16 x0, u16 y0, u16 r)
{
    // ʹ��Bresenham�㷨���ƿ���Բ
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    // ����Բ�ϵ�8���ԳƵ�
    while (x <= y) {
        LCD_DrawPoint(x0 + x, y0 + y);
        LCD_DrawPoint(x0 - x, y0 + y);
        LCD_DrawPoint(x0 + x, y0 - y);
        LCD_DrawPoint(x0 - x, y0 - y);
        LCD_DrawPoint(x0 + y, y0 + x);
        LCD_DrawPoint(x0 - y, y0 + x);
        LCD_DrawPoint(x0 + y, y0 - x);
        LCD_DrawPoint(x0 - y, y0 - x);
        
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
//������֮��ľ���ֵ 
//x1,x2����ȡ��ֵ��������
//����ֵ��|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//��һ������
//(x1,y1),(x2,y2):��������ʼ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

void Test_Draw_Line(void)
{
    u16 x1 = 20;
    u16 y1 = 30;
    u16 x2 = 200;
    u16 y2 = 150;
    u8 size = 4;
    u16 color = RED;

    lcd_draw_bline(x1, y1, x2, y2, size, color);
}

////////////////////////////////////////////////////////////////////////////////
//5�����ص����ɫ(���ݴ�������)												 
const u16 POINT_COLOR_TBL[5]={RED,GREEN,BLUE,BROWN,GRED};  
//���败�������Ժ���
void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
	 	key=KEY_Scan(0);
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//���
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  			   
			}
		}else delay_ms(10);	//û�а������µ�ʱ�� 	    
		if(key==KEY0_PRES)	//KEY0����,��ִ��У׼����
		{
			LCD_Clear(WHITE);	//����
		    TP_Adjust();  		//��ĻУ׼ 
			TP_Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)LED0 =!LED0;
	}
}
//���ݴ��������Ժ���
void ctp_test(void)
{
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//���һ�ε����� 
	while(1)
	{
		tp_dev.scan(0);
		for(t=0;t<5;t++)   //���5�㴥��
		{
			if((tp_dev.sta)&(1<<t))   //�ж��Ƿ��е㴥��
			{
                //printf("X����:%d,Y����:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
                    
					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//����
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<20)  //�������Ļ�ϵ�RST����
					{
						Load_Drow_Dialog();//���
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}
		
		delay_ms(5);i++;
		if(i%20==0)LED0=!LED0;
	}	
}



int main(void)
{ 
	HAL_Init();                   	//��ʼ��HAL��    
	STM32_Clock_Init(336,25,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		        //��ʼ��USMART
	LED_Init();						          //��ʼ��LED	
	KEY_Init();						          //��ʼ��KEY
	TIM2_Init();							  // ��ʼ��TIM2
	LCD_Init();           			    //��ʼ��LCD
	tp_dev.init();				          //��������ʼ�� 
	
	lv_init();
	lv_port_disp_init();   // ��Ҫʵ�ֵ���ʾ�ӿ�
	lv_port_indev_init();  // ��Ҫʵ�ֵĴ��ؽӿ�

	setup_ui(&guider_ui);
	events_init(&guider_ui);

    uint32_t time = 0;

    uint8_t AD7793_ID = 0;
    float TC_voltage = 0;
    float PT100_temp = 0;
    float temp = 0;
    double pt100Voltage = 0;
    double voltage = 0;
    double temperature = 0;
    
    GPIO_Configuration();

    AD7793init();
    AD7793_ID=Get_AD7793_ID();//Read AD7793 ID(0xXB)
    
    printf("AD7793_ID = %d",AD7793_ID);
	
    while (1)                                        {                                                  
        lv_task_handler();  
		HAL_Delay(5);
        time += 5;

        if (time == 500){
            time = 0;

            AD7793_GetPT100_init();
            HAL_Delay(5);
            PT100_temp = Get_PT100();//读取PT100温度
            
            pt100Voltage = kTypeTemperature2Voltage(PT100_temp);
            HAL_Delay(5);
            
            AD7793_CS_L;
            AD7793_thermocouple_init();
            HAL_Delay(5);
            TC_voltage = Get_thermocouple_Value();//读取热电动势
            HAL_Delay(5);
            
            voltage = TC_voltage + pt100Voltage;
            temperature = kTypeVoltage2Temperature(voltage);
            printf("PT100-temperature = %0.2f  k-temperature = %f\n",PT100_temp,temperature);
            char buf[200] = {0};
            sprintf(buf, "PT100-Temperature: %0.2f C", PT100_temp);
            lv_label_set_text(guider_ui.screen_label_1, buf);

            sprintf(buf, "K-Temperature: %0.2f C", temperature);
            lv_label_set_text(guider_ui.screen_label_2, buf);
            LED0 = !LED0;  
        }
	}
	
	//if(tp_dev.touchtype&0X80)ctp_test();//����������
	//else rtp_test(); 					//����������  
}

