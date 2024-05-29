#include "calculations.h"
#include "zeitmessung.h"

#include "DisplayOut.h"
#include "calculations.h"

int last_pulse = 0;
int rotations = 0;
double last_calculation = 0; // in sekunden

void check_time(int pulse_count) {
    last_calculation += getZeitspanne();
    if (last_calculation > WARTEZEIT) {
        if (pulse_count < 0) {
					pulse_count *= -1;
					int degrees = pulse_count * TO_DEGREE;
					setValues(_360_DEGREES - degrees, (pulse_count - last_pulse + rotations * _360_DEGREES) * 2 * TO_DEGREE);
        }else {
					setValues(pulse_count* TO_DEGREE, (pulse_count - last_pulse + rotations * _360_DEGREES) * 2 * TO_DEGREE);
				}
				last_pulse = pulse_count;
				rotations = 0;
				last_calculation = 0;
    }
}
void add_rotation() {
    rotations += 1;
}
