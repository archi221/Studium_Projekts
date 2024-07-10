#include "FSM.h"
#include "output.h"
#include "error_handeling.h"
#include "calculations.h"
#include "DisplayOut.h"
#include "zeitmessung.h"

static volatile int pulse_count = 0;
static volatile int fsm_state = ERROR_STATE;
static volatile int phase_fsm;
static volatile int direction = 0;
extern volatile int errno;

static void (*functions[13])() = 
	
	{right_rotation, right_rotation, right_rotation, right_rotation,
	left_rotation, left_rotation, left_rotation, left_rotation,
	error,
	no_rotation, no_rotation, no_rotation, no_rotation};
											
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

int get_dircetion(){
	return direction;
}

int get_pulse_count() {
	return pulse_count;
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
}


void set_fsm_state() {
	add_time();
	//testing(get_time());
	read_all();
	get_phase(&phase_fsm);
	fsm_state = transition_table[fsm_state][phase_fsm];
	functions[fsm_state]();
}

void no_rotation() {
}

void right_rotation() {
	pulse_count++;
	if (pulse_count >= 1200) {
			add_rotation();
			pulse_count = 0;
    }
	direction = 1;
}

void left_rotation() {
	pulse_count--;
		if (pulse_count <= -1200) {
			add_rotation();
			pulse_count = 0;
	}
	direction = 0;
}

void error(){
	errno = 1;
}