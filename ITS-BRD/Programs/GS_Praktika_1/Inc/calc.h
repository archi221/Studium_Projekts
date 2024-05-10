#ifndef CALC_H_
#define CALC_H_

/**
 * @brief Error codes
 *
 */
extern int error_check;

/**
 * @brief  Duplicate the first element of the stack
 * @return error code 0 if no error
 */
int duplicate_first();

/**
 * @brief  Swap the first two elements of the stack
 * @return error code 0 if no error
 */
int swap();

/**
 * @brief  Add the first two elements of the stack and pushes the result on the stack
 * @return error code 0 if no error
 */
int addition();

/**
 * @brief  Subtract the first two elements of the stack and pushes the result on the stack
 * @return error code 0 if no error
 */
int subtraction();

/**
 * @brief  Multiply the first two elements of the stack and pushes the result on the stack
 * @return error code 0 if no error
 */
int multiply();

/**
 * @brief  Divide the first two elements of the stack and pushes the result on the stack
 * @return error code 0 if no error
 */
int division();

/**
 * @brief  Push a value on the stack
 * @param  value: the value to push on the stack
 * @return error code 0 if no error
 */
int push_value(int value);

/**
 * @brief  Print the top value of the stack
 * @return error code 0 if no error
 */
int print_top_value_calc();

/**
 * @brief  Print the whole stack
 * @return error code 0 if no error
 */
int print_stack_calc();

/**
 * @brief  Delete the whole stack
 */
void delete_stack_calc();

#endif