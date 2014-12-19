
#include "timer.h"

//udelay(33000); /* 33 ms: the maximum delay of udelay() */
void mdelay(unsigned int msec) {
	unsigned int i = 0;
	for(i = 0; i<msec; i++)
		udelay(1000); /* 1 ms */
}
