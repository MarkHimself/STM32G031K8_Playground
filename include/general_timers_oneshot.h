#ifndef GENERAL_TIMERS_ONESHOT_H
#define GENERAL_TIMERS_ONESHOT_H

#include <stdbool.h>
#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"

#include "GPIO_Output.h"
#include "GPIO_Input.h"


void general_timers_oneshot_ex();
void init_TIM2();
void init_TIM2_CH2_Oneshot();
void trigger_TIM2_CH2_Oneshot();
void writeTIM2_Reload(uint32_t AR_Value);
void writeTIM2_CH2_Compare(uint32_t C_Value);
void Enable_TIM2_Clock();
void setup_PA1_asTIM2_CH2();
void writeTIM2_ClockPrescaler(uint32_t p);
void selectTIM2_CH2_PWM_Mode2();


#endif