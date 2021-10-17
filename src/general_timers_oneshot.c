
#include "include/general_timers_oneshot.h"

/*
TIM2 CH2
PA1			connect the output signal to PA1
AF2			use Alternate Function 2 to connect the timer 2, channel 2 signal to PA1

create a oneshot pulse.
*/


void general_timers_oneshot_ex(){
	
	volatile bool trigger = true;
	
	Enable_GPIOA_Clock();
	
	init_TIM2();
	init_TIM2_CH2_Oneshot();
	
	setup_PA1_asTIM2_CH2();
	
	while(1){
		if (trigger){
			trigger_TIM2_CH2_Oneshot();
			trigger = false;
		}
	}
}

void init_TIM2(){
	
	Enable_TIM2_Clock();
	
	// disable TIM2
	TIM2->CR1 &= 0x0U;	//								pg. 670
	
	// disable output channel 2									pg. 686
	TIM2->CCER &= ~TIM_CCER_CC2E;
	
	// reload
	// this is the value the oneshot pulse will turn off.
	writeTIM2_Reload(4000);
	
	// compare register
	// the value the oneshot pulse turns on
	writeTIM2_CH2_Compare(1);	// start the oneshot as soon as possible
	
	// select internal clock (CK_INT)							pg. 639
	// SMS = 000
	TIM2->SMCR = 0;		//										pg. 673
	
	// this should cause the PWM frequency to be 1 Hz (if your clock speed is 16 MHz and you 1000 for the reload register)
	// TIM2 clock frequency is 1000 Hz
	writeTIM2_ClockPrescaler(16000);
	
	// TIMER 2 counter is enabled.
	//TIM2->CR1 |= TIM_CR1_CEN;	//								pg. 670
	
	// Clear the counter value
	TIM2->CNT = 0x0U;			//								pg. 688
	
}

void init_TIM2_CH2_Oneshot(){
	
	TIM2->CR1 |= TIM_CR1_OPM;	// select one-pulse mode (stops clock)	pg. 670
	
	// use One-pulse mode
	// Use PWM Mode 2
	selectTIM2_CH2_PWM_Mode2();
	
	// re-initialize the counter
	// update the timer registers
	// without this, the first time you do a oneshot trigger won't do anything.
	TIM2->EGR = TIM_EGR_UG;		// update generation			pg. 679
	
}

void trigger_TIM2_CH2_Oneshot(){
	TIM2->CR1 |= TIM_CR1_CEN;	//								pg. 670
}

void writeTIM2_Reload(uint32_t AR_Value){
	TIM2->ARR = AR_Value;			// Auto reload register		pg. 689
}

void writeTIM2_CH2_Compare(uint32_t C_Value){
	TIM2->CCR2 = C_Value;			// 							pg. 690
}

void Enable_TIM2_Clock(){
	RCC->APBENR1 |= RCC_APBENR1_TIM2EN;					// Enable clock to TIM2						pg. 198
}

void setup_PA1_asTIM2_CH2(){
	
	uint32_t temp = 0;
	
	// enable output channel 2									pg. 686
	TIM2->CCER |= 0
		| TIM_CCER_CC2E		// Output Channel 2 signal is output on the corresponding output pin.
		//| TIM_CCER_CC2P		// Active low
	;
	
	// select alternate function mode for PA1					pg. 241
	temp = GPIOA->MODER;
	temp &= ~GPIO_MODER_MODE1_0;	// clear bit 0
	temp |= GPIO_MODER_MODE1_1;		// set bit 1
	GPIOA->MODER = temp;
	
	
	// select high speed										pg. 242
	temp = GPIOA->OSPEEDR;
	temp &= ~GPIO_OSPEEDR_OSPEED1_0;	// clear bit 0
	temp |= GPIO_OSPEEDR_OSPEED1_1;		// set bit 1
	GPIOA->OSPEEDR = temp;
	
	
	// select AF2												pg. 245
	// use AF2 for PA1 for TIM2_CH2
	temp = GPIOA->AFR[0];
	temp &= ~GPIO_AFRL_AFSEL1;			// clear the bits
	temp |= GPIO_AFRL_AFSEL1_1;
	GPIOA->AFR[0] = temp;
}

// this function will divide the TIMER 2 clock speed by p.
void writeTIM2_ClockPrescaler(uint32_t p){
	uint16_t psc = p - 1;			// subtract 1. Actual prescale value used is 1 + PSC
	TIM2->PSC = psc & TIM_PSC_PSC;	// 							pg. 688
}

void selectTIM2_CH2_PWM_Mode2(){
	uint32_t temp;
	temp = TIM2->CCMR1;				// read the register
	
	// clear all the channel 2 bits (to ensure they are clear)
	temp &= ~(0
		| TIM_CCMR1_OC2M
		| TIM_CCMR1_OC2PE
		| TIM_CCMR1_OC2FE
		| TIM_CCMR1_CC2S
	);
	
	temp |= 0						// select PWM mode 2		pg. 682
		| TIM_CCMR1_OC2M_2
		| TIM_CCMR1_OC2M_1
		| TIM_CCMR1_OC2M_0
	;
	
	TIM2->CCMR1 = temp;
}
