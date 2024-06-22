#include "IO.h"

void init_mode(int mode);

void write_bit();

void write_reset();

void write_bytes(unsigned char *commands, int anzahl);

bool read_bit();

void read_bytes(unsigned char *bytes, int anzahl);