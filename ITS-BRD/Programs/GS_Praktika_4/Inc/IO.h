#ifndef __IO__H__
#define __IO__H__

#include <stdint.h>
#include <stdbool.h>

enum{OPEN_DRAIN, PUSH_PULL};

void init_IO();

void init_mode(int mode);

void write_bit();

void write_reset();

void write_bytes(unsigned char *commands, int anzahl);

bool read_bit();

void read_bytes(unsigned char *bytes, int anzahl);


#endif