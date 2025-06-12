// Header files
#include "main.h"

// Private functions prototypes
void SystemClockConfig(void);
void UART2_Init(void);
void Error_Handler(void);

UART_HandleTypeDef huart2;
char user_data = "Hello World!\r\n";


int main(void){

	HAL_Init(); // Developer must define Msp_Init()
	SystemClockConfig(); // Developer-defined

	UART2_Init();

	return 0;
}

void SystemClockConfig(void){}

void UART2_Init(void){
	// Type definition
	huart2.Instance = USART2;

	// Initial type definition
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	// Apply configurations
	if( HAL_UART_Init(&huart2) != HAL_OK){
		Error_Handler();
	}
}

void Error_Handler(void){
	// Error handling ...
	while(1);
}
