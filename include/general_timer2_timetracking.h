#ifndef GENERAL_TIMER2_TIMETRACKING_H
#define GENERAL_TIMER2_TIMETRACKING_H

#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"

#include "general_timers_oneshot.h"
#include "GPIO_Output.h"

void TIM2_delay_ex();
void TIM2_ConfigureTimetracking();
void Disable_TIM2_Clock();
void TIM2_DisableCounter();
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t ms);


#endif