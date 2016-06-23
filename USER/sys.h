#ifndef _SYS_H_
#define _SYS_H_
extern unsigned char INFO[17] ;
extern unsigned char ferq[5];
extern unsigned char showBuf[5];
extern unsigned char nian[5];
extern unsigned char yue[3];
extern unsigned char	ri[3];
extern unsigned char week[7][4];
extern unsigned char	week_num;
extern unsigned char shi[3];
extern unsigned char fen[3];
extern unsigned char miao[3];
extern unsigned char jj[3];
 extern  char hanzi[3][3];
extern int secflag,month,day,hour,min,sec,weeks,year,ctemp;
extern int month2,day2,hour2,min2,sec2,weeks2,year2;
extern int year1,month1,sec1;
extern int timet,datet,states[2];
extern unsigned char state_s,fanzhuan;
extern char   zi[8][7];
void jie (void);
void xingqi(void);
void RTC_init(void);
void RTC_int_ini(void);

#endif
