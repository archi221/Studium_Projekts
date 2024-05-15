#include <stack.h>
#include <limits.h>
#include <error_handeling.h>
#include "display.h"

int swap() {
    int value_1, value_2;
    if (pop(&value_1))
        return STACK_UNDERFLOW;

    if (pop(&value_2)) {
        return STACK_UNDERFLOW;
    }

    push(value_1);
    return push(value_2);
}

int duplicate_first() {
    int value_1;
    if (pop(&value_1)) {
        return STACK_UNDERFLOW;// Underflow Stack empty
    }
		push(value_1);
    return push(value_1);
}

int addition() {
    int value_1, value_2;
    if (pop(&value_1)) {
        return STACK_UNDERFLOW;
    }
    if (pop(&value_2)) {
        push(value_1);
        return STACK_UNDERFLOW;
    }
    if (value_2 > 0) {
        if (value_1 > INT_MAX - value_2) {
            return INT_OVERFLOW;
        }
    } else if (value_2 < 0) {
        if (value_1 < INT_MIN - value_2) {
            return INT_OVERFLOW;
        }
    }
    return push(value_1 + value_2);
}

int subtraction() {
    int value_1, value_2;
    if (pop(&value_1)) {
        return STACK_UNDERFLOW;
    }

    if (pop(&value_2)) {
        push(value_1);
        return STACK_UNDERFLOW;
    }
    if (value_1 > 0) {
        if (value_2 < (INT_MIN + value_1)) {
            return INT_OVERFLOW;
        }
    } else if (value_1 < 0) {
        if (value_2 > (INT_MAX + value_1)) {
            return INT_OVERFLOW;
        }
    }
    return push(value_2 - value_1);
}

int multiply() {
    int value_1, value_2;
    if (pop(&value_1)) { //returns 0 when an error accurs
        return STACK_UNDERFLOW;
    }
    if (pop(&value_2)) {//returns 0 when an error accurs
        push(value_1);
        return STACK_UNDERFLOW;
    }
    if ((value_2 == -1 && value_1 == INT_MIN) || (value_1 == -1 && value_2 == INT_MIN)) {
        return INT_OVERFLOW;
    }
		if ((value_2 == -1 && value_1 == INT_MAX) || (value_1 == -1 && value_2 == INT_MAX)){
				return push(value_1 * value_2);
		}
    if (value_2 == 0 || value_1 <= (INT_MAX / value_2) || value_1 == 0 ) {
        return push(value_1 * value_2);
    }
    return INT_OVERFLOW;
}

int division() {
    int divisor, dividend;
    if (pop(&divisor)) {
        return STACK_UNDERFLOW;
    }

    if (pop(&dividend)) {
        push(divisor);
        return STACK_UNDERFLOW;
    }
    // Check for division by zero
    if (divisor == 0) {
        return DIVIDE_BY_ZERO;
    } else if (dividend == INT_MIN && divisor == -1) {
        return INT_OVERFLOW;
    }
    return push(dividend / divisor);
}

int push_value(int value) {
    if (push(value)) {
        return STACK_OVERFLOW;// Overflow Stack full
    }
    return SUCCESS;
}

int print_top_value_calc() {
    print_top_value();
    return SUCCESS;
}

int print_stack_calc() {
    print_stack();
    return SUCCESS;
}

void delete_stack_calc() {
    delete_stack();
    clearStdout();
}
