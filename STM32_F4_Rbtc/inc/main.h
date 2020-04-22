


#ifndef MAIN_H
#define MAIN_H


#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <string.h>
#include <stdio.h>
#include "init.h"
#include "state_machine.h"
#include "ssd1306.h"


void SystemConfigClk();

GPIO_InitTypeDef gpio;
UART_HandleTypeDef uart2;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;


#endif
