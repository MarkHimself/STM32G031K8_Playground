
#include "include/GPIO_Output.h"


// This function will setup the GPIO PB6 as an output and toggle the port.
void GPIO_Output_Example(){
	
	int slowdown = 0;
	bool isHigh = true;
	
	Enable_GPIOB_Clock();								// Enable the clock to the GPIO-B
	Configure_PB6_AsOutput();							// Configure PB6 as an output
	Configure_PB6_AsPushPull();							// Configure for Push-Pull (Not open drain)
	Set_PB6_High();										// Set the port HIGH
	
	while(1){
		for (int i = 0; i < 100000; ++i){				// slow down the processor by making it do lots of division (division is slow)
			slowdown = 56;
			slowdown = slowdown / 5;
		}
		if (isHigh){
			Set_PB6_Low();
		}
		else{
			Set_PB6_High();
		}
		isHigh = !isHigh;
	}
}

void Enable_GPIOB_Clock(){
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;					// Enable clock to IO Port B (GPIO-B)		pg. 196
}

void Configure_PB6_AsOutput(){
	
	uint32_t temp = 0;
	
	temp = GPIOB->MODER;				// read the register
	temp &= ~(GPIO_MODER_MODE6);		// clear the mode of PB6
	temp |= GPIO_MODER_MODE6_0;			// select output mode
	GPIOB->MODER = temp;				// write to the register									pg. 241
	
	// configure the speed register?
	
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6);				// disable the pull up and pull down		pg. 242
}

void Configure_PB6_AsPushPull(){
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT6);	// Configure as Push-Pull								pg. 241
}


void Set_PB6_High(){
	GPIOB->BSRR = GPIO_BSRR_BS6;		// Toggle the PB6 port to HIGH								pg. 243
}

void Set_PB6_Low(){
	GPIOB->BSRR = GPIO_BSRR_BR6;		// Toggle the PB6 port to LOW
}

