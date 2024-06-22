#ifndef __SENSOREN__H__
#define __SENSOREN__H__
#include <stdint.h>

typedef struct sensor{
	char typ[7];
	uint64_t pdrom;	
	double temperatur;
}sensor;

#endif