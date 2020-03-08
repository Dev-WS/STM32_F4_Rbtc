


#ifndef MAIN_H
#define MAIN_H


#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "init.h"
#include "ssd1306.h"


void SystemConfigClk();

UART_HandleTypeDef uart2;
I2C_HandleTypeDef hi2c1;
GPIO_InitTypeDef gpio;
RCC_OscInitTypeDef osc_init = {0};
RCC_ClkInitTypeDef clk_init = {0};
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_OC_InitTypeDef oc;

#endif
