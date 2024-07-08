#include "zeitmessung.h"
#include "STM32F4xx.h"
#include "timer.h"
#include "error_handeling.h"
#include <stdint.h>
#include <limits.h>
 
double zeitspanne;
uint32_t t1;
uint32_t t2;
 
void initZeitmessung(){
initTimer();
t1 = getTimeStamp();
}
 
double getZeitspanne(){
	t2 = t1;
	t1 = getTimeStamp();
	return t1 - t2;
}