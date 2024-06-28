#ifndef __IO__H__
#define __IO__H__

#include <stdint.h>
#include <stdbool.h>

#define LEDS GPIOD
#define NO_SLAVE 1
#define SLAVE 0
#define NOK -1
#define EOK 0

enum{OPEN_DRAIN, PUSH_PULL};

void init_IO();

void init_mode(int mode);

void write_bit(uint8_t bit_value);

int write_byte(uint8_t comand);

int write_reset();

int write_bytes(uint8_t *comand, int anzahl);

bool read_bit();

int read_bytes(unsigned char *bytes, int anzahl);


#endif