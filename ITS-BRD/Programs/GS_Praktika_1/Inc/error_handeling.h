#ifndef ERROR_HANDELING_H_
#define ERROR_HANDELING_H_
#define INT_OVERFLOW -92
#define INT_OVERFLOW_TEXT "Overflow: the result is to long! Press c to continue"
#define STACK_UNDERFLOW -11
#define STACK_UNDERFLOW_TEXT "Stack Underflow: not enough numbers on the Stack! Press c to continue"
#define STACK_OVERFLOW -15
#define STACK_OVERFLOW_TEXT "Stack Overflow: the stack is full! Press c to continue"
#define DIVIDE_BY_ZERO -85
#define DIVIDE_BY_ZERO_TEXT "Divide by zero: you cant divide by zero! Press c to continue"
#define UNEXPECTED_INPUT -44
#define UNEXPECTED_INPUT_TEXT "Unexpected: unexpected input! Press c to continue"
#define OVERFLOW_INPUT -55
#define OVERFLOW_INPUT_TEXT "Overflow: your input number is to long! Press c to continue"
#define SUCCESS 0
#define ERROR -1


/**
 * @brief prints what error occurred and waits for the user to delete the stack
 * @param the error code
 */
void check_error(int error_code);

#endif