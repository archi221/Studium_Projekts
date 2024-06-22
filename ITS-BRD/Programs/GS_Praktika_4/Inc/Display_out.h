#ifndef __DISPLAY_OUT__H__
#define __DISPLAY_OUT__H__

#include <stdint.h>
#include <stdbool.h>

void init_display();

void print_sensoren(uint64_t *sensoren, int anzahl);

void print_messungen(double *messungen, int anzahl);

#endif