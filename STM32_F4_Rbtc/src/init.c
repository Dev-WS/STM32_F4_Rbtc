//
//
//#include "init.h"
//#include <string.h>
//
//
//
//extern GPIO_InitTypeDef gpio;
//extern UART_HandleTypeDef uart2;
//
//
//
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
