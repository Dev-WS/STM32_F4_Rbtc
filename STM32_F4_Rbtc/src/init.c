

#include "init.h"
#include <string.h>



GPIO_InitTypeDef gpio;
UART_HandleTypeDef uart;



void send_string(char* s)
{
	HAL_UART_Transmit(&uart, (uint8_t*)s, strlen(s), 1000);
}

void receive_string(uint8_t* x){
	HAL_UART_Receive(&uart, x, sizeof(*x), 1000);
}


void uart2_init(){

	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_2;
	gpio.Alternate = GPIO_AF7_USART2;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_AF_OD;
	gpio.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio);

	uart.Instance = USART2;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);
}
