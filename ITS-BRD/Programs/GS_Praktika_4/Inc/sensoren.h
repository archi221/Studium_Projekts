#ifndef __SENSOREN__H__
#define __SENSOREN__H__

#include <stdint.h>

#define SENSOR_RESELUTION 0.0625

typedef struct sensor{
	unsigned char pdrom [8];
	double temperatur;
}sensor;

//__attribute__((__packed__)) 

#endif