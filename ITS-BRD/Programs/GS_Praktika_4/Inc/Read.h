#ifndef __READ__H__
#define __READ__H__

#include <stdint.h>
#include <stdbool.h>

#define PRELLDAUER 1 //im datenblatt checken
#define ANZAHL_LESEVERSUCH 5

bool read_bit();

void read_bytes(unsigned char *bytes, int anzahl);

void read_rom_code(uint64_t *rom_code);

void search_rom_code(uint64_t *rom_codes, int *anzahl_sensoren);

bool check_CRC(unsigned char *bytes, int anzahl_vor_crc);

#endif