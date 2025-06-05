// Header files
#include "stm32f4xx_hal.h"

// Private functions prototypes
void SystemClockConfig(void);


int main(void){

	HAL_Init(); // Developer must define Msp_Init()
	SystemClockConfig(); // Developer-defined


	return 0;
}

void SystemClockConfig(void){

}
