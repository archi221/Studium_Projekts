#include "FSM.h"

int fsm_state = ERROR;
void (*functions[9])() = {right_rotation, right_rotation, right_rotation, right_rotation,
													left_rotation, left_rotation, left_rotation, left_rotation,
													error};
int transition_table[9][4] = {{RA, RB, ERROR, LD},
															{LA, RB, RC, ERROR},
															{ERROR, LB, RC, RD},
															{RA, ERROR, LC, RD},
															{RA, ERROR, LC, LD},
															{ERROR, LB, LC, RD},
															{LA, LB, RC, ERROR},
															{LA, RB, ERROR, LD},
															{RA, RB, RC, RD}};
int start_fsm() {
	while (set_fsm_state()) {
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


	