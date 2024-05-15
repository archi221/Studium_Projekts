#include "FSM.h"

int pulse_count = 0;
int fsm_state = ERROR_STATE;
void (*functions[13])() = {right_rotation, right_rotation, right_rotation, right_rotation,
													left_rotation, left_rotation, left_rotation, left_rotation,
													error,
													no_rotation, no_rotation, no_rotation, no_rotation};

int transition_table[13][4] = {{A, RB, ERROR_STATE, LD},
															{LA, B, RC, ERROR_STATE},
															{ERROR_STATE, LB, C, RD},
															{RA, ERROR_STATE, LC, D},
															{RA, ERROR_STATE, LC, D},
															{ERROR_STATE, LB, C, RD},
															{LA, B, RC, ERROR_STATE},
															{A, RB, ERROR_STATE, LD},
															{RA, RB, RC, RD},
															{A, RB, ERROR_STATE, LC},
															{LA, B, RB, ERROR_STATE},
															{ERROR_STATE, LB, C, RD},
															{RA, ERROR_STATE, LC, D}};
int start_fsm() {
	while (true) {
		set_fsm_state();
		functions[fsm_state]();
	}
}

//check für get_phase --> no rotation yet fehlt noch
int set_fsm_state() {
	int phase;
	while (true) {
		get_phase(&phase);
		fsm_state = transition_table[fsm_state][phase];
	}
}

void error(){
//	error_state();
}

void no_rotation() {
	check_time(&pulse_count);
}

void right_rotation() {
	pulse_count++;
	check_time(&pulse_count);
//	set_all_outputs();
}

void left_rotation() {
	pulse_count--;
	check_time(&pulse_count);
//	set_all_outputs();
}



	