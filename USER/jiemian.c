#include <LPC21xx.H>
#include "lcd1602.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"






void jie(void)
{
	unsigned char i;
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
