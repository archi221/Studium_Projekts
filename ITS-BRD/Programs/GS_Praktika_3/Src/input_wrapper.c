#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <stdint.h>

void (*get_next_line)(RGBTRIPLE *line) = NULL;

static RGBQUAD pallete[256];

static RGBTRIPLE farbe;

static unsigned char amount;
static unsigned char color;

static bool is_compressed;

static int width;
static int add_width;
static int height;
static int padding;

static int counter = 0;
static int go_down = 0;

void init_next_picture() {
    BITMAPINFOHEADER infoheader;
    openNextFile();
    readHeaders();
    getInfoHeader(&infoheader);

    if (infoheader.biWidth <= LCD_BREITE) {
        width = infoheader.biWidth;
        add_width = 0;
    } else {
        width = LCD_BREITE;
        add_width = infoheader.biWidth - LCD_BREITE;
    }

    if (infoheader.biHeight <= LCD_HÖHE) {
        height = infoheader.biHeight;
    } else {
        height = LCD_HÖHE;
    }

    ERR_HANDLER((0 != infoheader.biCompression) && (infoheader.biCompression != 1),
                "biCompression: format not implemented");

    if (infoheader.biBitCount == 8) {
        //for schleife einfügen
        int tabbellenlänge = infoheader.biClrUsed == 0 ? 256 : infoheader.biClrUsed;
        for (int i = 0; i < tabbellenlänge; i++) {
            ERR_HANDLER(1 != COMread((char *) &pallete[i], sizeof(RGBQUAD), 1),
                        "readInfoHeader: Error during pallete read.");
        }

        if (infoheader.biCompression) {
            get_next_line = get_next_line_8_pressed;
            padding = 0;
        } else {
            get_next_line = get_next_line_8;
            padding = (((infoheader.biWidth) * 8 + 31) / 32) * 4;
        }
    } else if (infoheader.biBitCount == 24) {
        if (infoheader.biCompression) {
            ERR_HANDLER((true),
                        "biCompression: format not implemented for this formatt");
        } else {
            get_next_line = get_next_line_24;
            padding = (((infoheader.biWidth) * 24 + 31) / 32) * 4;
        }
    } else {
        ERR_HANDLER(true, "biBitCount: format not implemented");
    }
}

void get_next_line_8(RGBTRIPLE *line) {
    unsigned char *buffer = malloc((add_width + padding) * 8);
    for (int i = 0; i < height; ++i) {
        get_line(line, width, 0);
        wrap_line(0, i, width, line);
        if (padding + add_width != 0) {
            ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                        "get_next_line: Error during read.");
        }
        free(buffer);
    }

    void get_line(RGBTRIPLE *line, int anzahl, int ab) {
        for (int i = 0; i < anzahl; i++) {
            ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
                        "get_next_line: Error during read.");
            line[i + ab].rgbtBlue = pallete[color].rgbBlue;
            line[i + ab].rgbtGreen = pallete[color].rgbGreen;
            line[i + ab].rgbtRed = pallete[color].rgbRed;

        }

    }
}

void get_next_line_8_pressed(RGBTRIPLE *line) {
    for (int i = 0; i < height; ++i) {
        if (go_down) {
            go_down--;
            bool is_end_of_line = true;
        } else {
            bool is_end_of_line = false;
        }
        while (!is_end_of_line) {
            ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
                        "get_next_line amount: Error during read.");
            ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
                        "get_next_line color: Error during read.");
            if (amount == 0) {
                if (color == 0 || color == 1) {
                    is_end_of_line = true;
                    counter = 0;
                } else if (color == 2) {
                    ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
                                "get_next_line amount: Error during read.");
                    ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
                                "get_next_line color: Error during read.");
                    if (color) {
                        go_down = color;
                        counter = amount;
                    } else {
                        counter += amount;
                    }
                } else {
                    get_line(line, amount, counter);
                    wrap_line(counter, i, amount, line);
                    counter += amount;
                }

            } else {
                for (int i = 0; i < amount; i++) {
                    if (counter < width) {
                        line[counter].rgbtBlue = pallete[color].rgbBlue;
                        line[counter].rgbtGreen = pallete[color].rgbGreen;
                        line[counter].rgbtRed = pallete[color].rgbRed;
                        counter++;
                    }
                }
                wrap_line(counter - amount, i, amount, line);
            }
        }
    }
    char buffer[60];
    sprintf(buffer, "get_next_line: counter: %d width: %d hight: %d ", counter, width, height);
    ERR_HANDLER(counter < width, buffer);
}

void get_next_line_24(RGBTRIPLE *line) {
    ERR_HANDLER(is_compressed,
                "wrong format for compressed flag in InfoHeader")
    ";
    unsigned char *buffer = malloc((add_width + padding) * 24);
    for (int j = 0; j < height, j++) {
        for (int i = 0; i < width; i++) {
            ERR_HANDLER(1 != COMread((char *) &farbe, sizeof(RGBTRIPLE), 1),
                        "get_next_line: Error during read.");
            line[i] = farbe;
        }
        if (padding + add_width != 0) {
            ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                        "get_next_line: Error during read.");
        }
        wrap_line(0, j, width, line);
    }
    free(buffer);
}

int get_width() {
    return width;
}

int get_height() {
    return height;
}
