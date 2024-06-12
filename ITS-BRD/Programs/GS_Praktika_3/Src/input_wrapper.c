#include "input_wrapper.h"
#include "headers.h"
#include "errorhandler.h"
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <stdint.h>

void (*get_next_line)(RGBTRIPLE *line ) = NULL;

static RGBQUAD pallete[256];

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
	unsigned char *pt_pallete = malloc(sizeof(unsigned char) * width);
	ERR_HANDLER(is_compressed,
							"wrong format for compressed flag in InfoHeader");
	ERR_HANDLER(1 != COMread((char *) pt_pallete, width * sizeof(unsigned char), 1),
							"get_next_line: Error during read.");
	ERR_HANDLER(1 != COMread((char *) buffer, padding + add_width, 1),
							"get_next_line: Error during read.");
	for (int i = 0; i < width; i++) {
		line[i].rgbtBlue = pallete[pt_pallete[i]].rgbBlue;
		line[i].rgbtGreen = pallete[pt_pallete[i]].rgbGreen;
		line[i].rgbtRed = pallete[pt_pallete[i]].rgbRed;
	}
	free(buffer);
	free(pt_pallete);
}

void get_next_line_8_pressed(RGBTRIPLE *line) {
	unsigned char *pressed_pixel = malloc(2 * sizeof(uint8_t));
	int counter = 0;
	ERR_HANDLER(1 != COMread((char *) &pressed_pixel, 2 * sizeof(unsigned char), 1),
							"get_next_line: Error during read.");
	while (((pressed_pixel[0] + pressed_pixel[1]) != 0) ||
				(pressed_pixel[0] + pressed_pixel[1]) != 1) {
					counter = pressed_pixel[0] + pressed_pixel[1];
		for (int i = 0; i < pressed_pixel[0]; i++) {
			if (counter < width){
				line[counter].rgbtBlue = pallete[pressed_pixel[1]].rgbBlue;
				line[counter].rgbtGreen = pallete[pressed_pixel[1]].rgbGreen;
				line[counter].rgbtRed = pallete[pressed_pixel[1]].rgbRed;
			}
			counter++;
		}
			ERR_HANDLER(1 != COMread((char *) &pressed_pixel, 2 * sizeof(unsigned char), 1),
									"get_next_line: Error during read.");
	}
	ERR_HANDLER(counter < width, "get_next_line: Error line to short for header.");
	free(pressed_pixel);
}

void get_next_line_24(RGBTRIPLE *line) {
    unsigned char *buffer = malloc((add_width + padding) * bit_count);
    ERR_HANDLER(is_compressed,
                "wrong format for compressed flag in InfoHeader");
    ERR_HANDLER(1 != COMread((char *) line, width * sizeof(RGBTRIPLE), 1),
                "get_next_line: Error during read.");
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
