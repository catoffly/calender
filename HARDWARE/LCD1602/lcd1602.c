#include "lcd1602.h"
#include <LPC214X.H>
#include "delay.h"

void LCD_DATA_SET(unsigned char data)
{
	IO1CLR = LCD_DATA;
	IO1SET = data << 16;
}

/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
void LcdWriteCom(unsigned char com)	  //写入命令
{
	LCD_EN_L();    //使能
	LCD_RS_L();	   //选择发送命令
	LCD_RW_L();	   //选择写入
	
	LCD_DATA_SET(com);  //放入命令
	delay_ms(1);		//等待数据稳定

	LCD_EN_H();	      //写入时序
	delay_ms(5);	  //保持时间
	LCD_EN_L();
}
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
void LcdWriteData(unsigned char dat)			//写入数据
{
	LCD_EN_L();	//使能清零
	LCD_RS_H();	//选择输入数据
	LCD_RW_L();	//选择写入

	LCD_DATA_SET(dat); //写入数据
	delay_ms(1);

	LCD_EN_H();   //写入时序
	delay_ms(5);   //保持时间
	LCD_EN_L();
}

void LcdIO_Init(void)
{
	PINSEL2 |= LCD_RS;
	PINSEL2 |= LCD_RW;
	PINSEL2 |= LCD_EN;
	PINSEL2 = 0x00000000;//引脚功能选择为IO口
	
	IO1DIR |= LCD_RS;
	IO1DIR |= LCD_RW;
	IO1DIR |= LCD_EN;
	IO1DIR |= LCD_DATA;//设置相应引脚为输出
	
	LCD_RW_L();	   //选择写入
}

/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
void LcdInit(void)//LCD初始化子程序
{
	LcdIO_Init();
	
 	LcdWriteCom(0x38);  ////8位形式，两行字符。
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
	//LcdWriteCom(0x60);  //设置数据指针起点
	//LcdWriteCom(0xB0);  //设置数据指针起点
}

