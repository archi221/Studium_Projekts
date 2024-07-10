#include "calculations.h"
#include "zeitmessung.h"
#include <stdint.h>
#include "DisplayOut.h"
#include "calculations.h"

int last_pulse = 0;
int volatile rotations = 0;
uint32_t volatile time_passed = 0; 

void print(int pulse_count) {
		int rotation_2 = rotations;
		time_passed = 0;
		rotations = 0;
		if (time_passed) {
			time_passed = 0;
			if (rotations) {
				rotation_2++;
			}
			rotations = 0;
		}
		if (pulse_count < 0) {
			pulse_count = pulse_count * -1;
			setValues(360 - (pulse_count * TO_DEGREE), (pulse_count - last_pulse + rotation_2 * _360_DEGREES) * 2 * TO_DEGREE);
		}else {
			setValues(pulse_count * TO_DEGREE, (pulse_count - last_pulse + rotation_2 * _360_DEGREES) * 2 * TO_DEGREE);
		}
		last_pulse = pulse_count;
}

uint32_t get_time() {
	return time_passed;
}

void add_time() {
	  time_passed += getZeitspanne();
}

void add_rotation() {
    rotations += 1;
}

void reset_calculations() {
	last_pulse = 0;
	rotations = 0;
	time_passed = 0;
}