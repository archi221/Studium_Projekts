#ifndef __SENSOREN__H__
#define __SENSOREN__H__
#include <stdint.h>

typedef struct sensor{
	char sensor[7];
	unsigned char pdrom [8];
	double temperatur;
}__attribute__((__packed__)) sensor;

#endif