#include <LPC21xx.H>
#include "lcd1602.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"

#define LED1 1<<6 //P0.6
#define BEEP 1<<5 //P0.5

#define KEY7 1<<21 //P0.21
#define KEY8 1<<14 //P0.14


typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */

unsigned char INFO[17] = "KEY1: -  KEY2: +";
unsigned char ferq[5] = "Ferq";
unsigned char showBuf[5];
unsigned char nian[5]={2,0,1,6};
unsigned char yue[3]={0,6};
unsigned char	ri[3]={2,1};
unsigned char week[7][4]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
unsigned char	week_num=0;
unsigned char shi[3]={2,3};
unsigned char fen[3]={5,9};
unsigned char miao[3]={0,0};
unsigned char jj[3]="/:";
unsigned char hanzi[3][3]={"年","月","日"};
 
int FERQ = 500,FERQ1;

void showLCD(void)
{
	unsigned int i;
	
	 
	FERQ1=FERQ;
	showBuf[0]=FERQ1/1000+0x30;
	FERQ1=FERQ1%1000;
	showBuf[1]=FERQ1/100+0x30;
	FERQ1=FERQ1%100;
	showBuf[2]=FERQ1/10+0x30;
	FERQ1=FERQ1%10;
	showBuf[3]=FERQ1+0x30;
	LcdWriteCom(0xC8); //设置坐标在第二行
	for(i=0; i<4; i++)
	{
			//LcdWriteData(showBuf[i]);
	}

}
void __irq IRQ_Eint3(void)
{  
   
	   
		FERQ += 50;
		showLCD();
		if(FERQ > 1000)
		FERQ=100; 
		EXTINT = 0x0f;			        // 清除EINT3中断标志，1<<3 等价于 0x08
    VICVectAddr = 0x00;		            // 向量中断结束
}	
void __irq IRQ_Timr0(void)//定时器中断
{
//				miao[1]++;
//				if(miao[1]==10)
//				{
//					miao[0]++;
//					miao[1]=0;
//				}
//				if(miao[0]==6)
//				{
//					miao[0]=0;
//					fen[1]++;
//				}
//				if(fen[1]==10)
//				{
//					fen[1]=0;
//					fen[0]++;
//				}
//				if(fen[0]==6)
//				{
//					fen[0]=0;
//					shi[1]++;
//				}
//				if(shi[1]==10)
//				{
//					shi[1]=0;
//					shi[0]++;
//				}
//				if(shi[0]==2&&shi[1]==4)
//				{
//					shi[0]=0;
//					shi[1]=0;
//					week_num++;
//					ri[1]++;
//				}
				//jie();
				T0IR = 0x04;     
				VICVectAddr = 0x00;    
}
void eint(void)
{
	PINSEL1 = 3<<8;			            // 设置管脚连接，P0.20设置为EINT3
	VICIntSelect = 0x00000000;	        // 设置所有中断分配为IRQ中断
	VICVectCntl2 = 0x20|17; 
	VICVectAddr2=(unsigned int)IRQ_Eint3;
	EXTMODE = 0x0f; //外部中断3设置为边缘触发
	EXTPOLAR =0x00; //外部中断3设置为上升沿触发
  EXTINT = 0x0f;					    // 清除EINT3中断标志
  VICIntEnable = 1<<17;		    	// 使能EINT3中断，EINT3在Bit17上
}
void Timer0Init(void)
 {
  //Fcclk=Fosc*5=12*5=60MHz
  ////Fpclk=Fcclk/4=44.2368MHz/4=11.0592MHZ  定时器用的是Pclk
  
  T0PR = 999;     
  T0MCR = 0xc0;    
  T0MR2 = 15000;   
  T0TCR = 0x03;   
  T0TCR = 0x01;    
	VICIntSelect = 0x00;   
	VICVectCntl0 = 0x20|4; 
  VICVectAddr0 = (unsigned long)IRQ_Timr0;
  VICIntEnable = 1<<4;       
 }
int main(void)
{
	unsigned char i;
	sec=SEC;
	
	LcdInit();
	eint();
	Timer0Init();
	RTC_init();
	RTC_int_ini();
	
//	LcdWriteCom(0xc1); //设置坐标在第一行
//	for(i=0; i<4; i++)//年
//	{
//		LcdWriteData(nian[i]+0x30);
//	}
//	for(i=0; i<2; i++)//年 汉字
//	{
//		LcdWriteData(hanzi[0][i]);
//	}
//	for(i=0; i<2; i++)//月
//	{
//		LcdWriteData(yue[i]+0x30);
//	}
//	for(i=0; i<2; i++)//月 汉字
//	{
//		LcdWriteData(hanzi[1][i]);
//	}
//	for(i=0; i<2; i++)//日
//	{
//		LcdWriteData(ri[i]+0x30);
//	}
//	for(i=0; i<2; i++)//月 汉字
//	{
//		LcdWriteData(hanzi[2][i]);
//	}
//	LcdWriteCom(0xd3); //设置坐标在第一行
//	for(i=0; i<3; i++)//星期
//	{
//		LcdWriteData(week[2][i]);
//	}
//		LcdWriteCom(0xca);
//	for(i=0; i<2; i++)//时
//	{
//		LcdWriteData(shi[i]+0x30);
//	}
//	LcdWriteData(jj[1]);
//	for(i=0; i<2; i++)//分
//	{
//		LcdWriteData(fen[i]+0x30);
//	}
//	LcdWriteData(jj[1]);
//	for(i=0; i<2; i++)//miao
//	{
//		LcdWriteData(miao[i]+0x30);
//	}
	
	

	//IO0DIR |= LED1;
	//IO0DIR |= BEEP;
	
	
	while(1)
	{			
		xingqi();
		jie();
		
//		IO0CLR = BEEP;
//		IO0SET = LED1;
//		delay_ms(FERQ );
//		IO0SET = BEEP;
//		IO0CLR = LED1;
//		delay_ms(FERQ );
	}				
}
