


#ifndef MAIN_H
#define MAIN_H


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "init.h"

void send_string(char* s);
void receive_string(uint8_t* x);
void init();


#endif
