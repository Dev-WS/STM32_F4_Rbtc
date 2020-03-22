#ifndef INIT_H
#define INIT_H

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Error_handler(void);
void UART2_Init();
void USART2_IRQHandler(void);
void GPIO_Init();
void I2C1_Init();
void TIM2_Init();
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void TIM4_Init();
void send_string(char* s);
void receive_string(uint8_t* x);
//void uart2_init();

#endif
