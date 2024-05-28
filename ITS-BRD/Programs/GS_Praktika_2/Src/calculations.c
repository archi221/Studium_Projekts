#include "calculations.h"
#include "zeitmessung.h"

#include "DisplayOut.h"
#include "calculations.h"

int last_degrees = 0;
int rotations = 0;
double last_calculation = 0; // in sekunden

void check_time(int pulse_count) {
    last_calculation += getZeitspanne();
    if (last_calculation > 45000000) {
        if (pulse_count < 0) {
            pulse_count *= -1;
        }
        double degrees = pulse_count / TO_DEGREE;
        setValues(degrees, (degrees - last_degrees + rotations * _360_DEGREES) * 2);
				last_degrees = degrees;
				rotations = 0;
				last_calculation = 0;
    }
}
void add_rotation() {
    rotations += 1;
}
void minus_rotation() {
    rotations -= 1;
}