/*
 * MSP(Processor specific details) file - file where all the peripherals must be initialized
 */

#include "main.h"


/**
  * @brief  Initialize the MSP.
  * @retval None
  */
void HAL_MspInit( void )
{
	// Low-level processor initializations
	// HAL APIs for that are located in stm32f4xx_hal_cortex.c

	// 1. NVIC Priority grouping (if 2+ interrupts, what settings
	// will be used to figure out who has the highest priority )
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // default

	// 2. Enable required system exceptions of the processor(ARM M4)
	// System Control Block -> System Handler Control and State Register
	// Enable Usage fault, bus fault, and memory fault
	SCB->SHCSR = 0b111 << 16;

	// 3. Configure the priority of the system exceptions
	// No subpriority since NVIC_PRIORITYGROUP_4 grouping is selected
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

/**
  * @brief  Initialize the UART2.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspInit( UART_HandleTypeDef *huart ){

	// 1. Enable the corresponding clock
	__HAL_RCC_USART2_CLK_ENABLE();

	// 2. Pin muxing (PA2, PA3)
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_TypeDef GPIOA_Def;

	GPIO_InitTypeDef GPIOPA_Init;
	GPIOPA_Init.Pin = GPIO_PIN_2;
	GPIOPA_Init.Mode = GPIO_MODE_AF_PP;
	GPIOPA_Init.Pull = GPIO_PULLUP;
	GPIOPA_Init.Speed = GPIO_SPEED_FREQ_LOW;
	GPIOPA_Init.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(&GPIOA_Def, &GPIOPA_Init); // PA2 - TX

	GPIOPA_Init.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(&GPIOA_Def, &GPIOPA_Init); // PA3 - RX
	/*
	 * Manual equivalent:
	uint32_t* pointer = (uint32_t*)(GPIOA_BASE+0x20);
	*pointer &= ~(0b11111111 << 8); // clear AFRL3 and AFRL2
	*pointer |= GPIO_AF7_USART2 << 8; // Set AFRL2 to AF7
	*pointer |= GPIO_AF7_USART2 << 12; // Set AFRL3 to AF7
	*/

	// 3. Enable IRQ and Priority Settings
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);


}
