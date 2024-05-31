#include "calculations.h"
#include "zeitmessung.h"
#include <stdint.h>
#include "DisplayOut.h"
#include "calculations.h"

int last_pulse = 0;
int rotations = 0;
uint32_t last_calculation = 0; 

int check_time(int pulse_count) {
		int errno = false;
    last_calculation += getZeitspanne();
    if (last_calculation > WARTEZEIT) {
        if (pulse_count < 0) {
					pulse_count = pulse_count * -1;
					errno = setValues(360 - (pulse_count * TO_DEGREE), (pulse_count - last_pulse + rotations * _360_DEGREES) * 2 * TO_DEGREE);
        }else {
					errno = setValues(pulse_count * TO_DEGREE, (pulse_count - last_pulse + rotations * _360_DEGREES) * 2 * TO_DEGREE);
				}
				last_pulse = pulse_count;
				rotations = 0;
				last_calculation = 0;
    }
		return errno;
}

void add_rotation() {
    rotations += 1;
}

void reset_calculations() {
	last_pulse = 0;
	rotations = 0;
	last_calculation = 0;
}