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

void reset_fsm();

int set_fsm_state();

int error();

int right_rotation();

int left_rotation();

int no_rotation();

int set_fsm_state_while_print();

int error_while_print();

int right_rotation_while_print();

int left_rotation_while_print();

int no_rotation_while_print();

#endif 