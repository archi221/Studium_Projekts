#include "IO.h"
#include "zeitmessung.h"

static int mode;

void init_IO();

void init_mode(int mode) {
    if (mode == OPEN_DRAIN) {
        LEDS->OTYPER |= (0x01 << 1);
        LEDS->OTYPER &= ~0x01;
        LEDS->BSRR = 0x01;
        mode = OPEN_DRAIN;
    } else if (mode == PUSH_PULL) {
        LEDS->OTYPER &= ~0x01;
        LEDS->OTYPER &= ~(0x01 << 1);
        LEDS->BSRR = 0x01;
        LEDS->BSRR = (0x01 << 1);
        mode = PUSH_PULL;
    }
}

void write_bit(bool bit_value) {
    //error check needet for mode
    LEDS->BSRR = (0x01 << 17);
    sleep(6);
    if (bit_value) {
        LEDS->BSRR = (0x01 << 1);
        sleep(64);
    } else {
        sleep(54)
        LEDS->BSRR = (0x01 << 1);
        sleep(10);
    }
}

int write_reset() {
    //error check needet for mode
    LEDS->BSRR = (0x01 << 1);
    sleep(480);
    LEDS->BSRR = (0x01 << 17);
    sleep(70);
    int slave = (0x01 << 1) != (LEDS->IDR & (0x01 << 1)
    sleep(410);
    return slave;
}

bool read_bit() {
    //error check needet for mode
    LEDS->BSRR = (0x01 << 17);
    sleep(6);
    LEDS->BSRR = (0x01 << 1);
    sleep(9);
    int bit = (0x01 << 1) != (LEDS->IDR & (0x01 << 1);
    sleep(55),
    return bit;
}

void write_bytes(unsigned char *commands, int anzahl);

void read_bytes(unsigned char *bytes, int anzahl);