#ifndef GPIO_INPUT_H
#define GPIO_INPUT_H

#include <stdbool.h>
#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"


void GPIO_Input_Example();
void Enable_GPIOA_Clock();
void Configure_PA8_AsInput();
void Configure_PA8_AsPulldown();
void Configure_PA8_AsPullup();
void Configure_PA8_AsFloating();
bool read_PA8();


#endif