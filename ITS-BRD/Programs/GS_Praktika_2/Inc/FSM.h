#ifndef FSM_H
#define	FSM_H

#define RA 0
#define RB 1
#define RC 2
#define RD 3
#define LD 4
#define LC 5
#define LB 6
#define LA 7
#define ERROR_STATE 8

#include "output.h"
#include "error_handeling.h"

int set_fsm_state();

void error();

void right_rotation();

void left_rotation();

#endif 