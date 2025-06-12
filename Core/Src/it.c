#include "main.h"

// Must be implemented to make sure System timer
// properly ticks every 1 ms
void SysTick_Handler(){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
