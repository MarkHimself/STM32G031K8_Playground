#ifndef GENERAL_TIMERS_PWM_H
#define GENERAL_TIMERS_PWM_H

#include <stdbool.h>
#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"

#include "GPIO_Output.h"




void init_pwm();
void setup_PB0_asPWM();
void Configure_PB0_AsFloating();
void Enable_TIM3_Clock();
void writeTIM3_CH3_Reload(uint32_t AR_Value);
void writeTIM3_CH3_Compare(uint32_t C_Value);
void selectTIM3_CH3_PWM_Mode1();
void writeTIM3_ClockPrescaler(uint32_t p);


#endif