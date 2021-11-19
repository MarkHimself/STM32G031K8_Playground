
#include "include/adc.h"


/*
Use ADC_IN10.
This corresponds to PB2 (Info located in the datasheet. Table 12. Pin assignment and description)
*/


/*
perform an ADC conversion from the value of a port.
conversion initiated by software
*/
void ADC_Example1(){
	
	uint32_t adc_data = 0;
	
	// timer control
	TIM2_ConfigureTimetracking();
	
	// ADC control
	ADC_UseSystemClock();
	Enable_ADC_Clock();
	ADC_Disable();
	ADC_ClockMode2();
	ADC_EnableVoltageRegulator();
	ADC_Calibration();
	
	//ADC_EnableInterruptADRDY();
	//NVIC_EnableIRQ(ADC1_IRQn);
	
	ADC_Enable();
	
	ADC_DiscontinuousMode();
	ADC_12bit_resolution();
	ADC_EnableAutoOffMode();
	ADC_ChannelInputMode();
	
	ADC_ChannelSelection(10);
	
	while(1){
		ADC_StartConversion();
		ADC_WaitForEndOfConversion();
		adc_data = ADC_getData();
		delay_s(1);
		
		// you can disable the ADC
		ADC_Disable();
		
		delay_s(2);
		
		// Re-enable the ADC
		ADC_Enable();
	}
	
}

void Enable_ADC_Clock(){
	RCC->APBENR2 |= RCC_APBENR2_ADCEN;					// Enable clock to ADC		pg. 201
}

void ADC_UseSystemClock(){
	RCC->CCIPR &= ~RCC_CCIPR_ADCSEL;					// Use the system clock as the clock source for the ADC		pg. 209
}

// procedure is outlined on pg. 349
void ADC_Disable(){
	uint32_t temp = 0;
	
	temp = ADC1->CR;
	
	if (!(temp & ADC_CR_ADEN)) return;
	
	if (temp & ADC_CR_ADSTART){				// if there is an ongoing conversion
		ADC1->CR = ADC_CR_ADSTP;			// stop the conversion
		while(ADC1->CR & ADC_CR_ADSTP);		// wait until the conversion is stopped
	}
	
	ADC1->CR = ADC_CR_ADDIS;				// disable the ADC
	while(ADC1->CR & ADC_CR_ADEN);			// wait until the ADC is disabled
	while(ADC1->CR & ADC_CR_ADDIS);
	
	//ADC1->ISR = ADC_ISR_ADRDY;			// Clear the ADC Ready bit in the status register
}

// procedure is outlined on pg. 349
// however, the ISR_ADRDY bit does not come on the 2nd time you enable the ADC (i.e. enable ADC, disable ADC, enable ADC 2nd time)
void ADC_Enable(){
	
	if (ADC1->CR & ADC_CR_ADEN) return;		// if the ADC is already enabled
	
	ADC1->ISR = ADC_ISR_ADRDY;				// Clear the ADC Ready bit in the status register
	ADC1->CR = ADC_CR_ADEN;
	delay_ms(1);
	//while(!(ADC1->ISR & ADC_ISR_ADRDY));	// wait while it's not ready (stops waiting when it's ready) - the ADRDY bit is not reliable
}

void ADC_EnableVoltageRegulator(){
	ADC1->CR = ADC_CR_ADVREGEN;
	delay_us(20);		// wait for the voltage regulator startup time (pg. 77 of datasheet)
}

void ADC_Calibration(){
	uint32_t temp = ADC1->CR;
	if (!(temp & (ADC_CR_ADCAL | ADC_CR_ADSTART | ADC_CR_ADSTP | ADC_CR_ADDIS | ADC_CR_ADEN))){	// ensure the ADC is disabled
		ADC1->CR = ADC_CR_ADCAL;			// start the calibration
		while(ADC1->CR & ADC_CR_ADCAL);	// wait until calibration is complete
	}
}

// only call this function with the ADC disabled.
void ADC_ClockMode2(){
	
	uint32_t temp = ADC1->CFGR2;
	
	temp &= ~ADC_CFGR2_CKMODE;
	temp |= ADC_CFGR2_CKMODE_1;		// PCLK / 4
	ADC1->CFGR2 = temp;
}

void ADC_DiscontinuousMode(){
	uint32_t temp = ADC1->CFGR1;
	temp |= ADC_CFGR1_DISCEN;
	temp &= ~ADC_CFGR1_CONT;
	ADC1->CFGR1 = temp;
}

// see page 386, notes in ADSTART
void ADC_SingleConversionMode(){
	uint32_t temp = ADC1->CFGR1;
	temp &= ~(0
		| ADC_CFGR1_CONT
		| ADC_CFGR1_DISCEN
	);
	ADC1->CFGR1 = temp;
}

void ADC_12bit_resolution(){
	uint32_t temp = ADC1->CFGR1;
	temp &= ~ADC_CFGR1_RES;
	ADC1->CFGR1 = temp;
}

void ADC_EnableAutoOffMode(){
	uint32_t temp = ADC1->CFGR1;
	temp |= ADC_CFGR1_AUTOFF;
	ADC1->CFGR1 = temp;
}

void ADC_DisableAutoOffMode(){
	uint32_t temp = ADC1->CFGR1;
	temp &= ~ADC_CFGR1_AUTOFF;
	ADC1->CFGR1 = temp;
}

void ADC_StartConversion(){
	ADC1->CR = ADC_CR_ADSTART;
}

void ADC_WaitForEndOfConversion(){
	uint32_t temp;
	
	temp = ADC1->CR;
	if ((temp & ADC_CR_ADDIS) || (~temp & ADC_CR_ADEN)) return;		// return if the ADC is being disabled or not enabled
	
	// can also use the end of conversion flag
	while(ADC1->CR & ADC_CR_ADSTART);
}

void ADC_ChannelInputMode(){
	ADC1->CFGR1 &= ~ADC_CFGR1_CHSELRMOD;
}

void ADC_ChannelSequenceMode(){
	ADC1->CFGR1 |= ADC_CFGR1_CHSELRMOD;
}

void ADC_ChannelSelection(uint32_t channel){
	if (channel > 18) return;
	
	ADC1->ISR = ADC_ISR_CCRDY;							// clear the CCRDY flag
	ADC1->CHSELR = ADC_CHSELR_CHSEL0 << channel;		// select the n'th channel
	
	while(~ADC1->ISR & ADC_ISR_CCRDY);					// wait until the CCRDY flag is set.				pg. 381
}

uint32_t ADC_getData(){
	uint32_t temp = 0;
	temp = ADC1->DR;
	return temp;
}

void ADC_EnableInterruptADRDY(){
	ADC1->IER |= ADC_IER_ADRDYIE;
}

void ADC1_IRQHandler(void){
	
	ADC1->ISR = ADC_ISR_ADRDY;
	
	return;
}
