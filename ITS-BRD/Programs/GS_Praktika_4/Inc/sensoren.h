#ifndef __SENSOREN__H__
#define __SENSOREN__H__

#include <stdint.h>

typedef struct sensor{
	unsigned char pdrom [8];
	double temperatur;
}sensor;

//__attribute__((__packed__)) 

#endif