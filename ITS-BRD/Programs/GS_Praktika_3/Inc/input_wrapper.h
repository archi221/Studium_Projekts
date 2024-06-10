#ifndef _INPUT_H
#define _INPUT_H

#include "BMP_types.h"

void get_BM_file_header(struct tagBITMAPFILEHEADER *file_header);

void get_BM_info_header(struct tagBITMAPINFOHEADER *info_header);

void get_BT_palette(struct tagRGBQUAD[]);

void get_next_line(char *line);

void decompress_line(char *line);

#endif