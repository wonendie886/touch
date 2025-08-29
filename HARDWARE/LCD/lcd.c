#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//WKS STM32F407VET6���İ�
//2.8��/3.5��/4.3��/ TFTҺ������
//֧������IC�ͺŰ���:NT35310/NT35510/ST7796/ST7789
//�汾��V1.0
//////////////////////////////////////////////////////////////////////////////////	 

SRAM_HandleTypeDef TFTSRAM_Handler;    //SRAM���(���ڿ���LCD)

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR = 0x0000;		//������ɫ
u16 BACK_COLOR  = 0xFFFF;  	//����ɫ 

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

/* ************************ */
#define NV3401_RESET_PIN GPIO_PIN_12
#define NV3401_CS_PIN GPIO_PIN_10
#define NV3401_WR_PIN GPIO_PIN_11
#define NV3401_RD_PIN GPIO_PIN_9
#define NV3401_DC_PIN GPIO_PIN_8

#define NV3401_RESET PEout(12) 
#define NV3401_CS PEout(10)
#define NV3401_WR PEout(11)
#define NV3401_RD PEout(9)
#define NV3401_DC PEout(8)

///PORT PE
#define NV3401_DATA_PIN_13 GPIO_PIN_15
#define NV3401_DATA_PIN_14 GPIO_PIN_14
#define NV3401_DATA_PIN_15 GPIO_PIN_13

#define NV3401_DATA_13 15
#define NV3401_DATA_14 14
#define NV3401_DATA_15 13

///PORT PB
#define NV3401_DATA_PIN_8 GPIO_PIN_15
#define NV3401_DATA_PIN_9 GPIO_PIN_14
#define NV3401_DATA_PIN_10 GPIO_PIN_13
#define NV3401_DATA_PIN_11 GPIO_PIN_12
#define NV3401_DATA_PIN_12 GPIO_PIN_10

#define NV3401_DATA_8 15
#define NV3401_DATA_9 14
#define NV3401_DATA_10 13
#define NV3401_DATA_11 12
#define NV3401_DATA_12 10

/// PORT PD
#define NV3401_DATA_PIN_0 GPIO_PIN_15
#define NV3401_DATA_PIN_1 GPIO_PIN_14
#define NV3401_DATA_PIN_2 GPIO_PIN_13
#define NV3401_DATA_PIN_3 GPIO_PIN_12
#define NV3401_DATA_PIN_4 GPIO_PIN_11
#define NV3401_DATA_PIN_5 GPIO_PIN_10
#define NV3401_DATA_PIN_6 GPIO_PIN_9
#define NV3401_DATA_PIN_7 GPIO_PIN_8

#define NV3401_DATA_0 15
#define NV3401_DATA_1 14
#define NV3401_DATA_2 13
#define NV3401_DATA_3 12
#define NV3401_DATA_4 11
#define NV3401_DATA_5 10
#define NV3401_DATA_6 9
#define NV3401_DATA_7 8

static void nv3401_set_data(uint16_t data);
static void write_lcd_data(uint16_t data);
static void write_lcd_reg(uint16_t reg,uint16_t data);
static void write_lcd_cmd(uint16_t cmd);
static void nv3401_fillColor(uint16_t color, uint32_t pixel_count);
void nv3401_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#define DATA_MODE_OUTPUT 1
#define DATA_MODE_INPUT 0

void nv3401_gpio_init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	/// RESET - PE12
	/// CS 	  - PE10	
	/// WR    - PE11
	/// RD    - PE9
	//DC(DATA/COMMAND) - PE8

	///DATA[0-15]
	///DATA[0-7] - PD15- PD8
	///DATA[8-11] - PB15 - PB12
	///DATA[12] - PB10
	///DATA[13-15] - PE15 - PE13

	GPIO_InitTypeDef gpio_initure = {0};
	
	gpio_initure.Pin = NV3401_RESET_PIN | NV3401_CS_PIN | NV3401_WR_PIN | NV3401_RD_PIN | NV3401_DC_PIN
						| NV3401_DATA_PIN_13 | NV3401_DATA_PIN_14 | NV3401_DATA_PIN_15;	
	gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
	gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
	gpio_initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOE,&gpio_initure); 

	HAL_GPIO_WritePin(GPIOE,NV3401_RESET_PIN | NV3401_CS_PIN | NV3401_WR_PIN | NV3401_RD_PIN | NV3401_DC_PIN,GPIO_PIN_SET);

	gpio_initure.Pin = NV3401_DATA_PIN_0 | NV3401_DATA_PIN_1 | NV3401_DATA_PIN_2 | NV3401_DATA_PIN_3 
						| NV3401_DATA_PIN_4 | NV3401_DATA_PIN_5 | NV3401_DATA_PIN_6 | NV3401_DATA_PIN_7;

	HAL_GPIO_Init(GPIOD,&gpio_initure); 

	gpio_initure.Pin = NV3401_DATA_PIN_8 | NV3401_DATA_PIN_9 | NV3401_DATA_PIN_10 | NV3401_DATA_PIN_11 | NV3401_DATA_PIN_12;

	HAL_GPIO_Init(GPIOB,&gpio_initure);

	nv3401_set_data(0x0000);

	NV3401_RESET = 0;
	delay_ms(100);
	NV3401_RESET = 1;
	delay_ms(100);
} 

void set_data_out(uint8_t mode)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitTypeDef gpio_initure = {0};

	if (mode == DATA_MODE_OUTPUT){
		gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
		gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
		gpio_initure.Speed = GPIO_SPEED_HIGH;
	} else {
		gpio_initure.Mode = GPIO_MODE_INPUT;  
		gpio_initure.Pull = GPIO_PULLUP; 
	}

	gpio_initure.Pin = NV3401_DATA_PIN_13 | NV3401_DATA_PIN_14 | NV3401_DATA_PIN_15;	
	HAL_GPIO_Init(GPIOE,&gpio_initure); 

	gpio_initure.Pin = NV3401_DATA_PIN_0 | NV3401_DATA_PIN_1 | NV3401_DATA_PIN_2 | NV3401_DATA_PIN_3 
						| NV3401_DATA_PIN_4 | NV3401_DATA_PIN_5 | NV3401_DATA_PIN_6 | NV3401_DATA_PIN_7;

	HAL_GPIO_Init(GPIOD,&gpio_initure); 

	gpio_initure.Pin = NV3401_DATA_PIN_8 | NV3401_DATA_PIN_9 | NV3401_DATA_PIN_10 | NV3401_DATA_PIN_11 | NV3401_DATA_PIN_12;

	HAL_GPIO_Init(GPIOB,&gpio_initure);

	if (mode == DATA_MODE_OUTPUT){
		nv3401_set_data(0);
	}
}
void nv3401_lcd_init(void)
{
	write_lcd_reg(0x0000,0x00ff);
	write_lcd_reg(0x8000,0x00a5);
	// write_lcd_reg(0x0000,0x00E7);//TE_output_en
	// write_lcd_reg(0x8000,0x0010);
	write_lcd_reg(0x0000,0x0035);//TE_ interface_en
	write_lcd_reg(0x8000,0x0001);
	write_lcd_reg(0x0000,0x003A);
	write_lcd_reg(0x8000,0x0001);//00---666//01--565
	write_lcd_reg(0x0000,0x0040);
	write_lcd_reg(0x8000,0x0001); //01:IPS/00:TN
	write_lcd_reg(0x0000,0x0041);
	write_lcd_reg(0x8000,0x0001);//01--8bit//03--16bit
	write_lcd_reg(0x0000,0x0055);
	write_lcd_reg(0x8000,0x0001);
	write_lcd_reg(0x0000,0x0044);//VBP
	write_lcd_reg(0x8000,0x0015);//21
	write_lcd_reg(0x0000,0x0045);//VFP
	write_lcd_reg(0x8000,0x0015);//21
	write_lcd_reg(0x0000,0x007d);//vdds_trim[2:0]
	write_lcd_reg(0x8000,0x0003);//2.07V
	write_lcd_reg(0x0000,0x00c1);//avdd_clp_en avdd_clp[1:0] avcl_clp_en avcl_clp[1:0]
	write_lcd_reg(0x8000,0x00ab);//6.74V/-5.16V
	write_lcd_reg(0x0000,0x00c2);//vgh_clp_en vgl_clp[2:0]
	write_lcd_reg(0x8000,0x0017);
	write_lcd_reg(0x0000,0x00c3);//vgl_clp_en vgl_clp[2:0]
	write_lcd_reg(0x8000,0x0010);//-10.951
	write_lcd_reg(0x0000,0x00c6);//avdd_ratio_sel avcl_ratio_sel vgh_ratio_sel[1:0] vgl_ratio_sel[1:0]
	write_lcd_reg(0x8000,0x003a);//35
	write_lcd_reg(0x0000,0x00c7);//mv_clk_sel[1:0] avdd_clk_sel[1:0] avcl_clk_sel[1:0]
	write_lcd_reg(0x8000,0x0025); //2e
	write_lcd_reg(0x0000,0x00c8);// VGL_CLK_sel
	write_lcd_reg(0x8000,0x0011);
	write_lcd_reg(0x0000,0x006f);// user_gvdd
	write_lcd_reg(0x8000,0x002f);
	write_lcd_reg(0x0000,0x0078);// user_gvcl
	write_lcd_reg(0x8000,0x004b);

	write_lcd_reg(0x0000,0x007a);// user_vgsp
	write_lcd_reg(0x8000,0x0049);

	write_lcd_reg(0x0000,0x00c9);
	write_lcd_reg(0x8000,0x0000);

	write_lcd_reg(0x0000,0x0073);//osc
	write_lcd_reg(0x8000,0x0008);
	write_lcd_reg(0x0000,0x0074);
	write_lcd_reg(0x8000,0x0011);//12

	write_lcd_reg(0x0000,0x0067);
	write_lcd_reg(0x8000,0x0011);
	//gate_ed
	write_lcd_reg(0x0000,0x0051);//gate_st_o[7:0]
	//write_lcd_reg(0x8000,0x004b);
	write_lcd_reg(0x8000,0x0020);
	write_lcd_reg(0x0000,0x0052);//gate_ed_o[7:0]
	write_lcd_reg(0x8000,0x007c);
	write_lcd_reg(0x0000,0x0053);//gate_st_e[7:0]
	//write_lcd_reg(0x8000,0x0045);
	write_lcd_reg(0x8000,0x001c);
	write_lcd_reg(0x0000,0x0054);//gate_ed_e[7:0]
	write_lcd_reg(0x8000,0x0077);
	////sorce old
	write_lcd_reg(0x0000,0x0046);//fsm_hbp_o[5:0]
	write_lcd_reg(0x8000,0x000a);
	write_lcd_reg(0x0000,0x0047);//fsm_hfp_o[5:0]
	write_lcd_reg(0x8000,0x002a);
	write_lcd_reg(0x0000,0x0048);//fsm_hbp_e[5:0]
	write_lcd_reg(0x8000,0x000a);
	write_lcd_reg(0x0000,0x0049);//fsm_hfp_e[5:0]
	write_lcd_reg(0x8000,0x001a);
	write_lcd_reg(0x0000,0x0056);//src_ld_wd[1:0] src_ld_st[5:0]
	write_lcd_reg(0x8000,0x0043);
	write_lcd_reg(0x0000,0x0057);//pn_cs_en src_cs_st[5:0]
	write_lcd_reg(0x8000,0x0042);
	write_lcd_reg(0x0000,0x0058);//src_cs_p_wd[6:0]
	write_lcd_reg(0x8000,0x003c);
	write_lcd_reg(0x0000,0x0059);//src_cs_n_wd[6:0]
	write_lcd_reg(0x8000,0x0064);
	write_lcd_reg(0x0000,0x005a);//src_pchg_st_o[6:0]
	write_lcd_reg(0x8000,0x0041);
	write_lcd_reg(0x0000,0x005b);//src_pchg_wd_o[6:0]
	write_lcd_reg(0x8000,0x003c);
	write_lcd_reg(0x0000,0x005c);//src_pchg_st_e[6:0]
	write_lcd_reg(0x8000,0x0002);
	write_lcd_reg(0x0000,0x005d);//src_pchg_wd_e[6:0]
	write_lcd_reg(0x8000,0x003c);
	write_lcd_reg(0x0000,0x005e);//src_pol_sw[7:0]
	write_lcd_reg(0x8000,0x001f);
	write_lcd_reg(0x0000,0x0060);//src_op_st_o[7:0]
	write_lcd_reg(0x8000,0x0080);
	write_lcd_reg(0x0000,0x0061);//src_op_st_e[7:0]
	write_lcd_reg(0x8000,0x003f);
	write_lcd_reg(0x0000,0x0062);//src_op_ed_o[9:8] src_op_ed_e[9:8]
	write_lcd_reg(0x8000,0x0021);
	write_lcd_reg(0x0000,0x0063);//src_op_ed_o[7:0]
	write_lcd_reg(0x8000,0x0007);
	write_lcd_reg(0x0000,0x0064);//src_op_ed_e[7:0]
	write_lcd_reg(0x8000,0x00e0);
	write_lcd_reg(0x0000,0x0065);//chopper
	write_lcd_reg(0x8000,0x0001);//01-A2,02--A1

	write_lcd_reg(0x0000,0x00ca); //avdd_mux_st_o[7:0]
	write_lcd_reg(0x8000,0x0020);
	write_lcd_reg(0x0000,0x00cb); //avdd_mux_ed_o[7:0]
	write_lcd_reg(0x8000,0x0052);
	write_lcd_reg(0x0000,0x00cc); //avdd_mux_st_e[7:0]
	write_lcd_reg(0x8000,0x0010);
	write_lcd_reg(0x0000,0x00cD); //avdd_mux_ed_e[7:0]
	write_lcd_reg(0x8000,0x0042);
	write_lcd_reg(0x0000,0x00D0); //avcl_mux_st_o[7:0]
	write_lcd_reg(0x8000,0x0020);
	write_lcd_reg(0x0000,0x00D1); //avcl_mux_ed_o[7:0]
	write_lcd_reg(0x8000,0x0052);
	write_lcd_reg(0x0000,0x00D2); //avcl_mux_st_e[7:0]
	write_lcd_reg(0x8000,0x0010);
	write_lcd_reg(0x0000,0x00D3); //avcl_mux_ed_e[7:0]
	write_lcd_reg(0x8000,0x0042);
	write_lcd_reg(0x0000,0x00D4); //vgh_mux_st[7:0]
	write_lcd_reg(0x8000,0x000a);
	write_lcd_reg(0x0000,0x00D5); //vgh_mux_ed[7:0]
	write_lcd_reg(0x8000,0x0032);
	write_lcd_reg(0x0000,0x00e5); //DVDD_TRIM
	write_lcd_reg(0x8000,0x0006); //1.65 05
	write_lcd_reg(0x0000,0x00e6); //ESD_CTRL
	write_lcd_reg(0x8000,0x0000);
	write_lcd_reg(0x0000,0x006e); //LVD_en
	write_lcd_reg(0x8000,0x0014);
	//gammma 01
	write_lcd_reg(0x0000,0x0080); //gam_vrp0 63
	write_lcd_reg(0x8000,0x0004);
	write_lcd_reg(0x0000,0x00A0); //gam_VRN0 63
	write_lcd_reg(0x8000,0x0000);
	write_lcd_reg(0x0000,0x0081); //gam_vrp1 62
	write_lcd_reg(0x8000,0x0007);
	write_lcd_reg(0x0000,0x00A1); //gam_VRN1 62-
	write_lcd_reg(0x8000,0x0005);
	write_lcd_reg(0x0000,0x0082); //gam_vrp2 61
	write_lcd_reg(0x8000,0x0006);
	write_lcd_reg(0x0000,0x00A2); //gam_VRN2 61-
	write_lcd_reg(0x8000,0x0004);
	write_lcd_reg(0x0000,0x0083); //gam_vrp3 2
	write_lcd_reg(0x8000,0x0039);
	write_lcd_reg(0x0000,0x00A3); //gam_VRN3 2-
	write_lcd_reg(0x8000,0x0039);
	write_lcd_reg(0x0000,0x0084); //gam_vrp4 1
	write_lcd_reg(0x8000,0x003a);
	write_lcd_reg(0x0000,0x00A4); //gam_VRN4 1-
	write_lcd_reg(0x8000,0x003a);
	write_lcd_reg(0x0000,0x0085); //gam_vrp5 0
	write_lcd_reg(0x8000,0x003f); //2a~39-0.43
	write_lcd_reg(0x0000,0x00A5); //gam_VRN5 0-
	write_lcd_reg(0x8000,0x003f);
	write_lcd_reg(0x0000,0x0086); //gam_prp0 50
	write_lcd_reg(0x8000,0x002c); //33
	write_lcd_reg(0x0000,0x00A6); //gam_PRN0 50-
	write_lcd_reg(0x8000,0x002a); //2a
	//write_lcd_reg(0x0000,0x0087); //gam_prp1 14
	//write_lcd_reg(0x8000,0x0046); //2d
	//write_lcd_reg(0x0000,0x00A7); //gam_PRN1 14-
	//write_lcd_reg(0x8000,0x0044); //2d
	write_lcd_reg(0x0000,0x0087); //gam_prp1 14
	write_lcd_reg(0x8000,0x0043); //2d
	write_lcd_reg(0x0000,0x00A7); //gam_PRN1 14-
	write_lcd_reg(0x8000,0x0047); //2d
	write_lcd_reg(0x0000,0x0088); //gam_pkp0 59
	write_lcd_reg(0x8000,0x0008); //0b
	write_lcd_reg(0x0000,0x00A8); //gam_PKN0 59-
	write_lcd_reg(0x8000,0x0008); //0b
	write_lcd_reg(0x0000,0x0089); //gam_pkp1 57
	write_lcd_reg(0x8000,0x000f); //14
	write_lcd_reg(0x0000,0x00A9); //gam_PKN1 57-
	write_lcd_reg(0x8000,0x000f); //14
	write_lcd_reg(0x0000,0x008a); //gam_pkp2 54
	write_lcd_reg(0x8000,0x0017); //1a
	write_lcd_reg(0x0000,0x00Aa); //gam_PKN2 54-
	write_lcd_reg(0x8000,0x0017); //1a
	write_lcd_reg(0x0000,0x008b); //gam_PKP3 44
	write_lcd_reg(0x8000,0x0010);
	write_lcd_reg(0x0000,0x00Ab); //gam_PKN3 44-
	write_lcd_reg(0x8000,0x0010);
	write_lcd_reg(0x0000,0x008c); //gam_PKP4 38
	write_lcd_reg(0x8000,0x0016);
	write_lcd_reg(0x0000,0x00Ac); //gam_PKN4 38-
	write_lcd_reg(0x8000,0x0016);
	write_lcd_reg(0x0000,0x008d); //gam_PKP5 32
	write_lcd_reg(0x8000,0x0014);
	write_lcd_reg(0x0000,0x00Ad); //gam_PKN5 32-
	write_lcd_reg(0x8000,0x0014);
	write_lcd_reg(0x0000,0x008e); //gam_PKP6 26
	write_lcd_reg(0x8000,0x0011); //16
	write_lcd_reg(0x0000,0x00Ae); //gam_PKN6 26-
	write_lcd_reg(0x8000,0x0011); //13
	write_lcd_reg(0x0000,0x008f); //gam_PKP7 20
	write_lcd_reg(0x8000,0x0014); //1c
	write_lcd_reg(0x0000,0x00Af); //gam_PKN7 20-
	write_lcd_reg(0x8000,0x0014); //0a
	write_lcd_reg(0x0000,0x0090); //gam_PKP8 10
	write_lcd_reg(0x8000,0x0006);
	write_lcd_reg(0x0000,0x00B0); //gam_PKN8 10-
	write_lcd_reg(0x8000,0x0006);
	write_lcd_reg(0x0000,0x0091); //gam_PKP9 6
	write_lcd_reg(0x8000,0x000f);
	write_lcd_reg(0x0000,0x00B1); //gam_PKN9 6-
	write_lcd_reg(0x8000,0x000f);
	write_lcd_reg(0x0000,0x0092); //gam_PKP10 4
	write_lcd_reg(0x8000,0x0016);
	write_lcd_reg(0x0000,0x00B2); //gam_PKN10 4-
	write_lcd_reg(0x8000,0x0016);
	write_lcd_reg(0x0000,0x00ff);
	write_lcd_reg(0x8000,0x0000);
	write_lcd_reg(0x0000,0x0011);
	delay_ms(200);
	write_lcd_reg(0x0000,0x0029);
	delay_ms(120);

	//write_lcd_cmd(0x28); 0x001F
	nv3401_SetWindow(0,0,50-1,50-1);

	nv3401_fillColor(0xffff,50*50);
	
}   

static void nv3401_set_data(uint16_t data)
{
	PDout(NV3401_DATA_0) = (data >> 0) & 0x01;
	PDout(NV3401_DATA_1) = (data >> 1) & 0x01;
	PDout(NV3401_DATA_2) = (data >> 2) & 0x01;
	PDout(NV3401_DATA_3) = (data >> 3) & 0x01;
	PDout(NV3401_DATA_4) = (data >> 4) & 0x01;
	PDout(NV3401_DATA_5) = (data >> 5) & 0x01;
	PDout(NV3401_DATA_6) = (data >> 6) & 0x01;
	PDout(NV3401_DATA_7) = (data >> 7) & 0x01;

	PBout(NV3401_DATA_8) = (data >> 8) & 0x01;
	PBout(NV3401_DATA_9) = (data >> 9) & 0x01;
	PBout(NV3401_DATA_10) = (data >> 10) & 0x01;
	PBout(NV3401_DATA_11) = (data >> 11) & 0x01;
	PBout(NV3401_DATA_12) = (data >> 12) & 0x01;

	PEout(NV3401_DATA_13) = (data >> 13) & 0x01;
	PEout(NV3401_DATA_14) = (data >> 14) & 0x01;
	PEout(NV3401_DATA_15) = (data >> 15) & 0x01;
}

void nv3401_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    write_lcd_cmd(0x002A);  // 列地址设置
    write_lcd_data(x1 >> 8);
    write_lcd_data(x1 & 0xFF);
    write_lcd_data(x2 >> 8);
    write_lcd_data(x2 & 0xFF);
    
    write_lcd_cmd(0x002B);  // 行地址设置
    write_lcd_data(y1 >> 8);
    write_lcd_data(y1 & 0xFF);
    write_lcd_data(y2 >> 8);
    write_lcd_data(y2 & 0xFF);
    
    write_lcd_cmd(0x002C);  // 开始写入显存
}

static void nv3401_fillColor(uint16_t color, uint32_t pixel_count)
{
    // 设置好窗口后，连续写入颜色数据
    write_lcd_cmd(0x002C);  // 开始写入显存
    
	// for(uint32_t i = 0; i < pixel_count; i++) {
	// 	write_lcd_data(color);
    // }
	
	NV3401_CS = 0;
	
	NV3401_DC = 1; ///data
	NV3401_RD = 1;
    for(uint32_t i = 0; i < pixel_count; i++) {
		nv3401_set_data(color);
		NV3401_WR = 0;
		NV3401_WR = 1;
    }

	NV3401_CS = 1;
	
}

static uint16_t nv3401_get_data()
{
	uint16_t data = 0;

	data |= PDin(NV3401_DATA_0) << 0;
	data |= PDin(NV3401_DATA_1) << 1;
	data |= PDin(NV3401_DATA_2) << 2;
	data |= PDin(NV3401_DATA_3) << 3;
	data |= PDin(NV3401_DATA_4) << 4;
	data |= PDin(NV3401_DATA_5) << 5;
	data |= PDin(NV3401_DATA_6) << 6;
	data |= PDin(NV3401_DATA_7) << 7;

	data |= PBin(NV3401_DATA_8) << 8;
	data |= PBin(NV3401_DATA_9) << 9;
	data |= PBin(NV3401_DATA_10) << 10;
	data |= PBin(NV3401_DATA_11) << 11;
	data |= PBin(NV3401_DATA_12) << 12;

	data |= PEin(NV3401_DATA_13) << 13;
	data |= PEin(NV3401_DATA_14) << 14;
	data |= PEin(NV3401_DATA_15) << 15;

	return data;
}

uint16_t read_lcd_data(void)
{
	uint16_t data = 0;

	set_data_out(DATA_MODE_INPUT);

	NV3401_DC = 1;//data
	NV3401_WR = 1;
	NV3401_CS = 0;

	NV3401_RD = 0;

	data = nv3401_get_data();

	NV3401_RD = 1;

	NV3401_CS = 1;

	set_data_out(DATA_MODE_OUTPUT);

	return data;
}

static void write_lcd_data(uint16_t data)
{
	NV3401_CS = 0;

	///data
	NV3401_DC = 1;

	NV3401_RD = 1;

	nv3401_set_data(data);

	NV3401_WR = 0;
	NV3401_WR = 1;

	NV3401_CS = 1;
}
static void write_lcd_cmd(uint16_t cmd)
{
	NV3401_CS = 0;

	///command
	NV3401_DC = 0;

	NV3401_RD = 1;

	nv3401_set_data(cmd);

	NV3401_WR = 0;
	NV3401_WR = 1;

	NV3401_CS = 1;
}

static void write_lcd_reg(uint16_t cmd_data,uint16_t data)
{
	if (cmd_data == 0){
		write_lcd_cmd(data);
	} else {
		write_lcd_data(data);
	}
}

/// @brief NV3401 read id
void lcd_read_id()
{
	uint16_t id = 0;
	write_lcd_cmd(0xda);
	id = read_lcd_data();
	
	printf("1 lcd id:0x%x\n",id);
	write_lcd_cmd(0xdb);
	id =read_lcd_data();
	printf("2 lcd id:0x%x\n",id);

	write_lcd_cmd(0xdc);
	id = read_lcd_data();
	printf("3 lcd id:0x%x\n",id);
}


//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(vu16 regval)
{   
	regval=regval;		//ʹ��-O2�Ż���ʱ��,����������ʱ
	LCD->LCD_REG=regval;//д��Ҫд�ļĴ������	 
}

//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(vu16 data)
{	  
	data=data;			//ʹ��-O2�Ż���ʱ��,����������ʱ
	LCD->LCD_RAM=data;		 
}

//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{
	vu16 ram;			//��ֹ���Ż�
	ram=LCD->LCD_RAM;	
	return ram;	 
}

//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//д��Ҫд�ļĴ������	 
	LCD->LCD_RAM = LCD_RegValue;//д������	    		 
}

//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
	delay_us(5);		  
	return LCD_RD_DATA();		//���ض�����ֵ
}

//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	  
}

//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//дʮ��λGRAM
}

//ͨ���ú���ת��GBR��ʽΪRGB��ʽ
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f; 
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}

//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	LCD_SetCursor(x,y);
    if (lcddev.id == 0X5510)    //5510 ���Ͷ�GRAMָ��
    {
        LCD_WR_REG(0X2E00);
    }
    else                        //����IC(7796/5310/7789)���Ͷ�GRAMָ��
    {
        LCD_WR_REG(0X2E);
    }
 	  r = LCD_RD_DATA();								//dummy Read	   

	opt_delay(2);
    r = LCD_RD_DATA();          //ʵ��������ɫ

    //7796/5310/5510/7789 Ҫ��2�ζ���
	opt_delay(2);
    b = LCD_RD_DATA();
    g = r & 0XFF;               //���� 7796/5310/5510/7789, ��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
    g <<= 8;
		if (lcddev.id == 0X7796)    
    {
        return  r;              //7796ֱ�Ӷ��Ϳ���
    }  
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  // 5310/5510/7789 ��Ҫ��ʽת��һ��
}

//LCD������ʾ
void LCD_DisplayOn(void)
{					   
    if (lcddev.id == 0X5510)    //5510������ʾָ��
    {
        LCD_WR_REG(0X2900);     //������ʾ
    }
    else                        //7796/5310/7789 ���Ϳ�����ʾָ��
    {
        LCD_WR_REG(0X29);       //������ʾ
    }
}

//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
    if (lcddev.id == 0X5510)    //5510�ر���ʾָ��
    {
        LCD_WR_REG(0X2800);     //�ر���ʾ
    }
    else                        //7796/5310/7789 ���͹ر���ʾָ��
    {
        LCD_WR_REG(0X28);       //�ر���ʾ
    }
}

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    if (lcddev.id == 0X5510)     //5510��������
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(Xpos & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(Ypos >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(Ypos & 0XFF);
    }
    else     //7796/5310/7789��������
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos >> 8);
        LCD_WR_DATA(Xpos & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(Ypos >> 8);
        LCD_WR_DATA(Ypos & 0XFF);
    }
}

//����LCD���Զ�ɨ�跽��
//dir:0~7,����8������(���嶨���lcd.h)
//7796/5310/5510/7789��IC�Ѿ�ʵ�ʲ���
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��,
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.  
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
    //����ʱ��IC�ı�ɨ�跽��
    if (lcddev.dir == 1 )
    {
        switch (dir)   //����ת��
        {
            case 0:
                dir = 6;
                break;

            case 1:
                dir = 7;
                break;

            case 2:
                dir = 4;
                break;

            case 3:
                dir = 5;
                break;

            case 4:
                dir = 1;
                break;

            case 5:
                dir = 0;
                break;

            case 6:
                dir = 3;
                break;

            case 7:
                dir = 2;
                break;
        }
    }

    switch (dir)
    {
        case L2R_U2D://������,���ϵ���
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U://������,���µ���
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D://���ҵ���,���ϵ���
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U://���ҵ���,���µ���
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R://���ϵ���,������
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L://���ϵ���,���ҵ���
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R://���µ���,������
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L://���µ���,���ҵ���
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    if (lcddev.id == 0X5510)dirreg = 0X3600;
    else dirreg = 0X36;

    if (lcddev.id == 0X7796)   //7796 & 7789 Ҫ����BGRλ
    {
        regval |= 0X08;
    }

    LCD_WriteReg(dirreg, regval);

    
        if (regval & 0X20)
        {
            if (lcddev.width < lcddev.height)   //����X,Y
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
        else
        {
            if (lcddev.width > lcddev.height)   //����X,Y
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    

    //������ʾ����(����)��С
    if (lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(0);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(0);
        LCD_WR_REG(lcddev.setxcmd + 2);
        LCD_WR_DATA((lcddev.width - 1) >> 8);
        LCD_WR_REG(lcddev.setxcmd + 3);
        LCD_WR_DATA((lcddev.width - 1) & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(0);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(0);
        LCD_WR_REG(lcddev.setycmd + 2);
        LCD_WR_DATA((lcddev.height - 1) >> 8);
        LCD_WR_REG(lcddev.setycmd + 3);
        LCD_WR_DATA((lcddev.height - 1) & 0XFF);
    }
    else
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(0);
        LCD_WR_DATA(0);
        LCD_WR_DATA((lcddev.width - 1) >> 8);
        LCD_WR_DATA((lcddev.width - 1) & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(0);
        LCD_WR_DATA(0);
        LCD_WR_DATA((lcddev.height - 1) >> 8);
        LCD_WR_DATA((lcddev.height - 1) & 0XFF);
    }
}

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{ 
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	if(lcddev.id == 0X7789){LCD->LCD_RAM=POINT_COLOR>>8;	
		LCD->LCD_RAM=POINT_COLOR;	}
	else LCD->LCD_RAM=POINT_COLOR;  
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	   
 if (lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(y & 0XFF);
    }
    else     //7796/5310/7789����������
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_DATA(y & 0XFF);
    }

    LCD->LCD_REG=lcddev.wramcmd; 
		
		if(lcddev.id == 0X7789){LCD->LCD_RAM=color>>8;	
		LCD->LCD_RAM=color;}
		else 
			
    LCD->LCD_RAM=color; 
}


//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
    lcddev.dir = dir;       //����/����

    if (dir == 0)           //����
    {
        lcddev.width = 240;
        lcddev.height = 320;

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;   //����д��GRAM��ָ��
            lcddev.setxcmd = 0X2A00;   //����дX����ָ��
            lcddev.setycmd = 0X2B00;   //����дY����ָ��
            lcddev.width = 480;        //���ÿ���480
            lcddev.height = 800;       //���ø߶�800
        }
        else                        //����IC, ����: 7796 / 5310 / 7789��IC
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }

        if (lcddev.id == 0X5310||lcddev.id == 0X7796)    //�����5310/7796 ���ʾ�� 320*480�ֱ���
        {
            lcddev.width = 320;
            lcddev.height = 480;
        }
				if (lcddev.id == 0X9806)    /* �����9806 ���ʾ�� 480*800 �ֱ��� */
        {
            lcddev.width = 480;
            lcddev.height = 800;
        }  
    }
    else     //����
    {
        lcddev.width = 320;
        lcddev.height = 240;

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        }
				else if (lcddev.id == 0x1963 || lcddev.id == 0x9806)
        {
            lcddev.wramcmd = 0x2C;  /* ����д��GRAM��ָ�� */
            lcddev.setxcmd = 0x2A;  /* ����дX����ָ�� */
            lcddev.setycmd = 0x2B;  /* ����дY����ָ�� */
            lcddev.width = 800;     /* ���ÿ���800 */
            lcddev.height = 480;    /* ���ø߶�480 */
        }
        else                        //����IC, ����: 7796 / 5310 / 7789��IC
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }

        if (lcddev.id == 0X5310||lcddev.id == 0X7796)    //�����5310/7796 ���ʾ�� 320*480�ֱ���
        {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    LCD_Scan_Dir(DFT_SCAN_DIR);     //Ĭ��ɨ�跽��
}

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ��Ⱥ͸߶�,�������0!!
//�����С:width*height.
void LCD_Set_Window(u16 sx, u16 sy, u16 width, u16 height)
{
    u16 twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;

    if (lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(sx >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(sx & 0XFF);
        LCD_WR_REG(lcddev.setxcmd + 2);
        LCD_WR_DATA(twidth >> 8);
        LCD_WR_REG(lcddev.setxcmd + 3);
        LCD_WR_DATA(twidth & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(sy >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(sy & 0XFF);
        LCD_WR_REG(lcddev.setycmd + 2);
        LCD_WR_DATA(theight >> 8);
        LCD_WR_REG(lcddev.setycmd + 3);
        LCD_WR_DATA(theight & 0XFF);
    }
    else     //7796/5310/7789�����ô���
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(sx >> 8);
        LCD_WR_DATA(sx & 0XFF);
        LCD_WR_DATA(twidth >> 8);
        LCD_WR_DATA(twidth & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(sy >> 8);
        LCD_WR_DATA(sy & 0XFF);
        LCD_WR_DATA(theight >> 8);
        LCD_WR_DATA(theight & 0XFF);
    }
}

//SRAM�ײ�������ʱ��ʹ�ܣ����ŷ���
//�˺����ᱻHAL_SRAM_Init()����
//hsram:SRAM���
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_FSMC_CLK_ENABLE();			//ʹ��FSMCʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();			//ʹ��GPIODʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();			//ʹ��GPIOEʱ��
	__HAL_RCC_GPIOF_CLK_ENABLE();			//ʹ��GPIOFʱ��
	__HAL_RCC_GPIOG_CLK_ENABLE();			//ʹ��GPIOGʱ��
	
	//��ʼ��PD0,1,4,5,8,9,10,14,15
	GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|\
					 GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		  //���츴��
	GPIO_Initure.Pull=GPIO_PULLUP;			    //����
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;		  //����
	GPIO_Initure.Alternate=GPIO_AF12_FSMC;	//����ΪFSMC
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��
	
	//��ʼ��PE7,8,9,10,11,12,13,14,15
	GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|\
                     GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
	//��ʼ��PF12
	GPIO_Initure.Pin=GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
	//��ʼ��PG12
	GPIO_Initure.Pin=GPIO_PIN_7;
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);
}

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������LCDҺ����
//������ռ�ýϴ�flash,�û����Ը����Լ���ʵ�����,ɾ��δ�õ���LCD��ʼ������.�Խ�ʡ�ռ�.
void LCD_Init(void)
{ 	  
	GPIO_InitTypeDef GPIO_Initure;
	FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	FSMC_NORSRAM_TimingTypeDef FSMC_WriteTim;
	
  __HAL_RCC_GPIOD_CLK_ENABLE();			//ʹ��GPIOGʱ��  
	//__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
	
	GPIO_Initure.Pin=GPIO_PIN_12;          	//PB15,�������
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
	GPIO_Initure.Pull=GPIO_PULLUP;          //����
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	HAL_GPIO_Init(GPIOD,&GPIO_Initure); 
	
	GPIO_Initure.Pin=GPIO_PIN_11;
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //PG6,LCD��λ����
	
	TFTSRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;                
	TFTSRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;    
    
	TFTSRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK1;     				//ʹ��NE4
	TFTSRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	TFTSRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   			//SRAM
	TFTSRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; //16λ���ݿ���
	TFTSRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; //�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	TFTSRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;//�ȴ��źŵļ���,����ͻ��ģʽ����������
	TFTSRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   //�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	TFTSRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    //�洢��дʹ��
	TFTSRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           //�ȴ�ʹ��λ,�˴�δ�õ�
	TFTSRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_ENABLE;        //��дʹ�ò�ͬ��ʱ��
	TFTSRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	TFTSRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           //��ֹͻ��д
	TFTSRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
    
	//FMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x0F;       	//��ַ����ʱ�䣨ADDSET��Ϊ15��HCLK 1/168M=6ns*15=90ns
	FSMC_ReadWriteTim.AddressHoldTime=0;            //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
	FSMC_ReadWriteTim.DataSetupTime=60;				      //���ݱ���ʱ��(DATAST)Ϊ60��HCLK	=6*60=360ns
	FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
	//FMCдʱ����ƼĴ���
	FSMC_WriteTim.BusTurnAroundDuration=0;			    //������ת�׶γ���ʱ��Ϊ0���˱�������ֵ�Ļ���Ī��������Զ��޸�Ϊ4�����³������в�����
	FSMC_WriteTim.AddressSetupTime=9;          		  //��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns 
	FSMC_WriteTim.AddressHoldTime=0;
	FSMC_WriteTim.DataSetupTime=8;              	  //���ݱ���ʱ��Ϊ6ns*9��HCLK=54n
	FSMC_WriteTim.AccessMode=FSMC_ACCESS_MODE_A;    //ģʽA
	HAL_SRAM_Init(&TFTSRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);	//��ʼ��SRAM����

	delay_ms(50); // delay 50 ms 
	
  //LCD��λ
	LCD_RST=1;
	delay_ms(10);
	LCD_RST=0;
	delay_ms(50);
	LCD_RST=1; 
	delay_ms(200);  
	
	//����7796 ID�Ķ�ȡ		
	LCD_WR_REG(0XD3);				   
	lcddev.id=LCD_RD_DATA();	//dummy read 	
	lcddev.id=LCD_RD_DATA();	//����0X00
	lcddev.id=LCD_RD_DATA();   	//��ȡ77								   
	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA();  	//��ȡ96 	   			   
	if(lcddev.id!=0X7796)		//����ST7796,���Կ����ǲ���ST7789
	{
        LCD_WR_REG(0X04);
        lcddev.id = LCD_RD_DATA();      //dummy read
        lcddev.id = LCD_RD_DATA();      //����0X85
        lcddev.id = LCD_RD_DATA();      //��ȡ0X85
        lcddev.id <<= 8;
        lcddev.id |= LCD_RD_DATA() & 0XFF;     //��ȡ0X52

        if (lcddev.id == 0X8552)        //��8552��IDת����7789
        {
            lcddev.id = 0x7789;
        }

        if (lcddev.id != 0x7789)        //Ҳ����ST7789,�����ǲ���NT35310
        {
            LCD_WR_REG(0XD4);				   
            lcddev.id=LCD_RD_DATA();//dummy read  
            lcddev.id=LCD_RD_DATA();//����0X01	 
            lcddev.id=LCD_RD_DATA();//����0X53	
            lcddev.id<<=8;	 
            lcddev.id|=LCD_RD_DATA();	//�������0X10	 
            if(lcddev.id!=0X5310)		//Ҳ����NT35310,���Կ����ǲ���NT35510
            {
                //������Կ�������ṩ,�հἴ�ɣ�
                LCD_WriteReg(0xF000, 0x0055);
                LCD_WriteReg(0xF001, 0x00AA);
                LCD_WriteReg(0xF002, 0x0052);
                LCD_WriteReg(0xF003, 0x0008);
                LCD_WriteReg(0xF004, 0x0001);

                LCD_WR_REG(0xC500);             //��ȡID��8λ
                lcddev.id = LCD_RD_DATA();      //����0X55
                lcddev.id <<= 8;

                LCD_WR_REG(0xC501);             //��ȡID��8λ
                lcddev.id |= LCD_RD_DATA();     //����0X10
                delay_ms(5);
             // if(lcddev.id==0x8000)lcddev.id=0x5510;//NT35510���ص�ID��8000H,Ϊ��������,����ǿ������Ϊ5510
							  if (lcddev.id != 0x5510)    /* Ҳ����NT5510,���Կ����ǲ���ILI9806 */
								{
										LCD_WR_REG(0XD3);
										lcddev.id = LCD_RD_DATA();  /* dummy read */
										lcddev.id = LCD_RD_DATA();  /* ����0X00 */
										lcddev.id = LCD_RD_DATA();  /* ����0X98 */
										lcddev.id <<= 8;
										lcddev.id |= LCD_RD_DATA(); /* ����0X06 */     
								}				
            }
		    }
	}   
	//printf(" LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID   
	   if (lcddev.id == 0X7796)    //7796��ʼ��
	{	 
        LCD_WR_REG(0xF0);     
				LCD_WR_DATA(0xC3);   

				LCD_WR_REG(0xF0);     
				LCD_WR_DATA(0x96);   

				LCD_WR_REG(0x36);     
				LCD_WR_DATA(0x48);   

				LCD_WR_REG(0x3A);     
				LCD_WR_DATA(0x55);   

				LCD_WR_REG(0xB4);     //1-dot Inversion
				LCD_WR_DATA(0x01);   
						
				LCD_WR_REG(0xB6);     //
				LCD_WR_DATA(0x80); 
				LCD_WR_DATA(0x22);	
				LCD_WR_DATA(0x3B);			

				LCD_WR_REG(0xB7);     
				LCD_WR_DATA(0xC6);

				LCD_WR_REG(0xC0);     
				LCD_WR_DATA(0x80);   
				LCD_WR_DATA(0x16);   

				LCD_WR_REG(0xC1);     
				LCD_WR_DATA(0x19);   //18  //00

				LCD_WR_REG(0xC2);     
				LCD_WR_DATA(0xA7);   

				LCD_WR_REG(0xC5);     
				LCD_WR_DATA(0x16);   


				LCD_WR_REG(0xE8);     
				LCD_WR_DATA(0x40);
				LCD_WR_DATA(0x8A);
				LCD_WR_DATA(0x00);
				LCD_WR_DATA(0x00);
				LCD_WR_DATA(0x29);
				LCD_WR_DATA(0x19);
				LCD_WR_DATA(0xA5);
				LCD_WR_DATA(0x33);

				LCD_WR_REG(0xE0);     
				LCD_WR_DATA(0xF0);   
				LCD_WR_DATA(0x07);   
				LCD_WR_DATA(0x0D);   
				LCD_WR_DATA(0x04);   
				LCD_WR_DATA(0x05);   
				LCD_WR_DATA(0x14);   
				LCD_WR_DATA(0x36);   
				LCD_WR_DATA(0x54);   
				LCD_WR_DATA(0x4C);   
				LCD_WR_DATA(0x38);   
				LCD_WR_DATA(0x13);   
				LCD_WR_DATA(0x14);   
				LCD_WR_DATA(0x2E);   
				LCD_WR_DATA(0x34);   

				LCD_WR_REG(0xE1);     
				LCD_WR_DATA(0xF0);   
				LCD_WR_DATA(0x10);   
				LCD_WR_DATA(0x14);   
				LCD_WR_DATA(0x0E);   
				LCD_WR_DATA(0x0C);   
				LCD_WR_DATA(0x08);   
				LCD_WR_DATA(0x35);   
				LCD_WR_DATA(0x44);   
				LCD_WR_DATA(0x4C);   
				LCD_WR_DATA(0x26);   
				LCD_WR_DATA(0x10);   
				LCD_WR_DATA(0x12);   
				LCD_WR_DATA(0x2C);   
				LCD_WR_DATA(0x32); 

        LCD_WR_REG(0xF0);     
        LCD_WR_DATA(0x3C);   

        LCD_WR_REG(0xF0);     
        LCD_WR_DATA(0x69);   

        LCD_WR_REG(0x35);     
        LCD_WR_DATA(0x00); 

        LCD_WR_REG(0x21); 
 
        LCD_WR_REG(0x11);     

        delay_ms(120);                //ms

        LCD_WR_REG(0x29);     
        delay_ms(50); 

				LCD_WR_REG(0x2A);    //320 
				LCD_WR_DATA(0x00);   
				LCD_WR_DATA(0x00);   
				LCD_WR_DATA(0x01);   
        LCD_WR_DATA(0x3F);   

        LCD_WR_REG(0x2B);    //480
        LCD_WR_DATA(0x00);   
        LCD_WR_DATA(0x00);   
        LCD_WR_DATA(0x01);   
        LCD_WR_DATA(0xDF); 

        LCD_WR_REG(0x2C); 
	}
    else if(lcddev.id==0x7789)      //7789��ʼ��
    {
         LCD_WR_REG(0x11);   
			delay_ms(120);                //ms            

			LCD_WR_REG(0x36);     
			LCD_WR_DATA(0x00);   

			LCD_WR_REG(0x3A);     
			LCD_WR_DATA(0x55);   

			LCD_WR_REG(0xB2);     
			LCD_WR_DATA(0x0C);   
			LCD_WR_DATA(0x0C);   
			LCD_WR_DATA(0x00);   
			LCD_WR_DATA(0x33);   
			LCD_WR_DATA(0x33);   

			LCD_WR_REG(0xB7);     
			LCD_WR_DATA(0x56);   

			LCD_WR_REG(0xBB);     
			LCD_WR_DATA(0x20);   

			LCD_WR_REG(0xC0);     
			LCD_WR_DATA(0x2C);   

			LCD_WR_REG(0xC2);     
			LCD_WR_DATA(0x01);   

			LCD_WR_REG(0xC3);     
			LCD_WR_DATA(0x0F);   

			LCD_WR_REG(0xC4);     
			LCD_WR_DATA(0x20);   

			LCD_WR_REG(0xC6);     
			LCD_WR_DATA(0x0F);   

			LCD_WR_REG(0xD0);     
			LCD_WR_DATA(0xA4);   
			LCD_WR_DATA(0xA1);   

			LCD_WR_REG(0xD6);     
			LCD_WR_DATA(0xA1);   

			LCD_WR_REG(0xE0);
			LCD_WR_DATA(0xF0);
			LCD_WR_DATA(0x00);
			LCD_WR_DATA(0x06);
			LCD_WR_DATA(0x06);
			LCD_WR_DATA(0x07);
			LCD_WR_DATA(0x05);
			LCD_WR_DATA(0x30);
			LCD_WR_DATA(0x44);
			LCD_WR_DATA(0x48);
			LCD_WR_DATA(0x38);
			LCD_WR_DATA(0x11);
			LCD_WR_DATA(0x10);
			LCD_WR_DATA(0x2E);
			LCD_WR_DATA(0x34);

			LCD_WR_REG(0xE1);
			LCD_WR_DATA(0xF0);
			LCD_WR_DATA(0x0A);
			LCD_WR_DATA(0x0E);
			LCD_WR_DATA(0x0D);
			LCD_WR_DATA(0x0B);
			LCD_WR_DATA(0x27);
			LCD_WR_DATA(0x2F);
			LCD_WR_DATA(0x44);
			LCD_WR_DATA(0x47);
			LCD_WR_DATA(0x35);
			LCD_WR_DATA(0x12);
			LCD_WR_DATA(0x12);
			LCD_WR_DATA(0x2C);
			LCD_WR_DATA(0x32);

			LCD_WR_REG(0x35);     
			LCD_WR_DATA(0x00);   

			LCD_WR_REG(0x21);     

			LCD_WR_REG(0x29);     

			LCD_WR_REG(0x2A);     //Column Address Set
			LCD_WR_DATA(0x00);   
			LCD_WR_DATA(0x00);   //0
			LCD_WR_DATA(0x01);   
			LCD_WR_DATA(0x3F);   

			LCD_WR_REG(0x2B);     //Row Address Set
			LCD_WR_DATA(0x00);   
			LCD_WR_DATA(0x00);   //0
			LCD_WR_DATA(0x00);   
			LCD_WR_DATA(0xEF);   

			LCD_WR_REG(0x2C); 
    }
    else if(lcddev.id==0x5310)
	{ 
		LCD_WR_REG(0xED);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0xFE);

		LCD_WR_REG(0xEE);
		LCD_WR_DATA(0xDE);
		LCD_WR_DATA(0x21);

		LCD_WR_REG(0xF1);
		LCD_WR_DATA(0x01);
		LCD_WR_REG(0xDF);
		LCD_WR_DATA(0x10);

		//VCOMvoltage//
		LCD_WR_REG(0xC4);
		LCD_WR_DATA(0x8F);	  //5f

		LCD_WR_REG(0xC6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xE2);
		LCD_WR_DATA(0xE2);
		LCD_WR_DATA(0xE2);
		LCD_WR_REG(0xBF);
		LCD_WR_DATA(0xAA);

		LCD_WR_REG(0xB0);
		LCD_WR_DATA(0x0D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x0D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x11);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x19);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x21);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x5D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x5D);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB1);
		LCD_WR_DATA(0x80);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x8B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x96);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB4);
		LCD_WR_DATA(0x8B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x96);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA1);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB5);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x04);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3F);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x5E);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x64);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x8C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xAC);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDC);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x70);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x90);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xEB);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDC);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xB8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xBA);
		LCD_WR_DATA(0x24);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC1);
		LCD_WR_DATA(0x20);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x54);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xFF);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC2);
		LCD_WR_DATA(0x0A);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x04);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC3);
		LCD_WR_DATA(0x3C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3A);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x39);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x37);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x36);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x32);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2F);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x29);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x26);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x24);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x24);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x23);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x36);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x32);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2F);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x29);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x26);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x24);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x24);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x23);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC4);
		LCD_WR_DATA(0x62);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x84);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF0);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x18);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA4);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x18);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x50);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x0C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x17);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x95);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xE6);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC5);
		LCD_WR_DATA(0x32);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x65);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x76);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC6);
		LCD_WR_DATA(0x20);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x17);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC9);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE0);
		LCD_WR_DATA(0x16);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x1C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x21);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x36);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x46);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x52);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x64);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x7A);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x8B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB9);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC4);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xCA);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD9);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xE0);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE1);
		LCD_WR_DATA(0x16);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x1C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x22);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x36);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x45);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x52);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x64);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x7A);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x8B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB9);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC4);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xCA);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xE0);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE2);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x0B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x1B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x34);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x4F);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x61);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x79);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x97);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD1);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDD);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);
		LCD_WR_REG(0xE3);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x1C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x33);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x50);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x62);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x78);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x97);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC7);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD1);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD5);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDD);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE4);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x2A);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x4B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x5D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x74);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x84);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x93);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xBE);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC4);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xCD);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDD);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);
		LCD_WR_REG(0xE5);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x29);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x3C);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x4B);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x5D);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x74);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x84);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x93);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xA2);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xB3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xBE);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xC4);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xCD);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xD3);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xDC);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xF3);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE6);
		LCD_WR_DATA(0x11);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x34);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x56);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x76);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x77);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x66);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xBB);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x66);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x45);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x43);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE7);
		LCD_WR_DATA(0x32);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x76);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x66);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x67);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x67);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x87);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xBB);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x77);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x56);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x23); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x33);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x45);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE8);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x87);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x77);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x66);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x88);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xAA);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xBB);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x99);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x66);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x55);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE9);
		LCD_WR_DATA(0xAA);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0x00);
		LCD_WR_DATA(0xAA);

		LCD_WR_REG(0xCF);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xF0);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x50);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xF3);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xF9);
		LCD_WR_DATA(0x06);
		LCD_WR_DATA(0x10);
		LCD_WR_DATA(0x29);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0x3A);
		LCD_WR_DATA(0x55);	//66

		LCD_WR_REG(0x11);
		delay_ms(100);
		LCD_WR_REG(0x29);
		LCD_WR_REG(0x35);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0x51);
		LCD_WR_DATA(0xFF);
		LCD_WR_REG(0x53);
		LCD_WR_DATA(0x2C);
		LCD_WR_REG(0x55);
		LCD_WR_DATA(0x82);
		LCD_WR_REG(0x2c);
	}
	else if(lcddev.id==0x5510)
	{
		LCD_WriteReg(0xF000,0x55);
		LCD_WriteReg(0xF001,0xAA);
		LCD_WriteReg(0xF002,0x52);
		LCD_WriteReg(0xF003,0x08);
		LCD_WriteReg(0xF004,0x01);
		//AVDD Set AVDD 5.2V
		LCD_WriteReg(0xB000,0x0D);
		LCD_WriteReg(0xB001,0x0D);
		LCD_WriteReg(0xB002,0x0D);
		//AVDD ratio
		LCD_WriteReg(0xB600,0x34);
		LCD_WriteReg(0xB601,0x34);
		LCD_WriteReg(0xB602,0x34);
		//AVEE -5.2V
		LCD_WriteReg(0xB100,0x0D);
		LCD_WriteReg(0xB101,0x0D);
		LCD_WriteReg(0xB102,0x0D);
		//AVEE ratio
		LCD_WriteReg(0xB700,0x34);
		LCD_WriteReg(0xB701,0x34);
		LCD_WriteReg(0xB702,0x34);
		//VCL -2.5V
		LCD_WriteReg(0xB200,0x00);
		LCD_WriteReg(0xB201,0x00);
		LCD_WriteReg(0xB202,0x00);
		//VCL ratio
		LCD_WriteReg(0xB800,0x24);
		LCD_WriteReg(0xB801,0x24);
		LCD_WriteReg(0xB802,0x24);
		//VGH 15V (Free pump)
		LCD_WriteReg(0xBF00,0x01);
		LCD_WriteReg(0xB300,0x0F);
		LCD_WriteReg(0xB301,0x0F);
		LCD_WriteReg(0xB302,0x0F);
		//VGH ratio
		LCD_WriteReg(0xB900,0x34);
		LCD_WriteReg(0xB901,0x34);
		LCD_WriteReg(0xB902,0x34);
		//VGL_REG -10V
		LCD_WriteReg(0xB500,0x08);
		LCD_WriteReg(0xB501,0x08);
		LCD_WriteReg(0xB502,0x08);
		LCD_WriteReg(0xC200,0x03);
		//VGLX ratio
		LCD_WriteReg(0xBA00,0x24);
		LCD_WriteReg(0xBA01,0x24);
		LCD_WriteReg(0xBA02,0x24);
		//VGMP/VGSP 4.5V/0V
		LCD_WriteReg(0xBC00,0x00);
		LCD_WriteReg(0xBC01,0x78);
		LCD_WriteReg(0xBC02,0x00);
		//VGMN/VGSN -4.5V/0V
		LCD_WriteReg(0xBD00,0x00);
		LCD_WriteReg(0xBD01,0x78);
		LCD_WriteReg(0xBD02,0x00);
		//VCOM
		LCD_WriteReg(0xBE00,0x00);
		LCD_WriteReg(0xBE01,0x64);
		//Gamma Setting
		LCD_WriteReg(0xD100,0x00);
		LCD_WriteReg(0xD101,0x33);
		LCD_WriteReg(0xD102,0x00);
		LCD_WriteReg(0xD103,0x34);
		LCD_WriteReg(0xD104,0x00);
		LCD_WriteReg(0xD105,0x3A);
		LCD_WriteReg(0xD106,0x00);
		LCD_WriteReg(0xD107,0x4A);
		LCD_WriteReg(0xD108,0x00);
		LCD_WriteReg(0xD109,0x5C);
		LCD_WriteReg(0xD10A,0x00);
		LCD_WriteReg(0xD10B,0x81);
		LCD_WriteReg(0xD10C,0x00);
		LCD_WriteReg(0xD10D,0xA6);
		LCD_WriteReg(0xD10E,0x00);
		LCD_WriteReg(0xD10F,0xE5);
		LCD_WriteReg(0xD110,0x01);
		LCD_WriteReg(0xD111,0x13);
		LCD_WriteReg(0xD112,0x01);
		LCD_WriteReg(0xD113,0x54);
		LCD_WriteReg(0xD114,0x01);
		LCD_WriteReg(0xD115,0x82);
		LCD_WriteReg(0xD116,0x01);
		LCD_WriteReg(0xD117,0xCA);
		LCD_WriteReg(0xD118,0x02);
		LCD_WriteReg(0xD119,0x00);
		LCD_WriteReg(0xD11A,0x02);
		LCD_WriteReg(0xD11B,0x01);
		LCD_WriteReg(0xD11C,0x02);
		LCD_WriteReg(0xD11D,0x34);
		LCD_WriteReg(0xD11E,0x02);
		LCD_WriteReg(0xD11F,0x67);
		LCD_WriteReg(0xD120,0x02);
		LCD_WriteReg(0xD121,0x84);
		LCD_WriteReg(0xD122,0x02);
		LCD_WriteReg(0xD123,0xA4);
		LCD_WriteReg(0xD124,0x02);
		LCD_WriteReg(0xD125,0xB7);
		LCD_WriteReg(0xD126,0x02);
		LCD_WriteReg(0xD127,0xCF);
		LCD_WriteReg(0xD128,0x02);
		LCD_WriteReg(0xD129,0xDE);
		LCD_WriteReg(0xD12A,0x02);
		LCD_WriteReg(0xD12B,0xF2);
		LCD_WriteReg(0xD12C,0x02);
		LCD_WriteReg(0xD12D,0xFE);
		LCD_WriteReg(0xD12E,0x03);
		LCD_WriteReg(0xD12F,0x10);
		LCD_WriteReg(0xD130,0x03);
		LCD_WriteReg(0xD131,0x33);
		LCD_WriteReg(0xD132,0x03);
		LCD_WriteReg(0xD133,0x6D);
		LCD_WriteReg(0xD200,0x00);
		LCD_WriteReg(0xD201,0x33);
		LCD_WriteReg(0xD202,0x00);
		LCD_WriteReg(0xD203,0x34);
		LCD_WriteReg(0xD204,0x00);
		LCD_WriteReg(0xD205,0x3A);
		LCD_WriteReg(0xD206,0x00);
		LCD_WriteReg(0xD207,0x4A);
		LCD_WriteReg(0xD208,0x00);
		LCD_WriteReg(0xD209,0x5C);
		LCD_WriteReg(0xD20A,0x00);

		LCD_WriteReg(0xD20B,0x81);
		LCD_WriteReg(0xD20C,0x00);
		LCD_WriteReg(0xD20D,0xA6);
		LCD_WriteReg(0xD20E,0x00);
		LCD_WriteReg(0xD20F,0xE5);
		LCD_WriteReg(0xD210,0x01);
		LCD_WriteReg(0xD211,0x13);
		LCD_WriteReg(0xD212,0x01);
		LCD_WriteReg(0xD213,0x54);
		LCD_WriteReg(0xD214,0x01);
		LCD_WriteReg(0xD215,0x82);
		LCD_WriteReg(0xD216,0x01);
		LCD_WriteReg(0xD217,0xCA);
		LCD_WriteReg(0xD218,0x02);
		LCD_WriteReg(0xD219,0x00);
		LCD_WriteReg(0xD21A,0x02);
		LCD_WriteReg(0xD21B,0x01);
		LCD_WriteReg(0xD21C,0x02);
		LCD_WriteReg(0xD21D,0x34);
		LCD_WriteReg(0xD21E,0x02);
		LCD_WriteReg(0xD21F,0x67);
		LCD_WriteReg(0xD220,0x02);
		LCD_WriteReg(0xD221,0x84);
		LCD_WriteReg(0xD222,0x02);
		LCD_WriteReg(0xD223,0xA4);
		LCD_WriteReg(0xD224,0x02);
		LCD_WriteReg(0xD225,0xB7);
		LCD_WriteReg(0xD226,0x02);
		LCD_WriteReg(0xD227,0xCF);
		LCD_WriteReg(0xD228,0x02);
		LCD_WriteReg(0xD229,0xDE);
		LCD_WriteReg(0xD22A,0x02);
		LCD_WriteReg(0xD22B,0xF2);
		LCD_WriteReg(0xD22C,0x02);
		LCD_WriteReg(0xD22D,0xFE);
		LCD_WriteReg(0xD22E,0x03);
		LCD_WriteReg(0xD22F,0x10);
		LCD_WriteReg(0xD230,0x03);
		LCD_WriteReg(0xD231,0x33);
		LCD_WriteReg(0xD232,0x03);
		LCD_WriteReg(0xD233,0x6D);
		LCD_WriteReg(0xD300,0x00);
		LCD_WriteReg(0xD301,0x33);
		LCD_WriteReg(0xD302,0x00);
		LCD_WriteReg(0xD303,0x34);
		LCD_WriteReg(0xD304,0x00);
		LCD_WriteReg(0xD305,0x3A);
		LCD_WriteReg(0xD306,0x00);
		LCD_WriteReg(0xD307,0x4A);
		LCD_WriteReg(0xD308,0x00);
		LCD_WriteReg(0xD309,0x5C);
		LCD_WriteReg(0xD30A,0x00);

		LCD_WriteReg(0xD30B,0x81);
		LCD_WriteReg(0xD30C,0x00);
		LCD_WriteReg(0xD30D,0xA6);
		LCD_WriteReg(0xD30E,0x00);
		LCD_WriteReg(0xD30F,0xE5);
		LCD_WriteReg(0xD310,0x01);
		LCD_WriteReg(0xD311,0x13);
		LCD_WriteReg(0xD312,0x01);
		LCD_WriteReg(0xD313,0x54);
		LCD_WriteReg(0xD314,0x01);
		LCD_WriteReg(0xD315,0x82);
		LCD_WriteReg(0xD316,0x01);
		LCD_WriteReg(0xD317,0xCA);
		LCD_WriteReg(0xD318,0x02);
		LCD_WriteReg(0xD319,0x00);
		LCD_WriteReg(0xD31A,0x02);
		LCD_WriteReg(0xD31B,0x01);
		LCD_WriteReg(0xD31C,0x02);
		LCD_WriteReg(0xD31D,0x34);
		LCD_WriteReg(0xD31E,0x02);
		LCD_WriteReg(0xD31F,0x67);
		LCD_WriteReg(0xD320,0x02);
		LCD_WriteReg(0xD321,0x84);
		LCD_WriteReg(0xD322,0x02);
		LCD_WriteReg(0xD323,0xA4);
		LCD_WriteReg(0xD324,0x02);
		LCD_WriteReg(0xD325,0xB7);
		LCD_WriteReg(0xD326,0x02);
		LCD_WriteReg(0xD327,0xCF);
		LCD_WriteReg(0xD328,0x02);
		LCD_WriteReg(0xD329,0xDE);
		LCD_WriteReg(0xD32A,0x02);
		LCD_WriteReg(0xD32B,0xF2);
		LCD_WriteReg(0xD32C,0x02);
		LCD_WriteReg(0xD32D,0xFE);
		LCD_WriteReg(0xD32E,0x03);
		LCD_WriteReg(0xD32F,0x10);
		LCD_WriteReg(0xD330,0x03);
		LCD_WriteReg(0xD331,0x33);
		LCD_WriteReg(0xD332,0x03);
		LCD_WriteReg(0xD333,0x6D);
		LCD_WriteReg(0xD400,0x00);
		LCD_WriteReg(0xD401,0x33);
		LCD_WriteReg(0xD402,0x00);
		LCD_WriteReg(0xD403,0x34);
		LCD_WriteReg(0xD404,0x00);
		LCD_WriteReg(0xD405,0x3A);
		LCD_WriteReg(0xD406,0x00);
		LCD_WriteReg(0xD407,0x4A);
		LCD_WriteReg(0xD408,0x00);
		LCD_WriteReg(0xD409,0x5C);
		LCD_WriteReg(0xD40A,0x00);
		LCD_WriteReg(0xD40B,0x81);

		LCD_WriteReg(0xD40C,0x00);
		LCD_WriteReg(0xD40D,0xA6);
		LCD_WriteReg(0xD40E,0x00);
		LCD_WriteReg(0xD40F,0xE5);
		LCD_WriteReg(0xD410,0x01);
		LCD_WriteReg(0xD411,0x13);
		LCD_WriteReg(0xD412,0x01);
		LCD_WriteReg(0xD413,0x54);
		LCD_WriteReg(0xD414,0x01);
		LCD_WriteReg(0xD415,0x82);
		LCD_WriteReg(0xD416,0x01);
		LCD_WriteReg(0xD417,0xCA);
		LCD_WriteReg(0xD418,0x02);
		LCD_WriteReg(0xD419,0x00);
		LCD_WriteReg(0xD41A,0x02);
		LCD_WriteReg(0xD41B,0x01);
		LCD_WriteReg(0xD41C,0x02);
		LCD_WriteReg(0xD41D,0x34);
		LCD_WriteReg(0xD41E,0x02);
		LCD_WriteReg(0xD41F,0x67);
		LCD_WriteReg(0xD420,0x02);
		LCD_WriteReg(0xD421,0x84);
		LCD_WriteReg(0xD422,0x02);
		LCD_WriteReg(0xD423,0xA4);
		LCD_WriteReg(0xD424,0x02);
		LCD_WriteReg(0xD425,0xB7);
		LCD_WriteReg(0xD426,0x02);
		LCD_WriteReg(0xD427,0xCF);
		LCD_WriteReg(0xD428,0x02);
		LCD_WriteReg(0xD429,0xDE);
		LCD_WriteReg(0xD42A,0x02);
		LCD_WriteReg(0xD42B,0xF2);
		LCD_WriteReg(0xD42C,0x02);
		LCD_WriteReg(0xD42D,0xFE);
		LCD_WriteReg(0xD42E,0x03);
		LCD_WriteReg(0xD42F,0x10);
		LCD_WriteReg(0xD430,0x03);
		LCD_WriteReg(0xD431,0x33);
		LCD_WriteReg(0xD432,0x03);
		LCD_WriteReg(0xD433,0x6D);
		LCD_WriteReg(0xD500,0x00);
		LCD_WriteReg(0xD501,0x33);
		LCD_WriteReg(0xD502,0x00);
		LCD_WriteReg(0xD503,0x34);
		LCD_WriteReg(0xD504,0x00);
		LCD_WriteReg(0xD505,0x3A);
		LCD_WriteReg(0xD506,0x00);
		LCD_WriteReg(0xD507,0x4A);
		LCD_WriteReg(0xD508,0x00);
		LCD_WriteReg(0xD509,0x5C);
		LCD_WriteReg(0xD50A,0x00);
		LCD_WriteReg(0xD50B,0x81);

		LCD_WriteReg(0xD50C,0x00);
		LCD_WriteReg(0xD50D,0xA6);
		LCD_WriteReg(0xD50E,0x00);
		LCD_WriteReg(0xD50F,0xE5);
		LCD_WriteReg(0xD510,0x01);
		LCD_WriteReg(0xD511,0x13);
		LCD_WriteReg(0xD512,0x01);
		LCD_WriteReg(0xD513,0x54);
		LCD_WriteReg(0xD514,0x01);
		LCD_WriteReg(0xD515,0x82);
		LCD_WriteReg(0xD516,0x01);
		LCD_WriteReg(0xD517,0xCA);
		LCD_WriteReg(0xD518,0x02);
		LCD_WriteReg(0xD519,0x00);
		LCD_WriteReg(0xD51A,0x02);
		LCD_WriteReg(0xD51B,0x01);
		LCD_WriteReg(0xD51C,0x02);
		LCD_WriteReg(0xD51D,0x34);
		LCD_WriteReg(0xD51E,0x02);
		LCD_WriteReg(0xD51F,0x67);
		LCD_WriteReg(0xD520,0x02);
		LCD_WriteReg(0xD521,0x84);
		LCD_WriteReg(0xD522,0x02);
		LCD_WriteReg(0xD523,0xA4);
		LCD_WriteReg(0xD524,0x02);
		LCD_WriteReg(0xD525,0xB7);
		LCD_WriteReg(0xD526,0x02);
		LCD_WriteReg(0xD527,0xCF);
		LCD_WriteReg(0xD528,0x02);
		LCD_WriteReg(0xD529,0xDE);
		LCD_WriteReg(0xD52A,0x02);
		LCD_WriteReg(0xD52B,0xF2);
		LCD_WriteReg(0xD52C,0x02);
		LCD_WriteReg(0xD52D,0xFE);
		LCD_WriteReg(0xD52E,0x03);
		LCD_WriteReg(0xD52F,0x10);
		LCD_WriteReg(0xD530,0x03);
		LCD_WriteReg(0xD531,0x33);
		LCD_WriteReg(0xD532,0x03);
		LCD_WriteReg(0xD533,0x6D);
		LCD_WriteReg(0xD600,0x00);
		LCD_WriteReg(0xD601,0x33);
		LCD_WriteReg(0xD602,0x00);
		LCD_WriteReg(0xD603,0x34);
		LCD_WriteReg(0xD604,0x00);
		LCD_WriteReg(0xD605,0x3A);
		LCD_WriteReg(0xD606,0x00);
		LCD_WriteReg(0xD607,0x4A);
		LCD_WriteReg(0xD608,0x00);
		LCD_WriteReg(0xD609,0x5C);
		LCD_WriteReg(0xD60A,0x00);
		LCD_WriteReg(0xD60B,0x81);

		LCD_WriteReg(0xD60C,0x00);
		LCD_WriteReg(0xD60D,0xA6);
		LCD_WriteReg(0xD60E,0x00);
		LCD_WriteReg(0xD60F,0xE5);
		LCD_WriteReg(0xD610,0x01);
		LCD_WriteReg(0xD611,0x13);
		LCD_WriteReg(0xD612,0x01);
		LCD_WriteReg(0xD613,0x54);
		LCD_WriteReg(0xD614,0x01);
		LCD_WriteReg(0xD615,0x82);
		LCD_WriteReg(0xD616,0x01);
		LCD_WriteReg(0xD617,0xCA);
		LCD_WriteReg(0xD618,0x02);
		LCD_WriteReg(0xD619,0x00);
		LCD_WriteReg(0xD61A,0x02);
		LCD_WriteReg(0xD61B,0x01);
		LCD_WriteReg(0xD61C,0x02);
		LCD_WriteReg(0xD61D,0x34);
		LCD_WriteReg(0xD61E,0x02);
		LCD_WriteReg(0xD61F,0x67);
		LCD_WriteReg(0xD620,0x02);
		LCD_WriteReg(0xD621,0x84);
		LCD_WriteReg(0xD622,0x02);
		LCD_WriteReg(0xD623,0xA4);
		LCD_WriteReg(0xD624,0x02);
		LCD_WriteReg(0xD625,0xB7);
		LCD_WriteReg(0xD626,0x02);
		LCD_WriteReg(0xD627,0xCF);
		LCD_WriteReg(0xD628,0x02);
		LCD_WriteReg(0xD629,0xDE);
		LCD_WriteReg(0xD62A,0x02);
		LCD_WriteReg(0xD62B,0xF2);
		LCD_WriteReg(0xD62C,0x02);
		LCD_WriteReg(0xD62D,0xFE);
		LCD_WriteReg(0xD62E,0x03);
		LCD_WriteReg(0xD62F,0x10);
		LCD_WriteReg(0xD630,0x03);
		LCD_WriteReg(0xD631,0x33);
		LCD_WriteReg(0xD632,0x03);
		LCD_WriteReg(0xD633,0x6D);
		//LV2 Page 0 enable
		LCD_WriteReg(0xF000,0x55);
		LCD_WriteReg(0xF001,0xAA);
		LCD_WriteReg(0xF002,0x52);
		LCD_WriteReg(0xF003,0x08);
		LCD_WriteReg(0xF004,0x00);
		//Display control
		LCD_WriteReg(0xB100, 0xCC);
		LCD_WriteReg(0xB101, 0x00);
		//Source hold time
		LCD_WriteReg(0xB600,0x05);
		//Gate EQ control
		LCD_WriteReg(0xB700,0x70);
		LCD_WriteReg(0xB701,0x70);
		//Source EQ control (Mode 2)
		LCD_WriteReg(0xB800,0x01);
		LCD_WriteReg(0xB801,0x03);
		LCD_WriteReg(0xB802,0x03);
		LCD_WriteReg(0xB803,0x03);
		//Inversion mode (2-dot)
		LCD_WriteReg(0xBC00,0x02);
		LCD_WriteReg(0xBC01,0x00);
		LCD_WriteReg(0xBC02,0x00);
		//Timing control 4H w/ 4-delay
		LCD_WriteReg(0xC900,0xD0);
		LCD_WriteReg(0xC901,0x02);
		LCD_WriteReg(0xC902,0x50);
		LCD_WriteReg(0xC903,0x50);
		LCD_WriteReg(0xC904,0x50);
		LCD_WriteReg(0x3500,0x00);
		LCD_WriteReg(0x3A00,0x55);  //16-bit/pixel
		LCD_WR_REG(0x1100);
		delay_us(120);
		LCD_WR_REG(0x2900);
	}
	else if(lcddev.id==0x9806)
	{
    LCD_WR_REG(0xFF); /* EXTC Command Set enable register */
    LCD_WR_DATA(0xFF);
    LCD_WR_DATA(0x98);
    LCD_WR_DATA(0x06);

    LCD_WR_REG(0xBA); // SPI Interface Setting 
    LCD_WR_DATA(0x60);

    LCD_WR_REG(0xBC); /* GIP 1 */
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x61);
    LCD_WR_DATA(0xFB);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x2E);
    LCD_WR_DATA(0x73);
    LCD_WR_DATA(0xFF);
    LCD_WR_DATA(0xFF);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x66);
    LCD_WR_DATA(0x63);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xBD); /* GIP 2 */
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x23);
    LCD_WR_DATA(0x45);
    LCD_WR_DATA(0x67);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x23);
    LCD_WR_DATA(0x45);
    LCD_WR_DATA(0x67);

    LCD_WR_REG(0xBE); /* GIP 3 */
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x21);
    LCD_WR_DATA(0xAB);
    LCD_WR_DATA(0x60);
    LCD_WR_DATA(0x22);
    LCD_WR_DATA(0x22);
    LCD_WR_DATA(0x22);
    LCD_WR_DATA(0x22);
    LCD_WR_DATA(0x22);

    LCD_WR_REG(0xC7); /* VCOM Control */
    LCD_WR_DATA(0x6F);

    LCD_WR_REG(0xED); /* EN_volt_reg VGMP / VGMN /VGSP / VGSN voltage to output */
    LCD_WR_DATA(0x7F);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x00); 

    LCD_WR_REG(0XC0); /* Power Control 1 Setting AVDD / AVEE / VGH / VGL */
    LCD_WR_DATA(0x37);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x0A);  /* VGH 15V,VGLO-10V */

    LCD_WR_REG(0XFC); /* AVDD / AVEE generated by internal pumping. */
    LCD_WR_DATA(0x0A);

    LCD_WR_REG(0XDF); 
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0XF3); /* DVDD Voltage Setting */
    LCD_WR_DATA(0x74);

    LCD_WR_REG(0xB4); /* Inversion Type */
    LCD_WR_DATA(0x00);  /* 02 */
    LCD_WR_DATA(0x00);  /* 02 */
    LCD_WR_DATA(0x00);  /* 02 */

    LCD_WR_REG(0xF7); /* Resolution Control */
    LCD_WR_DATA(0x82);  /* 480*800 */
    // LCD_WR_DATA(0x89);  // 480x854

    LCD_WR_REG(0xB1); /* FRAME RATE Setting */
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x12);  // LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x13); 

    LCD_WR_REG(0XF2); /* CR_EQ_PC_SDT  #C0,06,40,28 */
    LCD_WR_DATA(0x80);
    LCD_WR_DATA(0x5B);
    LCD_WR_DATA(0x40);
    LCD_WR_DATA(0x28);

    LCD_WR_REG(0XC1); /* Power Control 2  SD OP Bias_VRH1_VRH2_EXT_CPCK_SEL */
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x7D);  /* VGMP */
    LCD_WR_DATA(0x7A);  /* VGMN */
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0xE0); /* Positive Gamma Control */
    LCD_WR_DATA(0x00);  /* P1 */
    LCD_WR_DATA(0x11);  /* P2 */
    LCD_WR_DATA(0x1C);  /* P3 */
    LCD_WR_DATA(0x0E);  /* P4 */
    LCD_WR_DATA(0x0F);  /* P5 */
    LCD_WR_DATA(0x0C);  /* P6 */
    LCD_WR_DATA(0xC7);  /* P7 */
    LCD_WR_DATA(0x06);  /* P8 */
    LCD_WR_DATA(0x06);  /* P9 */
    LCD_WR_DATA(0x0A);  /* P10 */
    LCD_WR_DATA(0x10);  /* P11 */
    LCD_WR_DATA(0x12);  /* P12 */
    LCD_WR_DATA(0x0A);  /* P13 */
    LCD_WR_DATA(0x10);  /* P14 */
    LCD_WR_DATA(0x02);  /* P15 */
    LCD_WR_DATA(0x00);  /* P16 */

    LCD_WR_REG(0xE1); /* Negative Gamma Correction */
    LCD_WR_DATA(0x00);  /* P1 */
    LCD_WR_DATA(0x12);  /* P2 */
    LCD_WR_DATA(0x18);  /* P3 */
    LCD_WR_DATA(0x0C);  /* P4 */
    LCD_WR_DATA(0x0F);  /* P5 */
    LCD_WR_DATA(0x0A);  /* P6 */
    LCD_WR_DATA(0x77);  /* P7 */
    LCD_WR_DATA(0x06);  /* P8 */
    LCD_WR_DATA(0x07);  /* P9 */
    LCD_WR_DATA(0x0A);  /* P10 */
    LCD_WR_DATA(0x0E);  /* P11 */
    LCD_WR_DATA(0x0B);  /* P12 */
    LCD_WR_DATA(0x10);  /* P13 */
    LCD_WR_DATA(0x1D);  /* P14 */
    LCD_WR_DATA(0x17);  /* P15 */
    LCD_WR_DATA(0x00);  /* P16 */



    LCD_WR_REG(0x35); //Tearing Effect ON 
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x3A); /* Pixel Format */
    LCD_WR_DATA(0x55);

    LCD_WR_REG(0x11);
    delay_ms(120);
    LCD_WR_REG(0x29);
	}
    //��ʼ������Ժ�,����
	  if(lcddev.id==0X7796||lcddev.id==0x7789||lcddev.id==0x5310||lcddev.id==0X5510|| lcddev.id == 0X9806)//������⼸��IC,������WRʱ��Ϊ���
    {
        //��������дʱ����ƼĴ�����ʱ��
				FSMC_Bank1E->BWTR[0]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
				FSMC_Bank1E->BWTR[0]&=~(0XF<<8);//���ݱ���ʱ������
				FSMC_Bank1E->BWTR[0]|=3<<0;		//��ַ����ʱ��(ADDSET)Ϊ3��HCLK =18ns 
        if(lcddev.id==0X7789)           //7789��������,��������ͷʵ�����������
        {
            FSMC_Bank1E->BWTR[0]|=4<<8; //���ݱ���ʱ��(DATAST)Ϊ6ns*5��HCLK=30ns
        }
        else
        {
            FSMC_Bank1E->BWTR[0]|=2<<8; //���ݱ���ʱ��(DATAST)Ϊ6ns*3��HCLK=18ns
        }
    } 
	LCD_Display_Dir(0);		//Ĭ��Ϊ����
	LCD_LED=1;				//��������
	LCD_Clear(WHITE);
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width; 
	totalpoint*=lcddev.height; 			//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);			//���ù��λ�� 
	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		if(lcddev.id == 0X7789){		
			LCD->LCD_RAM=color>>8;	
			LCD->LCD_RAM=color;	
		} else
			LCD->LCD_RAM=color;	
	} 
}

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0; 
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		LCD_SetCursor(sx,i);      				//���ù��λ�� 
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
        for (j = 0; j < xlen; j++)
        {
					if(lcddev.id == 0X7789){		LCD->LCD_RAM=color>>8;	
		         LCD->LCD_RAM=color;	}
					else
            LCD->LCD_RAM=color;     //���ù��λ��
        }
    }
}

//��ָ�����������ָ����ɫ��
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j; 
	width=ex-sx+1; 			//�õ����Ŀ���
	height=ey-sy+1;			//�߶�
	for(i=0;i<height;i++)
	{
		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
        for (j = 0; j < width; j++)
        {
					if(lcddev.id == 0X7789){		LCD->LCD_RAM=color[i * width + j]>>8;	
		         LCD->LCD_RAM=color[i * width + j];	}
					else
            LCD->LCD_RAM=color[i * width + j];  //д������
        }
    }
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;              //������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;

    if (delta_x > 0)incx = 1;       //���õ�������
    else if (delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;

    for (t = 0; t <= distance + 1; t++ )    //�������
    {
        LCD_DrawPoint(uRow, uCol); //����
        xerr += delta_x ;
        yerr += delta_y ;

        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

//������
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);       //�ж��¸���λ�õı�־

    while (a <= b)
    {
        LCD_DrawPoint(x0 + a, y0 - b);        //5
        LCD_DrawPoint(x0 + b, y0 - a);        //0
        LCD_DrawPoint(x0 + b, y0 + a);        //4
        LCD_DrawPoint(x0 + a, y0 + b);        //6
        LCD_DrawPoint(x0 - a, y0 + b);        //1
        LCD_DrawPoint(x0 - b, y0 + a);
        LCD_DrawPoint(x0 - a, y0 - b);        //2
        LCD_DrawPoint(x0 - b, y0 - a);        //7
        a++;

        //ʹ��Bresenham�㷨��Բ
        if (di < 0)di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24/32
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else if(size==32)temp=asc2_3216[num][t];	//����3216����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//��������
				break;
			}
		}
	}
}

//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ
//num:��ֵ(0~4294967295);
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size)
{
    u8 t, temp;
    u8 enshow = 0;

    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;

        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + (size / 2)*t, y, ' ', size, 0);
                continue;
            }
            else enshow = 1;

        }

        LCD_ShowChar(x + (size / 2)*t, y, temp + '0', size, 0);
    }
}

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
}

//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p)
{
    u8 x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' '))   //�ж��ǲ��ǷǷ��ַ�!
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)break; //�˳�

        LCD_ShowChar(x, y, *p, size, 0);
        x += size / 2;
        p++;
    }  
}































