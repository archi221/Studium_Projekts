#ifndef __IO_WRAPPER__H__
#define __IO_WRAPPER__H__

#include <stdint.h>
#include <stdbool.h>
//prellen muss nicht berücksichtigt werden


void read_rom_code(uint64_t *rom_code);

void search_rom_code(uint64_t *rom_codes, int *anzahl_sensoren);

bool check_CRC(unsigned char *bytes, int anzahl_vor_crc);

#endif