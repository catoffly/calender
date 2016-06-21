#ifndef _LCD1602_H_
#define _LCD1602_H_

#define LCD_RS 1<<24
#define LCD_RW 1<<25
#define LCD_EN 1<<26
#define LCD_DATA 0x00FF0000;

#define LCD_RS_H() IO1SET = LCD_RS;
#define LCD_RS_L() IO1CLR = LCD_RS;

#define LCD_RW_H() IO1SET = LCD_RW;
#define LCD_RW_L() IO1CLR = LCD_RW;

#define LCD_EN_H() IO1SET = LCD_EN;
#define LCD_EN_L() IO1CLR = LCD_EN;

extern void LcdInit(void);//LCD初始化子程序
extern void LcdWriteData(unsigned char dat);			//写入数据
extern void LcdWriteCom(unsigned char com);	  //写入命令


#endif
