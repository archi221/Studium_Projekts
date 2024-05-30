#include "FSM.h"
#include "output.h"
#include "error_handeling.h"
#include "calculations.h"
#include "DisplayOut.h"

static int pulse_count = 0;
static int fsm_state = ERROR_STATE;
int phase_fsm;
static void (*functions[13])() = {right_rotation, right_rotation, right_rotation, right_rotation,
																		left_rotation, left_rotation, left_rotation, left_rotation,
																		error,
																		no_rotation, no_rotation, no_rotation, no_rotation};
																			//A 	  B   	 C       D
static int transition_table[13][4] = {{A, RB, ERROR_STATE, LD,},  //RA  0
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

void get_first_phase() {
	while (get_phase(&phase_fsm)){
		read_all();
	};
	fsm_state = transition_table[fsm_state][phase_fsm];
	functions[fsm_state]();
}

void set_fsm_state() {
	read_all();
	get_phase(&phase_fsm);
	fsm_state = transition_table[fsm_state][phase_fsm];
	functions[fsm_state]();
}

void error(){
	lcdGotoXY( 0, 9);
	lcdPrintS("Error Press button 6 to Reset");
 while(get_error_input()){}
	 lcdGotoXY( 0, 9);
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