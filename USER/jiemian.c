#include <LPC21xx.H>
#include "lcd1602.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"

#define RTC_NUM  13



int secflag,month,day,hour,min,sec=0,weeks,year,ctemp;
int year1,month1,sec1,day1,hour1,min1;
int timet,datet;
void jie(void)
{
	unsigned char i;
	year1=year;
	nian[0]=year1/1000;
	year1=year1%1000;
	nian[1]=year1/100;
	year1=year1%100;
	nian[2]=year1/10;
	year1=year1%10;
	nian[3]=year1;
	
	month1=month;
	yue[0]=month1/10;
	month1=month1%10;
	yue[1]=month1;
	
	day1=day;
	ri[0]=day1/10;
	day1=day1%10;
	ri[1]=day1;
	
	hour1=hour;
	shi[0]=hour1/10;
	hour1=hour1%10;
	shi[1]=hour1;
	
	min1=min;
	fen[0]=min1/10;
	min1=min1%10;
	fen[1]=min1;
	
	sec1=sec;
	miao[0]=sec1/10;
	sec1=sec1%10;
	miao[1]=sec1;
	
	
	LcdWriteCom(0xc1); //设置坐标在第一行
	for(i=0; i<4; i++)//年
	{
		LcdWriteData(nian[i]+0x30);
	}
	for(i=0; i<2; i++)//年 汉字
	{
		LcdWriteData(hanzi[0][i]);
	}
	for(i=0; i<2; i++)//月
	{
		LcdWriteData(yue[i]+0x30);
	}
	for(i=0; i<2; i++)//月 汉字
	{
		LcdWriteData(hanzi[1][i]);
	}
	for(i=0; i<2; i++)//日
	{
		LcdWriteData(ri[i]+0x30);
	}
	for(i=0; i<2; i++)//月 汉字
	{
		LcdWriteData(hanzi[2][i]);
	}
	LcdWriteCom(0xd3); //设置坐标在第一行
	for(i=0; i<3; i++)//星期
	{
		LcdWriteData(week[week_num][i]);
	}
		LcdWriteCom(0xca);
	for(i=0; i<2; i++)//时
	{
		LcdWriteData(shi[i]+0x30);
	}
	LcdWriteData(jj[1]);
	for(i=0; i<2; i++)//分
	{
		LcdWriteData(fen[i]+0x30);
	}
	LcdWriteData(jj[1]);
	for(i=0; i<2; i++)//miao
	{
		LcdWriteData(miao[i]+0x30);
	}
	
}
void xingqi(void)
{
	int y,c,m,d;//星期 年 世纪 月 日
	int w;
	y=nian[2]*10+nian[3];//年
	m=yue[0]*10+yue[1];//月
	if(m<3)
	{
		y--;
		m+=12;
	}
	c=nian[0]*10+nian[1];//世纪
	d=ri[0]*10+ri[1];
	
	w=y+(y/4)+(c/4)-2*c+(26*(m+1)/10)+d-1;
	week_num=(w%7)-1;
	
}
//void calender_operation(void)//日期推算函数
//{
//	int days,nians;
//	nians=days/1461;//判断有几个四年
//	
//}
void RTC_init(void)
{
   CCR=0X12;
   CIIR=0X01;
   ILR=0X03;
   YEAR=2016;
   MONTH=06;
   DOM=22;
   DOW=2;
   HOUR=18;
   MIN=03;
   SEC=sec;
   CCR=0X11;
   secflag=0;
}
void __irq RTC_int(void)
{
   
   
   sec=SEC;
   min=MIN;
   hour=HOUR;
   weeks=DOW;
   day=DOM;
   month=MONTH;
	 year=YEAR;
   ILR=0X01;
   VICVectAddr=0x00;
   secflag=1;
}
void RTC_int_ini(void)
{
   VICIntSelect&=~(1<<RTC_NUM);
   VICVectCntl2=0x20|RTC_NUM;
   VICVectAddr2=(unsigned int)RTC_int;
   VICIntEnable=(1<<RTC_NUM);
}
