#include "IO.h"
#include "zeitmessung.h"
#include "errorhandler.h"
#include "stm32f4xx_hal.h"

static int mode;

void init_IO();

void init_mode(int mode) {
    if (mode == OPEN_DRAIN) {
        LEDS->OTYPER |= (0x01 << 1);
        LEDS->OTYPER &= ~0x01;
        LEDS->BSRR = 0x01;
				LEDS->BSRR = (0x01 << 1);
        mode = OPEN_DRAIN;
    } else if (mode == PUSH_PULL) {
        LEDS->OTYPER &= ~0x01;
        LEDS->OTYPER &= ~(0x01 << 1);
        LEDS->BSRR = 0x01;
        LEDS->BSRR = (0x01 << 1);
        mode = PUSH_PULL;
    }
}

void write_bit(int bit_value) {
    LEDS->BSRR = (0x01 << 17);
    sleep(6);
    if (bit_value) {
        LEDS->BSRR = (0x01 << 1);
        sleep(64);
    } else {
        sleep(54);
        LEDS->BSRR = (0x01 << 1);
        sleep(10);
    };
}

int write_reset() {
    RETURN_NOK_ON_ERR(mode != OPEN_DRAIN, "Write reset: Wrong mode")
    LEDS->BSRR = (0x01 << 17);
    sleep(480);
    LEDS->BSRR = (0x01 << 1);
    sleep(70);
    int slave = (0x01 << 1) != (LEDS->IDR & (0x01 << 1));
    sleep(410);
    return slave;
}

bool read_bit() {
    LEDS->BSRR = (0x01 << 17);
    sleep(6);
    LEDS->BSRR = (0x01 << 1);
    sleep(9);
    int bit = (0x01 << 1) != (LEDS->IDR & (0x01 << 1));
    sleep(55);
    return bit;
}

int write_bytes(unsigned char *commands, int anzahl) {
    RETURN_NOK_ON_ERR(mode != OPEN_DRAIN, "Write bit: Wrong mode")
    for (int i = 0; i < anzahl; ++i) {
        for (int j = 0; j < 8; ++j) {
            write_bit(commands[i] &= (0x1 << j));//da jedes value über null als true gewertet wird
        }
    }
    return EOK;
}

int read_bytes(unsigned char *bytes, int anzahl) {
    RETURN_NOK_ON_ERR(mode != OPEN_DRAIN, "Read bit: Wrong mode")
    for (int i = 0; i < anzahl; ++i) {
        bytes[i] = 0xf;
        for (int j = 0; j < 8; ++j) {
						int r = read_bit();
            bytes[i] |= (r << (7 - j));
        }
    }
    return EOK;
}