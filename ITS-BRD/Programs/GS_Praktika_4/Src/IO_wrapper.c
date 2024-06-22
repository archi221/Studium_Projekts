#include "IO_wrapper.h"


void read_rom_code(uint64_t *rom_code);

void search_rom_code(uint64_t *rom_codes, int *anzahl_sensoren);

bool check_CRC(unsigned char *bytes, int anzahl_vor_crc);