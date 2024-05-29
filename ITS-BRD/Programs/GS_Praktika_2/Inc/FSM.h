#ifndef FSM_H
#define	FSM_H

typedef enum FSM {
	RA = 0,
	RB = 1,
	RC = 2,
	RD = 3,
	LA = 4,
	LB = 5,
	LC = 6,
	LD = 7,
	ERROR_STATE = 8,
	A = 9,
	B = 10,
	NC = 11,
	D = 12,
}FSM;


void get_first_phase();

void set_fsm_state();

void error();

void right_rotation();

void left_rotation();

void no_rotation();

#endif 