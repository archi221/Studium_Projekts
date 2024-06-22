#ifndef __WRITE__H__
#define __WRITE__H__

#include <stdint.h>
#include <stdbool.h>

enum{OPEN_DRAIN, PUSH_PULL};

void init_mode(int mode);

void write_bit();

void write_reset();

void write_bytes(unsigned char *commands, int anzahl);


#endif