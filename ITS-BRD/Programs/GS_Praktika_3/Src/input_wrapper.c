#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"

static void (*get_next_line)(char *a, bool is_compressed) = NULL;

static RGBQUAD[256] pallete;

static bool is_compressed;

static int width;

void init_next_picture() {
    BITMAPINFOHEADER infoheader;
    openNextFile();
    readHeaders();
    getInfoHeader(&infoheader)
    infoheader.biWidth = width;
    if (infoheader.biBitCount == 8) {
        get_next_line = get_next_line_8;
        ERR_HANDLER(1 != COMread((char *) palette, sizeof(pallete) , 1),
                    "readInfoHeader: Error during read.");
    } else if (infoheader.biBitCount == 24) {
        get_next_line = get_next_line_24;
    } else {
        ERR_HANDLER(true, "biBitCount: format not implemented");
    }
    ERR_HANDLER(0 < infoheader.biCompression > 1,
                "biCompression: format not implemented");
    is_compressed = infoheader.biCompression ? true : false;
}

void get_next_line_8(char *line, bool compressed) {
    if (is_compressed) {
        decompress_line(line);
    }
}

void get_next_line_24(char *line, bool is_compressed) {
    ERR_HANDLER(is_compressed, "wrong format for compressed flag in InfoHeader");
    
}

void decompress_line(char *line) {

}
