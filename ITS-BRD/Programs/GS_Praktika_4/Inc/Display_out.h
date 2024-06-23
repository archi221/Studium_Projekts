#ifndef __DISPLAY_OUT__H__
#define __DISPLAY_OUT__H__

#include <stdint.h>
#include <stdbool.h>
#include "sensoren.h"

void init_display();

void print_sensoren(sensor *sensoren, int anzahl);


#endif