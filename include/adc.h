#ifndef ADC_H
#define ADC_H

#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"
#include "general_timer2_timetracking.h"


void ADC_Example1();
void Enable_ADC_Clock();
void ADC_UseSystemClock();
void ADC_Disable();
void ADC_Enable();
void ADC_EnableVoltageRegulator();
void ADC_Calibration();
void ADC_ClockMode2();
void ADC_DiscontinuousMode();
void ADC_SingleConversionMode();
void ADC_12bit_resolution();
void ADC_EnableAutoOffMode();
void ADC_DisableAutoOffMode();
void ADC_StartConversion();
void ADC_WaitForEndOfConversion();
void ADC_ChannelInputMode();
void ADC_ChannelSequenceMode();
void ADC_ChannelSelection(uint32_t channel);
uint32_t ADC_getData();

void ADC_EnableInterruptADRDY();





#endif