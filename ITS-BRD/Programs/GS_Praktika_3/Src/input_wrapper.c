#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <stdint.h>
#include "LCD_wrapper.h"

void (*get_next_line)(RGBTRIPLE *line) = NULL;

static RGBQUAD pallete[256];

static unsigned char amount;
static unsigned char color;

static int width;
static int add_width;
static int height;
static int padding;

static int counter = 0;
static int go_down = 0;

int init_next_picture() {
    BITMAPINFOHEADER infoheader;
    openNextFile();
    if (readHeaders()) {
			return NOK;
		}
    getInfoHeader(&infoheader);

    if (infoheader.biWidth <= LCD_BREITE) {
        width = infoheader.biWidth;
        add_width = 0;
    } else {
        width = LCD_BREITE;
        add_width = (infoheader.biWidth - LCD_BREITE) * (infoheader.biBitCount / 8);
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
						padding -= (infoheader.biWidth); // ein byte pro pixel
        }
    } else if (infoheader.biBitCount == 24) {
				//ERR_HANDLER(1 != COMread((char *) &pallete[0], sizeof(RGBQUAD), 1),
							//"readInfoHeader: Error during pallete read.");
        if (infoheader.biCompression) {
            ERR_HANDLER((true),
                        "biCompression: format not implemented for this formatt");
        } else {
            get_next_line = get_next_line_24;
            padding = (((infoheader.biWidth) * 24 + 31) / 32) * 4;//padding ist ein int
						padding -= (infoheader.biWidth) * 3; // mal 3 bytes
        }
    } else {
        ERR_HANDLER(true, "biBitCount: format not implemented");
    }
	return EOK;
}

void get_next_line_8(RGBTRIPLE *line) {
    unsigned char *buffer = malloc(add_width + padding);
    for (int i = 0; i < height; ++i) {
        get_line(line, width, 0, 0);
        wrap_line(0, i, width, line);
        if (padding + add_width != 0) {
            ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                        "get_next_line: Error during read.");
        }
        free(buffer);
    }
}

void get_line(RGBTRIPLE *line, int anzahl, int ab, int von) {
		amount = 0;
		for (int i = 0; i < anzahl; i++) {
				ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
										"get_next_line: Error during read.");
				if ((i + ab + von) < width) {
						line[i + ab].rgbtBlue = pallete[color].rgbBlue;
						line[i + ab].rgbtGreen = pallete[color].rgbGreen;
						line[i + ab].rgbtRed = pallete[color].rgbRed;
						amount++;
				}
		}
}

void get_next_line_8_pressed(RGBTRIPLE *line) {
	int von = 0;
	int anzahl = 0;
	bool is_end_of_line;
    for (int i = 0; i < height; ++i) {
        if (go_down) {
            go_down--;
            is_end_of_line = true;
        } else {
            is_end_of_line = false;
        }
        while (!is_end_of_line) {
            ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
                        "get_next_line amount: Error during read.");
            ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
                        "get_next_line color: Error during read.");
            if (amount == 0) {
                if (color == 0 || color == 1) {
										call_wrap_line(von, i, anzahl, line);
										is_end_of_line = true;
										counter = 0;
										anzahl = 0;
										von = 0;
                } else if (color == 2) {
										call_wrap_line(von, i, anzahl, line);
                    ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
                                "get_next_line amount: Error during read.");
                    ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
                                "get_next_line color: Error during read.");
                    if (color) {
                        go_down = color;
										}
										von += counter;
										counter = 0;
                   
                } else {
										 // da get line die variable color benutzt
                    get_line(line, color, counter, von);
										counter += amount;
										anzahl += amount;
									if (amount % 2) {
                    ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
                                "get_next_line amount: Error during read.");
									}
                }
            } else {
                for (int j = 0; j < amount; j++) {
										if ((counter + von) < width) {
												line[counter].rgbtBlue = pallete[color].rgbBlue;
												line[counter].rgbtGreen = pallete[color].rgbGreen;
												line[counter].rgbtRed = pallete[color].rgbRed;
												counter++;
												anzahl++;
										}
                }
            }
        }
    }
}

void get_next_line_24(RGBTRIPLE *line) {
    unsigned char *buffer = malloc(add_width + padding);
    for (int j = 0; j < height; j++) {
            ERR_HANDLER(1 != COMread((char *) line, width * sizeof(RGBTRIPLE), 1),
                        "get_next_line: Error during read.");
        if ((padding + add_width) != 0) {
            ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                        "get_next_line: Error during read.");
        }
        wrap_line(0, j, width, line);
    }
    free(buffer);
}

 void call_wrap_line(int von, int höhe, int anzahl, RGBTRIPLE *line) {
		if (von >= width) {
			anzahl = 0;
		}else if ((anzahl + von) > width) {
			anzahl = (width - von);
		}
		if (anzahl) {
				wrap_line(von, höhe, anzahl, line);
		}
}

int get_width() {
    return width;
}

int get_height() {
    return height;
}
