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
/************************************************
 WKS STM32F407VET6核心板
 触摸屏实验-HAL库函数版
************************************************/

//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}////////////////////////////////////////////////////////////////////////////////
/**
 * 在屏幕上绘制实心正方形
 * @param x0 正方形左上角X坐标
 * @param y0 正方形左上角Y坐标
 * @param size 正方形边长
 * @param color 正方形颜色
 */
void gui_fill_square(u16 x0, u16 y0, u16 size, u16 color)
{
    // 使用LCD_Fill函数填充一个矩形区域来实现实心正方形
    LCD_Fill(x0, y0, x0 + size - 1, y0 + size - 1, color);
}

//电容触摸屏专有部分
//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
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
 * 在屏幕上画空心圆
 * @param x0 圆心X坐标
 * @param y0 圆心Y坐标
 * @param r  圆的半径
 */
void draw_hollow_circle_on_screen(u16 x0, u16 y0, u16 r)
{
    // 使用Bresenham算法绘制空心圆
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    // 绘制圆上的8个对称点
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
//两个数之差的绝对值 
//x1,x2：需取差值的两个数
//返回值：|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//画一条粗线
//(x1,y1),(x2,y2):线条的起始坐标
//size：线条的粗细程度
//color：线条的颜色
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		gui_fill_circle(uRow,uCol,size,color);//画点 
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
//5个触控点的颜色(电容触摸屏用)												 
const u16 POINT_COLOR_TBL[5]={RED,GREEN,BLUE,BROWN,GRED};  
//电阻触摸屏测试函数
void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
	 	key=KEY_Scan(0);
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	    
		if(key==KEY0_PRES)	//KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE);	//清屏
		    TP_Adjust();  		//屏幕校准 
			TP_Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)LED0 =!LED0;
	}
}
//电容触摸屏测试函数
void ctp_test(void)
{
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//最后一次的数据 
	while(1)
	{
		tp_dev.scan(0);
		for(t=0;t<5;t++)   //最多5点触摸
		{
			if((tp_dev.sta)&(1<<t))   //判断是否有点触摸
			{
                //printf("X坐标:%d,Y坐标:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
                    
					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//画线
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<20)  //点击了屏幕上的RST部分
					{
						Load_Drow_Dialog();//清除
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}
		
		delay_ms(5);i++;
		if(i%20==0)LED0=!LED0;
	}	
}


void lv_example_led_1(void)
{
    /*Create a LED and switch it OFF*/
    lv_obj_t * led1  = lv_led_create(lv_scr_act());
    lv_obj_align(led1, LV_ALIGN_CENTER, -80, 0);
    lv_led_off(led1);
 
    /*Copy the previous LED and set a brightness*/
    lv_obj_t * led2  = lv_led_create(lv_scr_act());
    lv_obj_align(led2, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_brightness(led2, 150);
    lv_led_set_color(led2, lv_palette_main(LV_PALETTE_RED));
 
    /*Copy the previous LED and switch it ON*/
    lv_obj_t * led3  = lv_led_create(lv_scr_act());
    lv_obj_align(led3, LV_ALIGN_CENTER, 80, 0);
    lv_led_on(led3);
}

#include "lvgl.h"

/* 按钮点击回调函数 */
static void btn_event_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);

    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_label_set_text(label, "Touched!");
    }
}

/* 测试界面初始化 */
void lv_touch_test(void)
{
    /* 创建一个按钮 */
    lv_obj_t * btn = lv_btn_create(lv_scr_act());   // 在活动屏幕上建一个按钮
    lv_obj_center(btn);                             // 居中显示
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);

    /* 按钮上的文字 */
    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "Touch me!");
    lv_obj_center(label);
}



int main(void)
{ 
	HAL_Init();                   	//初始化HAL库    
	STM32_Clock_Init(336,25,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		        //初始化USMART
	LED_Init();						          //初始化LED	
	KEY_Init();						          //初始化KEY
	TIM2_Init();							  // 初始化TIM2
	LCD_Init();           			    //初始化LCD
	tp_dev.init();				          //触摸屏初始化 
	
	lv_init();
	lv_port_disp_init();   // 你要实现的显示接口
	lv_port_indev_init();  // 你要实现的触控接口
	//lv_example_led_1();
	lv_touch_test();

    while (1)                                            // while函数死循环，不能让main函数运行结束，否则会产生硬件错误
    {                                                  
        lv_task_handler();  
		HAL_Delay(5);//LVGL事物处理，必须加到循环中
	}
	
	//if(tp_dev.touchtype&0X80)ctp_test();//电容屏测试
	//else rtp_test(); 					//电阻屏测试  
}

