// Header files
#include "main.h"

// Private functions prototypes
void SystemClockConfig(void);
void UART2_Init(void);
void Error_Handler(void);

UART_HandleTypeDef huart2;
// Safe to type cast to uint8_t* since char is 1 byte as well
char* user_data = "Hello World!\r\n";


int main(void){

	// Initializations
	HAL_Init(); // Developer must define Msp_Init()
	SystemClockConfig(); // Developer-defined
	UART2_Init();

	// Send test data
	uint16_t data_len = strlen(user_data);
	if( HAL_UART_Transmit(&huart2, (uint8_t*) user_data, data_len, HAL_MAX_DELAY) != HAL_OK){
		Error_Handler();
	}

	// Read data
	uint8_t counter = 0;
	uint8_t rcv_byte;
	uint8_t rcv_buffer[100];
	HAL_UART_Receive(&huart2, &rcv_byte, 1, HAL_MAX_DELAY);

	while (counter < 100 && rcv_byte != '\n' && rcv_byte != '\r'){
		rcv_buffer[counter] = rcv_byte;
		HAL_UART_Receive(&huart2, &rcv_byte, 1, HAL_MAX_DELAY);
		counter++;
	}

	// Send its modified version back to the PC
	HAL_UART_Transmit(&huart2, (uint8_t*)rcv_buffer, counter, HAL_MAX_DELAY);

	while(1);

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
