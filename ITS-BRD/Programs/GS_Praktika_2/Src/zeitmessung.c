#include "zeitmessung.h"
#include "STM32F4xx.h"
#include "timer.h"
#include "error_handeling.h"
 
 
double zeitspanne;
uint32_t t1;
uint32_t t2;
 
void initZeitmessung(){
initTimer();
}
 
double getZeitstempel(){
	t2 = t1;
  t1 = getTimeStamp();
	return t1;
}
 
double getZeitspanne(){
	 zeitspanne = (t1 - t2) * (1.0/90.0);
   return zeitspanne;
}