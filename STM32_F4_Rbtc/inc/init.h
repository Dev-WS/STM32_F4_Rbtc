#ifndef INIT_H
#define INIT_H

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Error_handler(void);
void UART2_Init();
void GPIO_Init();
void I2C1_Init();

//void send_string(char* s);
//void receive_string(uint8_t* x);
//void uart2_init();

#endif
