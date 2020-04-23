#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H


void state_idle();
void state_start();
void state_stop();
void (*state_update)(); //= state_idle;


#endif
