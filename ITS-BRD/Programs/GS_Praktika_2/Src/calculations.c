#include "calculations.h"
#include "zeitmessung.h"

int rotations = 0;
double last_calculation = 0; // in sekunden

int check_time(int pulse_count) {
    last_calculation += getZeitspanne();
    if (last_calculation > 0.25) {
        if (pulse_count < 0) {
            pulse_count *= -1;
        }
        double degrees = pulse_count / TO_DEGREE;
        setValues(degrees, (winkel + (rotations * _360_DEGREES)) / last_calculation);
        rotations = 0;
    }
}
void add_rotation() {
    rotations += 1;
}
void minus_rotation() {
    rotation -= 1;
}