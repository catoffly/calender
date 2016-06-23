#include <LPC21xx.H>
#include "lcd1602.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"

#define LED1 1<<6 //P0.6
#define BEEP 1<<5 //P0.5

#define KEY7 1<<21 //P0.21
#define KEY8 1<<14 //P0.14


typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	�޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		�з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	�޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		�з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	�޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		�з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */

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
char hanzi[3][3]={"��","��","��"};
char zi[8][7]={"��ʦ��","�ı���","�ı���","�ı���","�ı���","�ı�ʱ","�ı��","�ı���"};
unsigned char state_s=0,state_num[2];
 
int FERQ = 500,FERQ1;


void __irq IRQ_Eint3(void)
{  
   
	  delay_ms(10);
		if(IO0PIN&0x100000)	
			state_s++;
		if(state_s>7)
			state_s=0;
		EXTINT = 0x0f;			        // ���EINT3�жϱ�־��1<<3 �ȼ��� 0x08
    VICVectAddr = 0x00;		            // �����жϽ���
}	
void __irq IRQ_Timr0(void)//��ʱ���ж�
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
	PINSEL1 = 3<<8;			            // ���ùܽ����ӣ�P0.20����ΪEINT3
	VICIntSelect = 0x00000000;	        // ���������жϷ���ΪIRQ�ж�
	VICVectCntl1 = 0x20|17; 
	VICVectAddr1=(unsigned int)IRQ_Eint3;
	EXTMODE = 0x0f; //�ⲿ�ж�3����Ϊ��Ե����
	EXTPOLAR =0x0f; //�ⲿ�ж�3����Ϊ�����ش���
  EXTINT = 0x0f;					    // ���EINT3�жϱ�־
  VICIntEnable = 1<<17;		    	// ʹ��EINT3�жϣ�EINT3��Bit17��
}
void Timer0Init(void)
 {
  //Fcclk=Fosc*5=12*5=60MHz
  ////Fpclk=Fcclk/4=44.2368MHz/4=11.0592MHZ  ��ʱ���õ���Pclk
  
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
