
#include "include/general_timers_pwm.h"


// this code will initialize and setup the TIMER 3 PWM on channel 3.
// It will also connect the TIMER 3 Channel 3 PWM signal to PB0
void init_pwm(){
	// PB0
	// TIM3_CH3													pg. 41 of datasheet
	// Uses AF1 (Alternate Function 1)
	
	Enable_GPIOB_Clock();
	Configure_PB0_AsFloating();
	
	Enable_TIM3_Clock();
	
	// disable output channel 3									pg. 686
	TIM3->CCER &= ~TIM_CCER_CC3E;
	
	// reload (start counting at 0) when this value is reached
	writeTIM3_CH3_Reload(1000);
	
	// compare register
	writeTIM3_CH3_Compare(100);
	
	
	// select internal clock (CK_INT)							pg. 639
	// SMS = 000
	TIM3->SMCR = 0;		//										pg. 673
	
	// this should cause the PWM frequency to be 1 Hz (if your clock speed is 16 MHz and you 1000 for the reload register)
	writeTIM3_ClockPrescaler(16000);
	
	// use PWM mode 1.
	// channel is active from 0 to the channel compare register value.
	selectTIM3_CH3_PWM_Mode1();
	
	setup_PB0_asPWM();
	
	// enable output channel 3									pg. 686
	TIM3->CCER |= 0
		| TIM_CCER_CC3E		// Output Channel 3 signal is output on the corresponding output pin.
		//| TIM_CCER_CC3P	// this bit will make the channel active low. I prefer active high.
	;
	
	// TIMER 3 counter is enabled.
	TIM3->CR1 |= TIM_CR1_CEN;	//								pg. 670
	
}

void setup_PB0_asPWM(){
	
	uint32_t temp = 0;
	
	// select alternate function mode for PB0					pg. 241
	temp = GPIOB->MODER;
	temp &= ~GPIO_MODER_MODE0_0;	// clear bit 0
	temp |= GPIO_MODER_MODE0_1;		// set bit 1
	GPIOB->MODER = temp;
	
	
	// select high speed										pg. 242
	temp = GPIOB->OSPEEDR;
	temp &= ~GPIO_OSPEEDR_OSPEED0_0;	// clear bit 0
	temp |= GPIO_OSPEEDR_OSPEED0_1;		// set bit 1
	GPIOB->OSPEEDR = temp;
	
	
	// select AF1												pg. 245
	// use AF1 for PBO for TIM3_CH3
	temp = GPIOB->AFR[0];
	temp &= ~GPIO_AFRL_AFSEL0;			// clear the bits
	temp |= GPIO_AFRL_AFSEL0_0;
	GPIOB->AFR[0] = temp;
}

void Configure_PB0_AsFloating(){		// No pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0;	// clear the bits (No pull-up, pull down)					pg. 242
}

void Enable_TIM3_Clock(){
	RCC->APBENR1 |= RCC_APBENR1_TIM3EN;					// Enable clock to TIM3						pg. 198
}

// get rid of _CH3 since only the timers (not the channels) get a reload value.
void writeTIM3_CH3_Reload(uint32_t AR_Value){
	TIM3->ARR = AR_Value;			// Auto reload register		pg. 689
}

void writeTIM3_CH3_Compare(uint32_t C_Value){
	TIM3->CCR3 = C_Value;			// 							pg. 690
}

void selectTIM3_CH3_PWM_Mode1(){
	uint32_t temp;
	temp = TIM3->CCMR2;				// read the register
	
	// clear all the channel 3 bits (to ensure they are clear)
	temp &= ~(0
		| TIM_CCMR2_OC3CE
		| TIM_CCMR2_OC3M
		| TIM_CCMR2_OC3PE
		| TIM_CCMR2_OC3FE
		| TIM_CCMR2_CC3S
	);
	
	temp |= 0						// select PWM mode 1		pg. 682
		| TIM_CCMR2_OC3M_2
		| TIM_CCMR2_OC3M_1
	;
	
	TIM3->CCMR2 = temp;
}

// this function will divide the TIMER 3 clock speed by p.
void writeTIM3_ClockPrescaler(uint32_t p){
	uint16_t psc = p - 1;			// subtract 1. Actual prescale value used is 1 + PSC
	TIM3->PSC = psc & TIM_PSC_PSC;	// 							pg. 688
}

