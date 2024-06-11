#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"

static void (*get_next_line)(RGBTRIPLE *line ) = NULL;

static RGBQUAD pallete[256];

static bool is_compressed;

static int width;
static int add_width;

static int height;
static int add_height;

void init_next_picture() {
    BITMAPINFOHEADER infoheader;
    openNextFile();
    readHeaders();
    getInfoHeader(&infoheader);
    if (infoheader.biWidth <= LCD_BREITE) {
        width = infoheader.biWidth;
    } else {
        width = LCD_BREITE;

    }


    height = infoheader.biHeight;
    if (infoheader.biBitCount == 8) {
        get_next_line = get_next_line_8;
        ERR_HANDLER(1 != COMread((char *) pallete, sizeof(pallete), 1),
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

void get_next_line_8(RGBTRIPLE *line) {
    if (is_compressed) {
        decompress_line(line);
    }
}

void get_next_line_24(RGBTRIPLE *line) {
    ERR_HANDLER(is_compressed,
                "wrong format for compressed flag in InfoHeader");
    ERR_HANDLER(1 != COMread((char *) line,width * sizeof(RGBTRIPLE), 1),
                "get_next_line: Error during read.");
    //add adjustmend for padding
}

int get_width() {
    return width;
}

int get_height() {
    return height;
}

void decompress_line(char *line) {

}
