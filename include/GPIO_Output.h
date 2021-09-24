#ifndef GPIO_OUTPUT_H
#define GPIO_OUTPUT_H

#include <stdbool.h>
#include "Device/ST/STM32G0xx/Include/stm32g031xx.h"


void GPIO_Output_Example();
void Enable_GPIOB_Clock();
void Configure_PB6_AsOutput();
void Configure_PB6_AsPushPull();
void Set_PB6_High();
void Set_PB6_Low();


#endif