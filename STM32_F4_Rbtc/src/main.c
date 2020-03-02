/**
  ******************************************************************************
  * @author  Dev-WS
  * @year    2020
  ******************************************************************************
*/

#include "main.h"


int main(void)
{
	HAL_Init();
	int n = 0;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	uart2_init();

	while(1){

		if (n == 0) send_string("Hello world3343!\r\n");
		else send_string("Hello world 23452!\r\n");
		n++;
		if (n > 1) n = 0;

	}
}
