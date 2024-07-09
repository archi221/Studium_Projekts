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
    uint32_t differenz;
    t2 = t1;
    t1 = getTimeStamp();

    if (t1 >= t2) {
        differenz = t1 - t2;
    } else {
        differenz = (UINT32_MAX - t2) + t1;
    }
	return differenz;
}