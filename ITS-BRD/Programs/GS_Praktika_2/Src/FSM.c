#include "FSM.h"

int fsm_state = ERROR_STATE;
void (*functions[9])() = {right_rotation, right_rotation, right_rotation, right_rotation,
													left_rotation, left_rotation, left_rotation, left_rotation,
													error};
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
		if (fsm_state != transition_table[fsm_state][phase]) {
			fsm_state = transition_table[fsm_state][phase];
			return SUCCESS;
		}
	}
}

void error(){
//	error_state();
}

void err_to_l_rotation() {
	
}

void err_to_r_rotation() {
}

void right_rotation() {
}

void left_rotation() {
}

void r_to_l_rotation() {
}

void l_to_r_rotation() {
}


	