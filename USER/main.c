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
char hanzi[3][3]={"年","月","日"};
char zi[8][7]={"老师好","改变年","改变月","改变日","改变周","改变时","改变分","改变秒"};
unsigned char state_s=0,state_num[2];
 
int FERQ = 500,FERQ1;


void __irq IRQ_Eint3(void)
{  
   
	  delay_ms(10);
		if(IO0PIN&0x100000)	
			state_s++;
		if(state_s>7)
			state_s=0;
		EXTINT = 0x0f;			        // 清除EINT3中断标志，1<<3 等价于 0x08
    VICVectAddr = 0x00;		            // 向量中断结束
}	
void __irq IRQ_Timr0(void)//定时器中断
{
				jie();
//				state_s++;
//				if(state_s>7)
//				state_s=0;
				T0IR = 0x04;     
				VICVectAddr = 0x00;    
}
void eint(void)
{
	PINSEL1 = 3<<8;			            // 设置管脚连接，P0.20设置为EINT3
	VICIntSelect = 0x00000000;	        // 设置所有中断分配为IRQ中断
	VICVectCntl1 = 0x20|17; 
	VICVectAddr1=(unsigned int)IRQ_Eint3;
	EXTMODE = 0x0f; //外部中断3设置为边缘触发
	EXTPOLAR =0x0f; //外部中断3设置为上升沿触发
  EXTINT = 0x0f;					    // 清除EINT3中断标志
  VICIntEnable = 1<<17;		    	// 使能EINT3中断，EINT3在Bit17上
}
void Timer0Init(void)
 {
  //Fcclk=Fosc*5=12*5=60MHz
  ////Fpclk=Fcclk/4=44.2368MHz/4=11.0592MHZ  定时器用的是Pclk
  
  T0PR = 999;     
  T0MCR = 0xc0;    
  T0MR2 = 7500;   
  T0TCR = 0x03;   
  T0TCR = 0x01;    
	VICIntSelect = 0x00000000;   
	VICVectCntl0 = 0x20|4; 
  VICVectAddr0 = (unsigned long)IRQ_Timr0;
  VICIntEnable = 1<<4;       
 }
int main(void)
{
	
	sec=SEC;
	min=MIN;
  hour=HOUR;
	weeks=DOW;
  day=DOM;
  month=MONTH;
	year=YEAR;
	
	LcdInit();
	eint();
	Timer0Init();
	RTC_init();
	RTC_int_ini();
	

	
	
	while(1)
	{			
		xingqi();
		//jie();
		

	}				
}
