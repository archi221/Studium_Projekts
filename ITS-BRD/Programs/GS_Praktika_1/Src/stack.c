#include "display.h"
#include <stdio.h>
#include <fake_sprintf.h>
#include "stack.h"
#include "error_handeling.h"

int stack[STACK_SIZE];
int current_position = 0;

int print_top_value() {
    char buffer[BUFFER_SIZE] = {0};
    if (current_position == 0) {
        return ERROR;
    }
    definitly_not_sprintf(buffer, stack[current_position - 1]);
    printStdout(buffer);
    return SUCCESS;
}

int pop() {
    if (current_position == 0) {
        return ERROR;
    }
    current_position--;
    return SUCCESS;
}

int print_stack() {

    if (current_position == 0) {
        return ERROR;
    }
    printStdout(" stack:");
    for (int i = 0; i < current_position; i++) {
        char buffer[BUFFER_SIZE] = {0};
        definitly_not_sprintf(buffer, stack[i]);
        printStdout(buffer);
    }
    return SUCCESS;
}

int push(int input_number) {
    if (current_position >= STACK_SIZE - 1) {
        return STACK_OVERFLOW;
    }
    stack[current_position] = input_number;
    current_position++;
    return SUCCESS;
}

void delete_stack(void) {
    current_position = 0;
}

int get_value(int *stack_value) {
    if (current_position == 0) {
        return ERROR;
    }
    *stack_value = stack[current_position - 1];
    return SUCCESS;
}