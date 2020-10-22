
//#include "state_machine.h"
#include "main.h"


void state_idle(){

};
void state_start(){

};
void state_stop(){

};

const state_machine_t state_machine[] = {
		{IDLE_STATE, &state_idle},
		{RUNNING_STATE, &state_running},
		{ERROR_STATE, &state_error},
		{STOP_STATE, &state_stop}
};


void state_check(){

	state_machine[Machine.state_t].state_machine_fun();

}


