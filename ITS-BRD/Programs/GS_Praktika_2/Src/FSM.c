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

int get_first_phase() {
	int phase;
	while (get_phase(&phase)){};
	fsm_state = transition_table[fsm_state][phase];
	functions[fsm_state]();
}

int set_fsm_state() {
	int phase;
	get_phase(&phase);
	fsm_state = transition_table[fsm_state][phase];
	functions[fsm_state]();
}

void error(){
//	error_state();
}

void no_rotation() {
	check_time(pulse_count);
}

void right_rotation() {
	pulse_count++;
    if (pulse_count >= 1400) {
        add_rotation();
        pulse_count = 0;
    } 
	check_time(pulse_count);
	set_all_outputs(pulse_count, true);
}

void left_rotation() {
	pulse_count--;
		if (pulse_count <= -1400) {
			add_rotation();
			pulse_count = 0;
	check_time(pulse_count);
	set_all_outputs(pulse_count, false);
}



	