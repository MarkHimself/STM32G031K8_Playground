#ifndef STARTUP_H
#define STARTUP_H

#include <stdint.h>
#include <system_stm32g0xx.h>	// this relies on stdint being defined...


void Reset_Handler(void);



// Fault Exceptions of the Cortex-M4 Processor
void NMI_Handler			(void) __attribute__ ((weak));
void HardFault_Handler		(void) __attribute__ ((weak));
void MemManage_Handler		(void) __attribute__ ((weak));



#endif