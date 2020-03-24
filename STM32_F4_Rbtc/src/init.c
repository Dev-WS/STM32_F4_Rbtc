

#include "init.h"
#include <string.h>

extern GPIO_InitTypeDef gpio;
extern UART_HandleTypeDef uart2;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_OC_InitTypeDef oc;



extern duty_H1;
extern duty_H2;

void Error_handler(void)
{
	while(1);
}


void send_string(char* s)
{
	HAL_UART_Transmit(&uart2, (uint8_t*)s, strlen(s), 1000);
}

void receive_string(uint8_t* x){
	HAL_UART_Receive(&uart2, x, sizeof(*x), 1000);
}

void GPIO_Init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);



	 gpio.Pin = GPIO_PIN_2;
	 gpio.Mode =GPIO_MODE_AF_PP;
	 gpio.Pull = GPIO_PULLUP;
	 gpio.Speed = GPIO_SPEED_FREQ_LOW;
	 gpio.Alternate =  GPIO_AF7_USART2; //TX
	 HAL_GPIO_Init(GPIOA,&gpio);

	 gpio.Pin = GPIO_PIN_3; //RX
	 gpio.Mode = GPIO_MODE_AF_OD;
	 HAL_GPIO_Init(GPIOA,&gpio);

	 gpio.Pin = GPIO_PIN_8 |GPIO_PIN_9;
	 gpio.Mode = GPIO_MODE_AF_OD;
	 gpio.Pull = GPIO_NOPULL;
	 gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	 gpio.Alternate = GPIO_AF4_I2C1;
	 HAL_GPIO_Init(GPIOB, &gpio);

	 	 //TIM2
	 gpio.Mode = GPIO_MODE_OUTPUT_PP;
	 gpio.Pin = GPIO_PIN_5;
	 gpio.Pull = GPIO_NOPULL;
	 gpio.Speed = GPIO_SPEED_FREQ_LOW;
	 gpio.Alternate = GPIO_AF1_TIM1;
	 HAL_GPIO_Init(GPIOA, &gpio);

//	 	 //TIM4
	 gpio.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	 gpio.Mode = GPIO_MODE_AF_PP;
	 gpio.Pull = GPIO_NOPULL;
	 gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	 gpio.Alternate = GPIO_AF2_TIM4;
	 HAL_GPIO_Init(GPIOD, &gpio);

}

void UART2_Init()
{
	uart2.Instance = USART2;
	uart2.Init.BaudRate = 115200;
	uart2.Init.WordLength = UART_WORDLENGTH_8B;
	uart2.Init.StopBits = UART_STOPBITS_1;
	uart2.Init.Parity = UART_PARITY_NONE;
	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart2.Init.Mode = UART_MODE_TX_RX;
	 if ( HAL_UART_Init(&uart2) != HAL_OK )
	 {
	 	Error_handler();
	 }

	 HAL_NVIC_EnableIRQ(USART2_IRQn);
	 HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
}

void I2C1_Init()
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 300000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	  {
	    Error_handler();

	  }
}


void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim4);
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&uart2);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
 else
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, duty_H1);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, duty_H1);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, duty_H1);

}

void TIM2_Init()
{
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 10000-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 999;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.RepetitionCounter = 0;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM4_Init()
{
	  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_OC_InitTypeDef sConfigOC = {0};

	 htim4.Instance = TIM4;
	 htim4.Init.Period = 1000 - 1;
	 htim4.Init.Prescaler = 10000 - 1;
	 htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	 htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	 htim4.Init.RepetitionCounter = 0;
	 htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
	  {
	    Error_handler();
	  }
//		HAL_TIM_Base_Start_IT(&htim4);
//		HAL_NVIC_EnableIRQ(TIM4_IRQn);

	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	  {
	    Error_handler();
	  }

	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = 499;
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;

	  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	  {
	    Error_handler();
	  }
	  sConfigOC.Pulse = duty_H1;
	  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	  {
	    Error_handler();
	  }
	  sConfigOC.Pulse = duty_H1;
	  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	  {
	    Error_handler();
	  }
	  sConfigOC.Pulse = 199;
	  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	  {
	    Error_handler();
	  }
	  HAL_NVIC_SetPriority( TIM4_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ( TIM4_IRQn );

	  HAL_TIM_GenerateEvent( &htim4, TIM_EVENTSOURCE_UPDATE );
	  HAL_TIM_GenerateEvent( &htim4, TIM_EVENTSOURCE_CC1 );

}

