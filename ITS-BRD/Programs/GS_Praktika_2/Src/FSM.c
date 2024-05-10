#include "FSM.h"

int fms_state = ERROR;
int transition_table[9][4] = {{RA, RB, ERROR, LD},
															{LA, RB, RC, ERROR},
															{ERROR, LB, RC, RD},
															{RA, ERROR, LC, RD},
															{RA, ERROR, LC, LD},
															{ERROR, LB, LC, RD},
															{LA, LB, RC, ERROR},
															{LA, RB, ERROR, LD},
															{RA, RB, RC, RD}};

while (fms_state == transition_table[fms_state][get_phase()]) {
	
}