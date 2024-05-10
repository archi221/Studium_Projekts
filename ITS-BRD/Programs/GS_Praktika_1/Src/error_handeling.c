#include "display.h"
#include <stdbool.h>
#include "token.h"
#include "scanner.h"
#include "stack.h"
#include "error_handeling.h"

void check_error(int error_code) {
    switch (error_code) {
        case INT_OVERFLOW:
            clearStdout();
            printStdout(INT_OVERFLOW_TEXT);
            break;
        case STACK_UNDERFLOW:
            clearStdout();
            printStdout(STACK_UNDERFLOW_TEXT);
            break;
        case STACK_OVERFLOW:
            clearStdout();
            printStdout(STACK_OVERFLOW_TEXT);
            break;
        case DIVIDE_BY_ZERO:
            clearStdout();
            printStdout(DIVIDE_BY_ZERO_TEXT);
            break;
        case UNEXPECTED_INPUT:
            clearStdout();
            printStdout(UNEXPECTED_INPUT_TEXT);
            break;
        case OVERFLOW_INPUT:
            clearStdout();
            printStdout(OVERFLOW_INPUT_TEXT);
            break;
    }
    while (true) {//waiting for user to input c delete the stack to reset the calculator
        T_token tastatur_eingabe = nextToken();
        if (tastatur_eingabe.tok == CLEAR) {
            delete_stack();
            clearStdout();
            break;
        }
    }
}