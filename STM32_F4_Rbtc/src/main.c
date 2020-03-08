/**
  ******************************************************************************
  * @author  Dev-WS
  * @year    2020
  ******************************************************************************
*/

#include "main.h"

int main(void)
{
	char msg[100];

	HAL_Init();
	SystemConfigClk();
	GPIO_Init();
    UART2_Init();
    TIM2_Init();
    TIM4_Init();
    SSD1306_Init();

    memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %ldHz\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&uart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK   : %ldHz\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&uart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK1  : %ldHz\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&uart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK2  : %ldHz\r\n\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&uart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

	while(1){

		SSD1306_GotoXY(10,27);
		SSD1306_Puts("Hello!", &Font_7x10, 1);
		SSD1306_GotoXY(10,52);
		SSD1306_Puts("Test.", &Font_7x10, 1);
		SSD1306_UpdateScreen(); //display
		SSD1306_Fill(0x01);
		HAL_Delay(1000);
	}


	return 0;
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
    //clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // NOT WORKING
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
