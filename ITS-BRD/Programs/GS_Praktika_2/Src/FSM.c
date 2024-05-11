#include "FSM.h"

int fsm_state = ERROR;
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

//check für get_phase no rotation yet fehlt noch
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

void right_rotation() {
}

void left_rotation() {
}
	