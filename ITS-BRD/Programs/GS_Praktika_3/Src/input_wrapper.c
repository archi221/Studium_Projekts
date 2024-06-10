#include "input_wrapper.h"
#include <stdio.h>
#include <stdbool.h>
#include "errorhandler.h"
#include "input.h"

void get_BM_file_header() {
    openNextFile();
    ERR_HANDLER(true != COMread((char *) &BITMAPINFOHEADER,
                                sizeof(BITMAPFILEHEADER), 1),
                "readFileHeaders: Error during read.");
    ERR_HANDLER(fileHeader != NULL, "readFileHeaders: Nullpointer");
}

void get_BM_info_header() {
    ERR_HANDLER(true != COMread((char *) &BITMAPFILEHEADER,
                                sizeof(BITMAPINFOHEADER), 1),
                "readInfoHeader: Error during read.");
    ERR_HANDLER(info_header != NULL, "readInfoHeader: Nullpointer");
    ERR_HANDLER(&BITMAPFILEHEADER->bfOffBits == sizeof(file_header) + sizeof(info_header),
                "readInfoHeader: wrong offsett");
}

void get_BT_palette(struct tagRGBQUAD palette[]) {
    ERR_HANDLER(true != COMread((char *) palette,
                                sizeof(RGBQUAD) * 266, 1),
                "readInfoHeader: Error during read.");
}

void get_next_line_8compressed(char *line, bool compressed) {
    if (compressed) {
        decompress_line(line)
    }
}

void get_next_line_24compressed(char *line, bool compressed) {
    ERR_HANDLER(compressed, "wrong format for compressed flag in InfoHeader")
}

void decompress_line(char *line) {

}
