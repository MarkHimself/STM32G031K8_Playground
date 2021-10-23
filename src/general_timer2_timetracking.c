
#include "include/general_timer2_timetracking.h"

/*
Use TIM2 for time-tracking because it is a 32-bit timer
microsecond, millisecond and second delay functions have been implemented.

*/

void TIM2_delay_ex(){
	
	uint32_t a = 0;
	
	TIM2_ConfigureTimetracking();
	
	// set up PB6 as an output to turn it on/off and watch it with a logic analyzer.
	Enable_GPIOB_Clock();								// Enable the clock to the GPIO-B
	Configure_PB6_AsOutput();							// Configure PB6 as an output
	Configure_PB6_AsPushPull();							// Configure for Push-Pull (Not open drain)
	Set_PB6_Low();
	
	while(1){
		for (int i = 2000; i < 4000; i = i + 1000){
			a = 2;
			delay_ms(i);
			a = 2;
			delay_s(12);
			a = 2;
			delay_us(21000000);							// 21 [s] delay
			a = 2;
			
			Set_PB6_High();
			delay_us(17);
			Set_PB6_Low();
			delay_us(426);
			Set_PB6_High();
			delay_ms(2);
			Set_PB6_Low();
			
		}
	}
}


void TIM2_ConfigureTimetracking(){
	
	Disable_TIM2_Clock();					// this will reset TIM2
	Enable_TIM2_Clock();
	
	TIM2_DisableCounter();
	
	TIM2->CR2 = 0;
	TIM2->SMCR = 0;
	TIM2->DIER = 0;
	TIM2->SR = 0;
	TIM2->TISEL = 0;
	
	TIM2->CNT = 0;							// set count to 0					pg. 687
	
	TIM2->CCMR1 = 0;
	TIM2->CCMR2 = 0;
	
	TIM2->CCER = 0;
	
	TIM2->EGR = TIM_EGR_UG;					// update generation				pg. 679
}

void Disable_TIM2_Clock(){
	RCC->APBENR1 &= ~RCC_APBENR1_TIM2EN;	// Disable clock to TIM2			pg. 198
}

void TIM2_DisableCounter(){
	TIM2->CR1 = 0;
	TIM2->CNT = 0;
}

void delay_us(uint32_t us){
	// good up to 4,290,000 ms (4,290,000,000 us)
	
	uint32_t temp = 0;
	
	if (us == 0) return;
	
	if (us > 4290000000){
		temp = us / 1000;		// amount of delay to do in [ms]
		delay_ms(temp);
		us = us - temp*1000;	// amount of delay still needed to do in [us]
	}
	
	// perform the delay in microseconds
	if (us > 0){
		// Using a 16 prescaler results in 1us clock pulses.
		writeTIM2_ClockPrescaler(16);
		TIM2->EGR = TIM_EGR_UG;					// update generation				pg. 679
		TIM2->ARR = us;			// Load the reload register
		
		TIM2->CR1 = 0			// start the timer
			| TIM_CR1_OPM
			| TIM_CR1_CEN
		;
	
		while(TIM2->CR1 & TIM_CR1_CEN);	// wait for timer to finish
		TIM2->SR = 0;
	}
}

void delay_ms(uint32_t ms){
	// good up to 1000 ms
	uint32_t temp = 0;
	
	if (ms == 0) return;
	
	if (ms > 1000){
		temp = ms / 1000;		// amount of delay to do in [s]
		delay_s(temp);
		ms = ms - temp*1000;	// amount of delay still needed to do in [ms]
	}
	
	// perform the delay in milliseconds
	if (ms > 0){
		// using a 250 prescaler with the MCU frequency of 16MHz results in a timer frequency of 64,000 Hz.
		// Now, just multiply delay [ms] by 64 (left shift by 6) to calculate the number of clock ticks needed.
		writeTIM2_ClockPrescaler(250);
		TIM2->EGR = TIM_EGR_UG;					// update generation				pg. 679
		
		TIM2->ARR = ms << 6;
		TIM2->CR1 = 0
			| TIM_CR1_OPM
			| TIM_CR1_CEN
		;
		
		while(TIM2->CR1 & TIM_CR1_CEN);
		TIM2->SR = 0;
	}
	return;
}

void delay_s(uint32_t s){
	// good up to 16777215 s (do not go above this value)
	
	// perform the delay in seconds
	if (s > 0){
		// using a 62,500 prescaler with the MCU frequency of 16MHz results in a timer frequency of 256 Hz.
		// Now, just multiply delay [s] by 256 (left shift by 8) to calculate the number of clock ticks needed.
		writeTIM2_ClockPrescaler(62500);
		TIM2->EGR = TIM_EGR_UG;					// update generation				pg. 679
		
		TIM2->ARR = s << 8;
		TIM2->CR1 = 0
			| TIM_CR1_OPM
			| TIM_CR1_CEN
		;
		
		while(TIM2->CR1 & TIM_CR1_CEN);
		TIM2->SR = 0;
	}
	return;
}

