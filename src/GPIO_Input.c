
#include "include/GPIO_Input.h"



// This function will setup the GPIO PA8 as an input and read the port.
void GPIO_Input_Example(){
	
	int slowdown = 0;
	bool isHigh;
	
	Enable_GPIOA_Clock();								// Enable the clock to the GPIO-A
	Configure_PA8_AsInput();							// Configure PA8 as an input
	Configure_PA8_AsPulldown();							// Configure for Pull-down
	//Configure_PA8_AsPullup();							// Configure for Pull-up
	//Configure_PA8_AsFloating();							// Configure for no pull-up and no pull-down
	
	while(1){
		for (int i = 0; i < 100000; ++i){				// slow down the processor by making it do lots of division (division is slow)
			slowdown = 56;
			slowdown = slowdown / 5;
		}
		isHigh = read_PA8();
		slowdown = 0;
	}
}

void Enable_GPIOA_Clock(){
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;					// Enable clock to IO Port A (GPIO-A)		pg. 196
}

void Configure_PA8_AsInput(){
	uint32_t temp = 0;
	
	temp = GPIOA->MODER;				// read the register
	temp &= ~(GPIO_MODER_MODE8);		// clear the mode of PA8 - Selects Input Mode
	GPIOA->MODER = temp;				// write to the register									pg. 241
	
	// configure the speed register?
	
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD8);				// disable the pull up and pull down		pg. 242
}

void Configure_PA8_AsPulldown(){
	uint32_t temp = 0;
	temp = GPIOA->PUPDR;				// read the register
	temp &= ~GPIO_PUPDR_PUPD8;			// clear the bits
	temp |= GPIO_PUPDR_PUPD8_1;			// select pull-down
	GPIOA->PUPDR = temp;				// Configure as Pull-down									pg. 242
}

void Configure_PA8_AsPullup(){
	uint32_t temp = 0;
	temp = GPIOA->PUPDR;				// read the register
	temp &= ~GPIO_PUPDR_PUPD8;			// clear the bits
	temp |= GPIO_PUPDR_PUPD8_0;			// select pull-up
	GPIOA->PUPDR = temp;				// Configure as Pull-up										pg. 242
}

void Configure_PA8_AsFloating(){		// No pull-up, no pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD8;	// clear the bits (No pull-up, pull down)					pg. 242
}

bool read_PA8(){
	return GPIOA->IDR & GPIO_IDR_ID8;	// return the status of the data bit						pg. 243
}






