#include <LPC21xx.H>
#include "lcd1602.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"






void jie(void)
{
	unsigned char i;
	LcdWriteCom(0xc1); //���������ڵ�һ��
	for(i=0; i<4; i++)//��
	{
		LcdWriteData(nian[i]+0x30);
	}
	for(i=0; i<2; i++)//�� ����
	{
		LcdWriteData(hanzi[0][i]);
	}
	for(i=0; i<2; i++)//��
	{
		LcdWriteData(yue[i]+0x30);
	}
	for(i=0; i<2; i++)//�� ����
	{
		LcdWriteData(hanzi[1][i]);
	}
	for(i=0; i<2; i++)//��
	{
		LcdWriteData(ri[i]+0x30);
	}
	for(i=0; i<2; i++)//�� ����
	{
		LcdWriteData(hanzi[2][i]);
	}
	LcdWriteCom(0xd3); //���������ڵ�һ��
	for(i=0; i<3; i++)//����
	{
		LcdWriteData(week[week_num][i]);
	}
		LcdWriteCom(0xca);
	for(i=0; i<2; i++)//ʱ
	{
		LcdWriteData(shi[i]+0x30);
	}
	LcdWriteData(jj[1]);
	for(i=0; i<2; i++)//��
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
	int y,c,m,d;//���� �� ���� �� ��
	int w;
	y=nian[2]*10+nian[3];//��
	m=yue[0]*10+yue[1];//��
	if(m<3)
	{
		y--;
		m+=12;
	}
	c=nian[0]*10+nian[1];//����
	d=ri[0]*10+ri[1];
	
	w=y+(y/4)+(c/4)-2*c+(26*(m+1)/10)+d-1;
	week_num=(w%7)-1;
	
}
