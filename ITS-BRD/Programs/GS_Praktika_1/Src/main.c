/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf hinzugefuegt
 ******************************************************************************
 */


#include <stdbool.h>
#include "init.h"
#include "display.h"
#include "scanner.h"
#include "token.h"
#include "calc.h"
#include "error_handeling.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */


int main(void) {
    initITSboard();                 // Initialisierung des ITS Boards
    initDisplay();

    int error_code;

    while (true) {
        T_token tastatur_eingabe = nextToken(); //checking the input
        switch (tastatur_eingabe.tok) {

            case NUMBER:
                error_code = push_value(tastatur_eingabe.val);
                break;
            case PLUS:
                error_code = addition();
                break;
            case MINUS:
                error_code = subtraction();
                break;
            case MULT:
                error_code = multiply();
                break;
            case DIV:
                error_code = division();
                break;
            case PRT:
                error_code = print_top_value_calc();
                break;
            case SWAP:
                error_code = swap();
                break;
            case PRT_ALL:
                error_code = print_stack_calc();
                break;
            case CLEAR:
                delete_stack_calc();
                error_code = SUCCESS;
                break;
            case DOUBLE:
                error_code = duplicate_first();
                break;
            case UNEXPECTED:
                error_code = UNEXPECTED_INPUT;
                break;
            case OVERFLOW:
                error_code = OVERFLOW_INPUT;
                break;

        }
        if (error_code) {
            check_error(error_code);
        }
    }
}

// EOF
