#ifndef __IO_WRAPPER__H__
#define __IO_WRAPPER__H__

#include <stdint.h>
#include <stdbool.h>
//prellen muss nicht berücksichtigt werden

// TMEX API TEST BUILD DECLARATIONS
#define TMEXUTIL
//#include "ibtmexcw.h"
long session_handle;
// END TMEX API TEST BUILD DECLARATIONS
// definitions
#define FALSE 0
#define TRUE 1

// method declarations
int OWFirst();

int OWNext();

int OWSearch();

int OWVerify();

void OWTargetSetup(unsigned char family_code);

void OWFamilySkipSetup();

void read_rom_code(uint64_t *rom_code);

void search_rom_code(uint64_t *rom_codes, int *anzahl_sensoren);

bool check_CRC(unsigned char *bytes, int anzahl_vor_crc);

void read_temperature(double *temperatur);

#endif