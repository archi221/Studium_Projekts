#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <stdint.h>

void (*get_next_line)(RGBTRIPLE *line ) = NULL;

static RGBQUAD pallete[256];

static RGBTRIPLE farbe;

static unsigned char amount;
static unsigned char color;

static bool is_compressed;

static int width;
static int add_width;

static int height;

static int padding;

static int bit_count;

void init_next_picture() {
    BITMAPINFOHEADER infoheader;
    openNextFile();
    readHeaders();
    getInfoHeader(&infoheader);
    bit_count = infoheader.biBitCount;

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
    if (bit_count == 8) {
			if (infoheader.biCompression) {
					get_next_line = get_next_line_8_pressed;
			}else {
					ERR_HANDLER(1 != COMread((char *) pallete, sizeof(RGBQUAD) * infoheader.biBitCount, 1),
											"readInfoHeader: Error during pallete read.");
					get_next_line = get_next_line_8;
					padding = (((infoheader.biWidth) * 8 + 31) / 32) * 4;
			}
    } else if (bit_count == 24) {
				if (infoheader.biCompression) {
			ERR_HANDLER((true),
							"biCompression: format not implemented for this formatt");
			}else {
					get_next_line = get_next_line_24;
				  padding = (((infoheader.biWidth) * 24 + 31) / 32) * 4;
			}
    } else {
        ERR_HANDLER(true, "biBitCount: format not implemented");
    }
}

void get_next_line_8(RGBTRIPLE *line) {
	unsigned char *buffer = malloc((add_width + padding) * bit_count);
	ERR_HANDLER(is_compressed,
							"wrong format for compressed flag in InfoHeader");

	for (int i = 0; i < width; i++) {
		ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
				"get_next_line: Error during read.");
		line[i].rgbtBlue = pallete[color].rgbBlue;
		line[i].rgbtGreen = pallete[color].rgbGreen;
		line[i].rgbtRed = pallete[color].rgbRed;

	}
	ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
						"get_next_line: Error during read.");
	free(buffer);
}

void get_next_line_8_pressed(RGBTRIPLE *line) {
	int counter = 0;
	
	ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
							"get_next_line amount: Error during read.");
	ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
							"get_next_line color: Error during read.");
	while (!(((amount == 0) && (color == 0)) ||
				((amount == 0) && (color == 1)))) {
					
		for (int i = 0; i < amount; i++) {
			if (counter < width){
				line[counter].rgbtBlue = pallete[color].rgbBlue;
				line[counter].rgbtGreen = pallete[color].rgbGreen;
				line[counter].rgbtRed = pallete[color].rgbRed;
			}
			counter++;
		}
		ERR_HANDLER(1 != COMread((char *) &amount, sizeof(unsigned char), 1),
							"get_next_line amount: Error during read.");
		ERR_HANDLER(1 != COMread((char *) &color, sizeof(unsigned char), 1),
							"get_next_line color: Error during read.");
	}
	ERR_HANDLER(counter < width, "get_next_line: Error line to short for header.");
}

void get_next_line_24(RGBTRIPLE *line) {
	    ERR_HANDLER(is_compressed,
                "wrong format for compressed flag in InfoHeader");
   unsigned char *buffer = malloc((add_width + padding) * bit_count);
	//COMread funktioniert wahrscheinlich nur mit struct wegen komprimierung
	for (int i = 0; i < width; i++) {
		ERR_HANDLER(1 != COMread((char *) &farbe, sizeof(RGBTRIPLE), 1),
								"get_next_line: Error during read.");
		line[i] = farbe;
	}

    ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
                "get_next_line: Error during read.");
		free(buffer);  
}

int get_width() {
    return width;
}

int get_height() {
    return height;
}
