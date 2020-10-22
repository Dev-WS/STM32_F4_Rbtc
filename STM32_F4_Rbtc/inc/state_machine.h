
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

void state_idle(void);
void state_running(void);
void state_error(void);
void state_stop(void);
void state_check();


typedef void (*state_fun)(void);
typedef uint16_t state_id;

enum{

	IDLE_STATE,
	RUNNING_STATE,
	ERROR_STATE,
	STOP_STATE

};

typedef struct{
	state_id state_t;
	state_fun state_machine_fun;

} state_machine_t;

state_machine_t Machine;


#endif
