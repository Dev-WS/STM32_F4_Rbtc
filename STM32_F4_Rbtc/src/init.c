

#include "init.h"
#include <string.h>

extern GPIO_InitTypeDef gpio;
extern UART_HandleTypeDef uart2;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_OC_InitTypeDef oc;

void Error_handler(void)
{
	while(1);
}


void GPIO_Init()
{

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

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
	 HAL_GPIO_Init(GPIOA, &gpio);

	 	 //TIM4
	 GPIO_InitTypeDef gpio;
	 gpio.Mode = GPIO_MODE_AF_PP;
	 gpio.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
	 gpio.Pull = GPIO_NOPULL;
	 gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	 HAL_GPIO_Init(GPIOB, &gpio);

}

void UART2_Init()
{
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);

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
	HAL_I2C_Init(&hi2c1);
}


void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
 else
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void TIM2_Init()
{

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 8000-1;
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
	 htim4.Instance = TIM4;
	 htim4.Init.Period = 1000 - 1;
	 htim4.Init.Prescaler = 8000 - 1;
	 htim4.Init.ClockDivision = 0;
	 htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	 htim4.Init.RepetitionCounter = 0;
	 htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	 HAL_TIM_PWM_Init(&htim4);

	 oc.OCMode = TIM_OCMODE_PWM1;
	 oc.Pulse = 100;
	 oc.OCPolarity = TIM_OCPOLARITY_HIGH;
	 oc.OCNPolarity = TIM_OCNPOLARITY_LOW;
	 oc.OCFastMode = TIM_OCFAST_ENABLE;
	 oc.OCIdleState = TIM_OCIDLESTATE_SET;
	 oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	 HAL_TIM_PWM_ConfigChannel(&htim4, &oc, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

//void send_string(char* s)
//{
//	HAL_UART_Transmit(&uart2, (uint8_t*)s, strlen(s), 1000);
//}
//
//void receive_string(uint8_t* x){
//	HAL_UART_Receive(&uart2, x, sizeof(*x), 1000);
//}
