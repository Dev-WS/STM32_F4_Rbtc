/**
  ******************************************************************************
  * @author  Dev-WS
  * @year    2020
  ******************************************************************************
*/

#include "main.h"


typedef enum {FALSE = 0, TRUE = !FALSE} bool;
unsigned char buforRx[17]={0};
unsigned char bufRxIndex=0;
bool getData=FALSE;
unsigned char buforTx[20]={"Stan diod: ........\0"};
unsigned char bufTxIndex=0;
char *user_data = "The application is running\r\n";
char *user_data2 = "The uart IT is running\r\n";



uint8_t data_buffer[100];
uint8_t recvd_data;
uint32_t count=0;
uint8_t reception_complete = FALSE;

uint8_t duty_H1=499;
uint8_t duty_H2=0;
uint8_t m = 0x5A;
uint8_t dataRS = 0x00;
uint8_t multiple = 0x64;

int main(void)
{
	char msg[100];

	HAL_Init();
	SystemConfigClk();
	GPIO_Init();
    UART2_Init();
    I2C1_Init();
    TIM2_Init();
    TIM4_Init();
    SSD1306_Init();

    HAL_TIM_Base_Start_IT(&htim4);

    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);

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
	sprintf(msg,"PCLK2  : %ldHz\r\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&uart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

//	int test = 0;
//	int n = 0;

//	uint8_t x;

//	uint16_t len_of_data = strlen(user_data);
//	uint16_t len_of_data2 = strlen(user_data2);
//	HAL_UART_Transmit(&uart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);
//	HAL_UART_Transmit_IT(&uart2,(uint8_t*)user_data2,len_of_data2);

//	HAL_UART_Transmit(&uart2,(uint8_t*)user_data, sizeof(user_data),HAL_MAX_DELAY);


	//send_string("test!\r\n");

//    while(reception_complete != TRUE)
//    {
//    	HAL_UART_Receive_IT(&uart2,&recvd_data,1);
//    }

	//

	HAL_UART_Receive_IT(&uart2, &dataRS, 1);
	HAL_UART_Transmit_IT(&uart2, &m, 1);

	while(1){

		if(getData)
		{
			getData = FALSE;
			HAL_UART_Transmit_IT(&uart2, buforRx, 20);
		}

	}


	return 0;
}

void SystemConfigClk()
{
	RCC_OscInitTypeDef osc_init = {0};
	RCC_ClkInitTypeDef clk_init = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	memset(&osc_init,0,sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc_init.HSEState = RCC_HSE_BYPASS;
    osc_init.PLL.PLLState = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc_init.PLL.PLLM = 4;
	osc_init.PLL.PLLN = 100;
	osc_init.PLL.PLLP = RCC_PLLP_DIV2;
	osc_init.PLL.PLLQ = 7;

    //osc_init.HSEState = RCC_HSE_ON;
    if ( HAL_RCC_OscConfig(&osc_init) != HAL_OK)
    {
    	Error_handler();
    }

    clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
    					RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    //clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // NOT WORKING
    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
    clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    if( HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_3) != HAL_OK)
    {
    	Error_handler();
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance==USART2){

//		if(buforRx[bufRxIndex] == 0x0D) { // detecting /CR
//			  getData = TRUE;
//
//			   while (bufRxIndex<17) {
//				buforRx[bufRxIndex]=0;
//				bufRxIndex++;
//			  }
//			  bufRxIndex = 0;
//			} else {
//			  bufRxIndex++;
//			  if (bufRxIndex>16) bufRxIndex=16;
//
//			}
//			HAL_UART_Receive_IT(&uart2, &buforRx[bufRxIndex], 1);
//

//			duty_H1 = dataRS * multiple;
//
//			if (duty_H1 > 499) duty_H1 = 499;
//			if (duty_H1 < 0) duty_H1 = 0;

	}
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance==USART2){


		HAL_UART_Transmit_IT(&uart2, &m, 1);
	}


}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//	 if(recvd_data == '\r')
//	 {
//		 reception_complete = TRUE;
//		 data_buffer[count++]='\r';
//		 HAL_UART_Transmit(huart,data_buffer,count,HAL_MAX_DELAY);
//	 }
//	 else
//	 {
//		 data_buffer[count++] = recvd_data;
//	 }
//
//
//}
