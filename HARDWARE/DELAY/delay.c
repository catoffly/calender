#include "delay.h"

void delay_ms(unsigned int ms)
{
    unsigned int b;
	
    for(;ms>0;ms--)
		for(b=11998;b>0;b--);
}
