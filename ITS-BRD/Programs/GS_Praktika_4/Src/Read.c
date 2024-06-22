#include "Read.h"

bool read_bit();

void read_bytes(unsigned char *bytes, int anzahl);

void read_rom_code(uint64_t *rom_code);

void search_rom_code(uint64_t *rom_codes, int *anzahl_sensoren);

bool check_CRC(unsigned char *bytes, int anzahl_vor_crc);