#ifndef STACK_H_
#define STACK_H_
#define STACK_SIZE 10
#define BUFFER_SIZE 30

/**
 * @brief  Print the top value of the stack
 * @return error code 0 if no error
 */
int print_top_value ();


/**
 * @brief  Push a value on the stack
 * @param  input_number: the value to push on the stack
 * @return error code 0 if no error
 */
int push (int input_number);

/**
 * @brief  Print the whole stack
 * @return error code 0 if no error
 */
int print_stack ();

/**
 * @brief  Delete the whole stack
 * @return error code 0 if no error
 */
void delete_stack ();

/**
 * @brief  Get the top value of the stack and delete it
 * @param  stack_value: pointer to the value
 * @return error code 0 if no error
 */
int pop(int *stack_value);
	
#endif