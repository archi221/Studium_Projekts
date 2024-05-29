#include "FSM.h"
#include "output.h"
#include "error_handeling.h"
#include "calculations.h"
#include "DisplayOut.h"

int pulse_count = 0;
int fsm_state = ERROR_STATE;
void (*functions[13])() = {left_rotation, left_rotation, left_rotation, left_rotation,
													right_rotation, right_rotation, right_rotation, right_rotation,
													error,
													no_rotation, no_rotation, no_rotation, no_rotation};

int transition_table[13][4] = {{A, RB, ERROR_STATE, LD},
															{LA, B, RC, ERROR_STATE},
															{ERROR_STATE, LB, NC, RD},
															{RA, ERROR_STATE, LC, D},
															
															{A, RB, ERROR_STATE, LD},
															{LA, B, RC, ERROR_STATE},
															{ERROR_STATE, LB, NC, RD},
															{RA, ERROR_STATE, LC, D},
															
															{A, B, NC, D},
															
															{A, RB, ERROR_STATE, LD},
															{LA, B, RC, ERROR_STATE},
															{ERROR_STATE, LB, NC, RD},
															{RA, ERROR_STATE, LC, D}};

void get_first_phase() {
	int phase;
	while (get_phase(&phase)){
		read_all();
	};
	fsm_state = transition_table[fsm_state][phase];
	functions[fsm_state]();
}

void set_fsm_state() {
	int phase;
	read_all();
	get_phase(&phase);
	fsm_state = transition_table[fsm_state][phase];
	functions[fsm_state]();
}

void error(){
	lcdGotoXY( 0, 3);
	lcdPrintS("Error Press button 6 to Reset");
 while(get_error_input()){}
	 lcdGotoXY( 0, 3);
	 lcdPrintS("                            ");
}

void no_rotation() {
	check_time(pulse_count);
}

void right_rotation() {
	pulse_count++;
	if (pulse_count >= 1200) {
			add_rotation();
			pulse_count = 0;
    } 
	check_time(pulse_count);
	set_all(pulse_count, true);
}

void left_rotation() {
	pulse_count--;
		if (pulse_count <= -1200) {
			add_rotation();
			pulse_count = 0;
	}
	check_time(pulse_count);
	set_all(pulse_count, false);
}