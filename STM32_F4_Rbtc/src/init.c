

#include "init.h"
#include <string.h>

extern GPIO_InitTypeDef gpio;
extern UART_HandleTypeDef uart2;
extern I2C_HandleTypeDef hi2c1;

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

//void send_string(char* s)
//{
//	HAL_UART_Transmit(&uart2, (uint8_t*)s, strlen(s), 1000);
//}
//
//void receive_string(uint8_t* x){
//	HAL_UART_Receive(&uart2, x, sizeof(*x), 1000);
//}
//
//
//void uart2_init(){
//
//	gpio.Mode = GPIO_MODE_AF_PP;
//	gpio.Pin = GPIO_PIN_2;
//	gpio.Alternate = GPIO_AF7_USART2;
//	gpio.Pull = GPIO_NOPULL;
//	gpio.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOA, &gpio);
//
//	gpio.Mode = GPIO_MODE_AF_OD;
//	gpio.Pin = GPIO_PIN_3;
//	HAL_GPIO_Init(GPIOA, &gpio);
//
//	uart2.Instance = USART2;
//	uart2.Init.BaudRate = 115200;
//	uart2.Init.WordLength = UART_WORDLENGTH_8B;
//	uart2.Init.Parity = UART_PARITY_NONE;
//	uart2.Init.StopBits = UART_STOPBITS_1;
//	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	uart2.Init.OverSampling = UART_OVERSAMPLING_16;
//	uart2.Init.Mode = UART_MODE_TX_RX;
//	HAL_UART_Init(&uart2);
//}
