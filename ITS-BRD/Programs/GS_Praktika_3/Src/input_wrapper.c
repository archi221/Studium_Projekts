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

int init_next_picture() {
	  int errno = EOK;
    BITMAPINFOHEADER infoheader;
    openNextFile();
    if (readHeaders()) {
			errno = NOK;
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
        int tabbellenlänge = infoheader.biClrUsed == 0 ? 256 : infoheader.biClrUsed;
				ERR_HANDLER(1 != COMread((char *) pallete, tabbellenlänge * sizeof(RGBQUAD), 1),
										"readInfoHeader: Error during pallete read.");
        

        if (infoheader.biCompression) {
            get_next_line = get_next_line_8_pressed;
            padding = 0;
        } else {
            get_next_line = get_next_line_8;
            padding = (((infoheader.biWidth) * 8 + 31) / 32) * 4;
						padding -= (infoheader.biWidth); // ein byte pro pixel
        }
    } else if (infoheader.biBitCount == 24) {
        if (infoheader.biCompression) {
            ERR_HANDLER((true),
                        "biCompression: format not implemented for this formatt");
						errno = NOK;
        } else {
            get_next_line = get_next_line_24;
            padding = (((infoheader.biWidth) * 24 + 31) / 32) * 4;//padding ist ein int
						padding -= (infoheader.biWidth) * _3_BYTES; 
        }
    } else {
        ERR_HANDLER(true, "biBitCount: format not implemented");
				errno = NOK;
    }
	return errno;
}

void get_next_line_8(RGBTRIPLE *line) {
    unsigned char *buffer = malloc(add_width + padding);
    for (int i = 0; i < height; ++i) {
        get_line(line, width);
        wrap_line(0, i, width, line);
        if ((padding + add_width) != 0) {
            ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                        "get_next_line: Error during read.");
        }
    }
	free(buffer);
}

void get_line(RGBTRIPLE *line, int anzahl) {
		for (int i = 0; i < anzahl; i++) {
				ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
										"get_next_line: Error during read.");
				line[counter].rgbtBlue = pallete[color].rgbBlue;
				line[counter].rgbtGreen = pallete[color].rgbGreen;
				line[counter].rgbtRed = pallete[color].rgbRed;
				counter++;
		}
}

void find_end_of_line() {
	bool exit = false;
	while(!exit) {
		ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
								"get_next_line amount: Error during read.");
		ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
								"get_next_line color: Error during read.");
		if (amount == ESCAPE) {
			if ((color == LINE_END) || (color == BITMAP_END)) {
				exit = true;
			}else if (color == DELTA) {
				exit = true;
			}else {
				color = (color % 2) ? color + 1: color;
				unsigned char *buffer =  malloc(color * sizeof(unsigned char));
				ERR_HANDLER(1 != COMread((char *) buffer,color * sizeof(unsigned char), 1),
									"get_next_line color: Error during read.");
				free(buffer);
			}
		}
	}
}

void get_next_line_8_pressed(RGBTRIPLE *line) {
	int von = 0;
	for (int i = 0; i < height; ++i) {
		bool is_end_of_line = false;
			while (!is_end_of_line) {
				
					if ((counter + von) >= width) {
							find_end_of_line();
					}else {
							ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
													"get_next_line amount: Error during read.");
							ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
													"get_next_line color: Error during read.");
				}
					if (amount == ESCAPE) {
						
							if (color == LINE_END || color == BITMAP_END) {
									call_wrap_line(von, i, line);
									is_end_of_line = true;
									von = 0;
									counter = 0;
							} else if (color == DELTA) {
								
									call_wrap_line(von, i, line);
									ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
															"get_next_line amount: Error during read.");
									ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
															"get_next_line color: Error during read.");
									i += color;
									von += counter + amount;
									counter = 0;
								 
							} else {
									
									amount = color;// da get line die variable color benutzt
									get_line(line, color);
									if (amount % 2) {
										ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
																"get_next_line amount: Error during read.");
									}
							}
					} else {
							for (int j = 0; j < amount; j++) {
									line[counter].rgbtBlue = pallete[color].rgbBlue;
									line[counter].rgbtGreen = pallete[color].rgbGreen;
									line[counter].rgbtRed = pallete[color].rgbRed;
									counter++;
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

 void call_wrap_line(int von, int höhe, RGBTRIPLE *line) {
		if (von >= width) {
			counter = 0;
		}else if ((counter + von) > width) {
			counter = (width - von);
		}
		if (counter) {
				wrap_line(von, höhe, counter, line);
		}
}

int get_width() {
    return width;
}

int get_height() {
    return height;
}
