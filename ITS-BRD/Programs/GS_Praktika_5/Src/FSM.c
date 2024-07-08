#include "FSM.h"
#include "output.h"
#include "error_handeling.h"
#include "calculations.h"
#include "DisplayOut.h"
#include"zeitmessung.h"

static int pulse_count = 0;
static int fsm_state = ERROR_STATE;
int phase_fsm;

static int (*functions[13])() = 
	
	{right_rotation, right_rotation, right_rotation, right_rotation,
	left_rotation, left_rotation, left_rotation, left_rotation,
	error,
	no_rotation, no_rotation, no_rotation, no_rotation};

static int (*functions_while_print[13])() = 
	
	{right_rotation_while_print, right_rotation_while_print, right_rotation_while_print, right_rotation_while_print,
	left_rotation_while_print, left_rotation_while_print, left_rotation_while_print, left_rotation_while_print,
	error_while_print,
	no_rotation_while_print, no_rotation_while_print, no_rotation_while_print, no_rotation_while_print};
											
static int transition_table[13][4] = 
		//A 	  B   	 C       D
	 {{A, RB, ERROR_STATE, LD,},  //RA  0
		{LA, B, RC, ERROR_STATE,},   //RB  1
		{ERROR_STATE, LB, NC, RD,},  //RC  2
		{RA, ERROR_STATE, LC, D,},   //RD  3
																
		{A, RB, ERROR_STATE, LD,},   //LA  4
		{LA, B, RC, ERROR_STATE,},   //LB  5
		{ERROR_STATE, LB, NC, RD,},  //LC  6
		{RA, ERROR_STATE, LC, D,},   //LD  7
																
		{A, B, NC, D,},              //ERROR_STATE 8
																
		{A, RB, ERROR_STATE, LD,},   //A 9
		{LA, B, RC, ERROR_STATE,},   //B 10
		{ERROR_STATE, LB, NC, RD,},  //NC 11
		{RA, ERROR_STATE, LC, D}};  //D 12
	 
void reset_fsm() {
	pulse_count = 0;
	fsm_state = ERROR_STATE;	
}
		
void get_first_phase() {
	get_phase(&phase_fsm);
	int phase_old = phase_fsm;
	while (phase_old == phase_fsm) {
		read_all();
		getZeitspanne(); //to reset the timer while their is no imput
		get_phase(&phase_fsm);
	}
	fsm_state = transition_table[fsm_state][phase_fsm];
	functions[fsm_state]();
}


int set_fsm_state() {
	read_all();
	get_phase(&phase_fsm);
	fsm_state = transition_table[fsm_state][phase_fsm];
	return functions[fsm_state]();
}

int error(){
	return INVALID_PHASE;
}

int no_rotation() {
	return check_time(pulse_count);
}

int right_rotation() {
	pulse_count++;
	if (pulse_count >= 1200) {
			add_rotation();
			pulse_count = 0;
    } 
	set_all(pulse_count, true);
	return check_time(pulse_count);	
}

int left_rotation() {
	pulse_count--;
		if (pulse_count <= -1200) {
			add_rotation();
			pulse_count = 0;
	}
	set_all(pulse_count, false);
	return check_time(pulse_count);
}

int set_fsm_state_while_print() {
	read_all();
	get_phase(&phase_fsm);
	fsm_state = transition_table[fsm_state][phase_fsm];
		int errno = functions_while_print[fsm_state]();
	if (errno) {
		return INVALID_PHASE;
	}
	return SUCCESS;
}

int no_rotation_while_print() {
	return SUCCESS;
}

int right_rotation_while_print() {
	pulse_count++;
	if (pulse_count >= 1200) {
			add_rotation();
			pulse_count = 0;
    } 
	set_all(pulse_count, true);
	return SUCCESS;	
}

int left_rotation_while_print() {
	pulse_count--;
		if (pulse_count <= -1200) {
			add_rotation();
			pulse_count = 0;
	}
	set_all(pulse_count, false);
	return SUCCESS;
}

int error_while_print(){
	return INVALID_PHASE;
}