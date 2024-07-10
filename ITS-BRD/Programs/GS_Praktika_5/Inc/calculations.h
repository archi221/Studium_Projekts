#ifndef __CALCULATIONS__H__
#define __CALCULATIONS__H__

#include <stdint.h>

#define TO_DEGREE 0.3
#define _360_DEGREES 1200
#define WARTEZEIT 45000000

void add_time();

void add_rotation();

void print(int pulse_count);

void reset_calculations();

uint32_t get_time();

#endif