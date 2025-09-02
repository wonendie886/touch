#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	 

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
	write_lcd_reg(0x8000,0x0003);//01--8bit//03--16bit
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

/*
	

	for (int i=0;i < 99;i++)
	{
		if (i % 3 == 0){
			nv3401_fillColor(RED,480*272);
		} else if (i % 3 == 1){
		    nv3401_fillColor(GREEN,480*272);
		} else {
			nv3401_fillColor(BLUE,480*272);
		}
		delay_ms(1000);
	}
	*/
	nv3401_SetWindow(0,0,480-1,272-1);
	nv3401_fillColor(BLACK,480*272);
	
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
    //write_lcd_cmd(0x002C);  // 开始写入显存
    
	// for(uint32_t i = 0; i < pixel_count; i++) {
	// 	write_lcd_data(color);
    // }
	
	NV3401_CS = 0;
	
	NV3401_DC = 1; ///data
	NV3401_RD = 1;
    for(uint32_t i = 0; i < pixel_count; i++) {
		
		NV3401_WR = 0;
		nv3401_set_data(color);
		NV3401_WR = 1;
    }

	NV3401_CS = 1;
	
}
/// @brief LVGL callback function to fill a rectangle with a color
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
	uint16_t height = 0,width = 0;

	width = ex - sx + 1; 			
	height = ey - sy + 1;	

	write_lcd_cmd(0x002A);  // 列地址设置
    write_lcd_data(sx >> 8);
    write_lcd_data(sx & 0xFF);
    write_lcd_data(ex >> 8);
    write_lcd_data(ex & 0xFF);
    
    write_lcd_cmd(0x002B);  // 行地址设置
    write_lcd_data(sy >> 8);
    write_lcd_data(sy & 0xFF);
    write_lcd_data(ey >> 8);
    write_lcd_data(ey & 0xFF);
    
    write_lcd_cmd(0x002C);  // 开始写入显存

	write_lcd_cmd(0x002C);
	NV3401_CS = 0;
	
	NV3401_DC = 1; ///data
	NV3401_RD = 1;
    for(uint32_t i = 0; i < width*height; i++) {
		NV3401_WR = 0;
		nv3401_set_data(color[i]);
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
	uint16_t data = 0;
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

	write_lcd_cmd(0x3a);
	data = read_lcd_data();
	printf("pxl_fmt:0x%x\n",data);

	write_lcd_cmd(0x09);
	for(int i = 0; i < 4; i++){
		data = read_lcd_data();
		printf("state parameter %d:0x%x\n",i,data);
	}

}

































