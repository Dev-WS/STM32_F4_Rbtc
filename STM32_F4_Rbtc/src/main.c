/**
  ******************************************************************************
  * @author  Dev-WS
  * @year    2020
  ******************************************************************************
*/

#include <string.h>
#include "stm32f4xx_hal.h"
#include "main.h"

#define TRUE 1
#define FALSE 0


void Error_handler(void);
void UART2_GPIO_Init();
void SystemConfigClk();

UART_HandleTypeDef huart2;
GPIO_InitTypeDef gpio_uart2;
RCC_OscInitTypeDef osc_init = {0};
RCC_ClkInitTypeDef clk_init = {0};

int main(void)
{
	char msg[100];

	HAL_Init();
	SystemConfigClk();
    UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %ldHz\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK   : %ldHz\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK1  : %ldHz\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK2  : %ldHz\r\n\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	while(1);


	return 0;
}

void UART2_Init()
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	 gpio_uart2.Pin = GPIO_PIN_2;
	 gpio_uart2.Mode =GPIO_MODE_AF_PP;
	 gpio_uart2.Pull = GPIO_PULLUP;
	 gpio_uart2.Speed = GPIO_SPEED_FREQ_LOW;
	 gpio_uart2.Alternate =  GPIO_AF7_USART2; //TX
	 HAL_GPIO_Init(GPIOA,&gpio_uart2);

	 gpio_uart2.Pin = GPIO_PIN_3; //RX
	 gpio_uart2.Mode = GPIO_MODE_AF_OD;
	 HAL_GPIO_Init(GPIOA,&gpio_uart2);

	 HAL_NVIC_EnableIRQ(USART2_IRQn);
	 HAL_NVIC_SetPriority(USART2_IRQn,15,0);


	 huart2.Instance = USART2;
	 huart2.Init.BaudRate = 115200;
	 huart2.Init.WordLength = UART_WORDLENGTH_8B;
	 huart2.Init.StopBits = UART_STOPBITS_1;
	 huart2.Init.Parity = UART_PARITY_NONE;
	 huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 huart2.Init.Mode = UART_MODE_TX_RX;
	 if ( HAL_UART_Init(&huart2) != HAL_OK )
	 {
	 	Error_handler();
	 }


}


void SystemConfigClk()
{
	memset(&osc_init,0,sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc_init.HSEState = RCC_HSE_BYPASS;

    //osc_init.HSEState = RCC_HSE_ON;
    if ( HAL_RCC_OscConfig(&osc_init) != HAL_OK)
    {
    	Error_handler();
    }


    osc_init.PLL.PLLState = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;


    // SYS_CLOCK PLL
	osc_init.PLL.PLLM = 8;
	osc_init.PLL.PLLN = 50;
	osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	osc_init.PLL.PLLQ = 2;

    clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
    					RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    //clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
    clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    if( HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS) != HAL_OK)
    {
    	Error_handler();
    }

    __HAL_RCC_HSI_DISABLE();

     HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

     HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void Error_handler(void)
{
	while(1);
}

