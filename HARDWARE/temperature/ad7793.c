#include "ad7793.h"
#include "math.h"

float TC_voltage;
float PT100_temp;

//void RCC_Configuration(void); 

void Delay(vu32 nCount);
void AD7793Reset(void);
void AD7793Write(uint8_t  Data);
uint32_t AD7793Read(void);
uint8_t AD7793Read_Byte(void);
uint8_t Get_AD7793_ID(void);

float tempsssssssss;
uint32_t TESTSSS;

double kTypeVoltage2Temperature(double voltage)
{
  double temp;
  double d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;
  if (voltage < -6.458 || 54.8864 < voltage)
  {
  return (-999);
  }
  else if (-6.458 <= voltage && voltage < -6.45774)
  {
    temp = -270;
  }
  else if (-6.45774 <= voltage && voltage < -5.8914){
    double abs0[70];
    abs0 [0] = -6.45774;
    abs0 [1] = -6.45692;
    abs0 [2] = -6.45592;
    abs0 [3] = -6.45475;
    abs0 [4] = -6.45339;
    abs0 [5] = -6.45183;
    abs0 [6] = -6.45009;
    abs0 [7] = -6.44815;
    abs0 [8] = -6.44600;
    abs0 [9] = -6.44365;
    abs0[10] = -6.44109;
    abs0[11] = -6.43832;
    abs0[12] = -6.43534;
    abs0[13] = -6.43214;
    abs0[14] = -6.42873;
    abs0[15] = -6.42509;
    abs0[16] = -6.42124;
    abs0[17] = -6.41717;
    abs0[18] = -6.41287;
    abs0[19] = -6.40835;
    abs0[20] = -6.40361;
    abs0[21] = -6.39864;
    abs0[22] = -6.39345;
    abs0[23] = -6.38803;
    abs0[24] = -6.38239;
    abs0[25] = -6.37652;
    abs0[26] = -6.37043;
    abs0[27] = -6.36412;
    abs0[28] = -6.35758;
    abs0[29] = -6.35081;
    abs0[30] = -6.34383;
    abs0[31] = -6.33662;
    abs0[32] = -6.32919;
    abs0[33] = -6.32154;
    abs0[34] = -6.31366;
    abs0[35] = -6.30557;
    abs0[36] = -6.29726;
    abs0[37] = -6.28873;
    abs0[38] = -6.27998;
    abs0[39] = -6.27102;
    abs0[40] = -6.26184;
    abs0[41] = -6.25244;
    abs0[42] = -6.24284;
    abs0[43] = -6.23302;
    abs0[44] = -6.22299;
    abs0[45] = -6.21275;
    abs0[46] = -6.20230;
    abs0[47] = -6.19164;
    abs0[48] = -6.18077;
    abs0[49] = -6.16970;
    abs0[50] = -6.15842;
    abs0[51] = -6.14694;
    abs0[52] = -6.13526;
    abs0[53] = -6.12337;
    abs0[54] = -6.11129;
    abs0[55] = -6.09900;
    abs0[56] = -6.08652;
    abs0[57] = -6.07383;
    abs0[58] = -6.06095;
    abs0[59] = -6.04788;
    abs0[60] = -6.03461;
    abs0[61] = -6.02114;
    abs0[62] = -6.00749;
    abs0[63] = -5.99364;
    abs0[64] = -5.97960;
    abs0[65] = -5.96537;
    abs0[66] = -5.95095;
    abs0[67] = -5.93634;
    abs0[68] = -5.92155;
    abs0[69] = -5.90657;
    abs0[70] = -5.89140;

    int i = 0;
    while(voltage>abs0[i]){i++;};
    double a = abs0[i-1];
    double b = abs0[i];
    temp=(-270+i-1)+((voltage - a)/(b - a));        
  }
  // From 500.00 to 00
  else if (-5.8914 <= voltage && voltage < 0)
  {
  d0 = 0;
  d1 = 25.173462;
  d2 = -1.1662878;
  d3 = -1.0833638;
  d4 = -0.8977354;
  d5 = -0.37342377;
  d6 = -0.086632643;
  d7 = -0.010450598;
  d8 = -0.00051920577;
  d9 = 0;
  temp = d0 + d1 * pow(voltage, 1) +
    d2 * pow(voltage, 2) +
    d3 * pow(voltage, 3) +
    d4 * pow(voltage, 4) +
    d5 * pow(voltage, 5) +
    d6 * pow(voltage, 6) +
    d7 * pow(voltage, 7) +
    d8 * pow(voltage, 8) +
    d9 * pow(voltage, 9);
  }
  // From 0 to 500.00
  else if (0 <= voltage && voltage < 20.644)
  {
  d0 = 0;
  d1 = 25.08355;
  d2 = 0.07860106;
  d3 = -0.2503131;
  d4 = 0.0831527;
  d5 = -0.01228034;
  d6 = 0.0009804036;
  d7 = -0.0000441303;
  d8 = 0.000001057734;
  d9 = -0.00000001052755;
  temp = d0 + d1 * pow(voltage, 1) +
    d2 * pow(voltage, 2) +
    d3 * pow(voltage, 3) +
    d4 * pow(voltage, 4) +
    d5 * pow(voltage, 5) +
    d6 * pow(voltage, 6) +
    d7 * pow(voltage, 7) +
    d8 * pow(voltage, 8) +
    d9 * pow(voltage, 9);
  }
  // From 500.00 to 1372.00
  else if (20.644 <= voltage && voltage <= 54.8864)
  {
  d0 = -131.8058;
  d1 = 48.30222;
  d2 = -1.646031;
  d3 = 0.05464731;
  d4 = -0.0009650715;
  d5 = 0.000008802193;
  d6 = -0.0000000311081;

  temp = d0 + d1 * pow(voltage, 1) +
    d2 * pow(voltage, 2) +
    d3 * pow(voltage, 3) +
    d4 * pow(voltage, 4) +
    d5 * pow(voltage, 5) +
    d6 * pow(voltage, 6);
  }
  return(temp);
 }

 double kTypeTemperature2Voltage(double input_temp)
{
  double c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
  double a0, a1, a2, v0, v1;
  double voltage;
  double temp = input_temp;

  if (temp < -270 || 1372 < temp)
  {
  return (-999);
  } else if (-270 <= temp && temp < 0)
  {
  c0 = 0;
  c1 = 0.039450128025;
  c2 = 0.000023622373598;
  c3 = -3.2858906784e-07;
  c4 = -4.9904828777e-09;
  c5 = -6.7509059173e-11;
  c6 = -5.7410327428e-13;
  c7 = -3.1088872894e-15;
  c8 = -1.0451609365e-17;
  c9 = -1.9889266878e-20;
  c10 = -1.6322697486e-23;

  voltage = 1000 * (c0 * pow(temp, 0)+
    c1 * pow(temp, 1) +
    c2 * pow(temp, 2) +
    c3 * pow(temp, 3) +
    c4 * pow(temp, 4) +
    c5 * pow(temp, 5) +
    c6 * pow(temp, 6) +
    c7 * pow(temp, 7) +
    c8 * pow(temp, 8) +
    c9 * pow(temp, 9) +
    c10 * pow(temp, 10));
  }
  else if (0 <= temp && temp <= 1372)
  {
  c0 = -0.017600413686;
  c1 = 0.038921204975;
  c2 = 0.000018558770032;
  c3 = -9.9457592874e-08;
  c4 = 3.1840945719e-10;
  c5 = -5.6072844889e-13;
  c6 = 5.6075059059e-16;
  c7 = -3.2020720003e-19;
  c8 = 9.7151147152e-23;
  c9 = -1.2104721275e-26;
  a0 = 0.1185976;
  a1 = -0.0001183432;
  a2 = 126.9686;

  v0 = (c0 * pow(temp, 0) +
    c1 * pow(temp, 1) +
    c2 * pow(temp, 2) +
    c3 * pow(temp, 3) +
    c4 * pow(temp, 4) +
    c5 * pow(temp, 5) +
    c6 * pow(temp, 6) +
    c7 * pow(temp, 7) +
    c8 * pow(temp, 8) +
    c9 * pow(temp, 9));

  v1 = a0 * exp(a1 * pow(temp - a2, 2));

  voltage = (v0 + v1);
  }
  return (voltage);
}

#if 0
int main(void) 
{ 
  //RCC_Configuration();
  GPIO_Configuration();

  AD7793init();
  AD7793_ID=Get_AD7793_ID();//Read AD7793 ID(0xXB)
  /*
  while(AD7793_DOUT);
  AD7793Write(0x08);//Mode Register
  AD7793Write(0x40);//进入空闲模式
  AD7793Write(0x4F);//
  AD7793Write(0x38);//写对应通道的满量程寄存器的值
  AD7793Write((0x54a300>>16)&0xFF);
  AD7793Write((0x54a300>>8)&0xFF);
  AD7793Write(0x54a300&0xFF);
  */
  /*
  AD7793Write(0x78);//读满刻度校准寄存器的值
  TESTSSS=AD7793Read();
*/
  while (1) 
  {
    AD7793_CS_L;
    AD7793_thermocouple_init();
    Delay(5000);
    TC_voltage = Get_thermocouple_Value();//读取热电动势
    tempsssssssss=TC_voltage*24937.65586+PT100_temp;
    Delay(5000);
    AD7793_GetPT100_init();
    Delay(5000);
    PT100_temp = Get_PT100();//读取PT100温度
    Delay(5000);
  } 
} 
#endif
uint8_t Get_AD7793_ID(void)
{
  uint8_t ID;
  AD7793Write(0x60);//读满刻度校准寄存器的值
  ID=AD7793Read_Byte();
  return ID;
}


float Get_PT100(void)//Return the temp of PT100;
{
  float PT100_TEMP;
  float PT100_R_Value;
  uint32_t DATA_T;
  while(AD7793_DOUT);
  AD7793Write(0x58);
  DATA_T=AD7793Read()-0x800000;
  PT100_TEMP=DATA_T;
  PT100_TEMP/=0x7fffff;
  PT100_R_Value=PT100_TEMP*402;
  PT100_TEMP=(PT100_R_Value-100)/0.385055;//A gruad
  return PT100_TEMP;
}

///return mV
float Get_thermocouple_Value(void)//Return the Voltage of TC;
{
  float Voltage;
  uint32_t DATA_T;
  int32_t DATA_T1;
  while(AD7793_DOUT);
  AD7793Write(0x58);
  DATA_T=AD7793Read();
  DATA_T^=0xFFFFFF;
  DATA_T&=0xffffff;
  DATA_T1=0x7FFFFF-DATA_T;
  Voltage=DATA_T1*1.17; //Vref=1.17V
  Voltage/=0x7fffff;

  Voltage = Voltage*1000;
  Voltage /= 32;//gain = 32
  return Voltage;
}


void AD7793Reset(void)
{
  uint8_t ResetTime;
  ResetTime=50;
  AD7793_SCLK_H;
  AD7793_CS_L;
  AD7793_SDI_H;
  while(ResetTime--)
  {
    AD7793_SCLK_L;
    Delay(200);
    AD7793_SCLK_H;
    Delay(200);
  }
}


void AD7793Write(uint8_t Data)
{
  uint8_t data;
  data=Data;
  AD7793_SCLK_H;
  AD7793_CS_L;
  AD7793_SDI_L;
  for(uint8_t i=0;i<8;i++)
  {
    AD7793_SCLK_L;
    if(data&0x80)
    AD7793_SDI_H;
    else
    AD7793_SDI_L;
    Delay(100);
    AD7793_SCLK_H;
    Delay(100);
    data=data<<1;
  }
  //AD7793_CS_H;
}


uint32_t AD7793Read(void)
{
  uint32_t DATA;
  AD7793_SDI_L;
  AD7793_CS_L;
  AD7793_SCLK_H;
  DATA=0;
  for(uint8_t i=0;i<24;i++)
  {
    DATA<<=1;
    AD7793_SCLK_L;
    Delay(100);
    if(AD7793_DOUT)
    DATA|=0x01;
    AD7793_SCLK_H;
    Delay(100);
  }
  //AD7793_CS_H;
  return DATA;
}


uint8_t AD7793Read_Byte(void)
{
  uint8_t DATA;
  AD7793_SDI_L;
  AD7793_CS_L;
  AD7793_SCLK_H;
  DATA=0;
  for(uint8_t i=0;i<8;i++)
  {
    DATA<<=1;
    AD7793_SCLK_L;
    Delay(100);
    if(AD7793_DOUT)
    DATA|=0x01;
    AD7793_SCLK_H;
    Delay(100);
  }
  //AD7793_CS_H;
  return DATA;
}


void AD7793init(void)
{	
  AD7793Reset();
  Delay(200);
  AD7793Write(0x28);//IO register
  AD7793Write(0x06);//AD7793Write(0x02),
  AD7793Write(0x10);//configuration register
  AD7793Write(0x10);//Gain 1
  AD7793Write(0x10);//external Reference
  
  AD7793Write(0x08);//Mode Register
  AD7793Write(0x80);//内部零刻度校准
  AD7793Write(0x4F);
  Delay(800);
  while(AD7793_DOUT);
  AD7793Write(0x08);//Mode Register
  AD7793Write(0xA0);//内部满量程校准
  AD7793Write(0x4F);//
  Delay(800);
  while(AD7793_DOUT);
}

void AD7793_thermocouple_init(void)
{	
  AD7793Reset();
  Delay(20000);
  AD7793Write(0x28);//IO register
  AD7793Write(0x0A);//Set 420uA Current Source for PT100
  
  AD7793Write(0x10);//configuration register
  AD7793Write(0x45);//Gain =32
  AD7793Write(0x90);//00010000//10010000

  AD7793Write(0x08);//Mode Register
  AD7793Write(0x00);//00000000
  AD7793Write(0x0B);//00001011  12.5Hz DATA OUT
}


void AD7793_GetPT100_init(void)
{	
  AD7793Reset();
  Delay(20000);
  AD7793Write(0x28);//IO register
  AD7793Write(0x0A);//Set 420uA Current Source for PT100

  AD7793Write(0x10);//configuration register
  AD7793Write(0x40);//Gain =1   01000101
  AD7793Write(0x11);//10010000//100100001

  AD7793Write(0x08);//Mode Register
  AD7793Write(0x00);//00000000
  AD7793Write(0x0B);//00001011 12.5Hz DATA OUT
}


void GPIO_Configuration(void) 
{ 
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_initure = {0};
    
    gpio_initure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
	gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
	gpio_initure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE,&gpio_initure); 
    
    gpio_initure.Pin = GPIO_PIN_6;
    gpio_initure.Mode = GPIO_MODE_IT_FALLING;
    gpio_initure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &gpio_initure);
    
} 


void Delay(vu32 nCount) 
{ 
  for(; nCount != 0; nCount--); 
} 
