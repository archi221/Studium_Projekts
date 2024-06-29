#include "zeitmessung.h"
#include "STM32F4xx.h"
#include "timer.h"
#include <stdint.h>
#include <limits.h>

static uint32_t t1;
static uint32_t t2;

void initZeitmessung() {
    initTimer();
    t1 = getTimeStamp();
}

double getZeitspanne() {
    uint32_t differenz;
    t2 = t1;
    t1 = getTimeStamp();

    if (t1 >= t2) {
        differenz = t1 - t2;
    } else {
        differenz = (UINT32_MAX - t2) + t1;
    }
    return (double) differenz / TO_MIKROSECONDS;
}

void sleep(double anzahl_ms) {
    uint32_t time2 = getTimeStamp();
    uint32_t time1;
    double differenz = 0;
    anzahl_ms *= TO_TIMER_INCREMENTS;

    do {
        time1 = getTimeStamp();
        if (time1 >= time2) {
            differenz = time1 - time2;
        } else {
            differenz = (UINT32_MAX - time2) + time1;
        }

    } while (differenz < anzahl_ms);
}