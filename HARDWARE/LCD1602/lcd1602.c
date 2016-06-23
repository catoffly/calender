#include "lcd1602.h"
#include <LPC214X.H>
#include "delay.h"

void LCD_DATA_SET(unsigned char data)
{
	IO1CLR = LCD_DATA;
	IO1SET = data << 16;
}

/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
void LcdWriteCom(unsigned char com)	  //д������
{
	LCD_EN_L();    //ʹ��
	LCD_RS_L();	   //ѡ��������
	LCD_RW_L();	   //ѡ��д��
	
	LCD_DATA_SET(com);  //��������
	delay_ms(1);		//�ȴ������ȶ�

	LCD_EN_H();	      //д��ʱ��
	delay_ms(5);	  //����ʱ��
	LCD_EN_L();
}
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
void LcdWriteData(unsigned char dat)			//д������
{
	LCD_EN_L();	//ʹ������
	LCD_RS_H();	//ѡ����������
	LCD_RW_L();	//ѡ��д��

	LCD_DATA_SET(dat); //д������
	delay_ms(1);

	LCD_EN_H();   //д��ʱ��
	delay_ms(5);   //����ʱ��
	LCD_EN_L();
}

void LcdIO_Init(void)
{
	PINSEL2 |= LCD_RS;
	PINSEL2 |= LCD_RW;
	PINSEL2 |= LCD_EN;
	PINSEL2 = 0x00000000;//���Ź���ѡ��ΪIO��
	
	IO1DIR |= LCD_RS;
	IO1DIR |= LCD_RW;
	IO1DIR |= LCD_EN;
	IO1DIR |= LCD_DATA;//������Ӧ����Ϊ���
	
	LCD_RW_L();	   //ѡ��д��
}

/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
void LcdInit(void)//LCD��ʼ���ӳ���
{
	LcdIO_Init();
	
 	LcdWriteCom(0x38);  ////8λ��ʽ�������ַ���
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
	//LcdWriteCom(0x60);  //��������ָ�����
	//LcdWriteCom(0xB0);  //��������ָ�����
}

