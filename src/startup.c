

#include "include/startup.h"
#include <system_stm32g0xx.h>

extern uint32_t _etext;
extern uint32_t _sstack;
extern uint32_t _estack;
extern uint32_t _sdata_flash;
extern uint32_t _sdata_sram;
extern uint32_t _edata_flash;
extern uint32_t _edata_sram;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sno_init;
extern uint32_t _eno_init;


void SVC_Handler						(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler						(void) __attribute__ ((weak, alias("Default_Handler")));

void SysTick_Handler					(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler						(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_TAMP_IRQHandler				(void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler						(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler				(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler	(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM2_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM14_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM16_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM17_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));
void LPUART1_IRQHandler					(void) __attribute__ ((weak, alias("Default_Handler")));

void main(void);

__attribute__((section(".isr_vector")))
uint32_t vector_table[] = {
	(uint32_t) &_estack,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &HardFault_Handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) &SVC_Handler,
	(uint32_t) 0,
	(uint32_t) 0,
	(uint32_t) &PendSV_Handler,
	(uint32_t) &SysTick_Handler,
	(uint32_t) &WWDG_IRQHandler,                   /* Window WatchDog              */
	(uint32_t) &PVD_IRQHandler,                    /* PVD through EXTI Line detect */
	(uint32_t) &RTC_TAMP_IRQHandler,               /* RTC through the EXTI line    */
	(uint32_t) &FLASH_IRQHandler,                  /* FLASH                        */
	(uint32_t) &RCC_IRQHandler,                    /* RCC                          */
	(uint32_t) &EXTI0_1_IRQHandler,                /* EXTI Line 0 and 1            */
	(uint32_t) &EXTI2_3_IRQHandler,                /* EXTI Line 2 and 3            */
	(uint32_t) &EXTI4_15_IRQHandler,               /* EXTI Line 4 to 15            */
	(uint32_t) 0,                                  /* reserved - UCPD and USB      */
	(uint32_t) &DMA1_Channel1_IRQHandler,          /* DMA1 Channel 1               */
	(uint32_t) &DMA1_Channel2_3_IRQHandler,        /* DMA1 Channel 2 and Channel 3 */
	(uint32_t) &DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler, /* DMA1 Channel 4 to Channel 5, DMAMUX1 overrun */
	(uint32_t) &ADC1_IRQHandler,                   /* ADC1                        */
	(uint32_t) &TIM1_BRK_UP_TRG_COM_IRQHandler,    /* TIM1 Break, Update, Trigger and Commutation */
	(uint32_t) &TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
	(uint32_t) &TIM2_IRQHandler,                   /* TIM2                         */
	(uint32_t) &TIM3_IRQHandler,                   /* TIM3                         */
	(uint32_t) &LPTIM1_IRQHandler,                 /* LPTIM1                       */
	(uint32_t) &LPTIM2_IRQHandler,                 /* LPTIM2                       */
	(uint32_t) &TIM14_IRQHandler,                  /* TIM14                        */
	(uint32_t) 0,                                  /* reserved                     */
	(uint32_t) &TIM16_IRQHandler,                  /* TIM16                        */
	(uint32_t) &TIM17_IRQHandler,                  /* TIM17                        */
	(uint32_t) &I2C1_IRQHandler,                   /* I2C1                         */
	(uint32_t) &I2C2_IRQHandler,                   /* I2C2                         */
	(uint32_t) &SPI1_IRQHandler,                   /* SPI1                         */
	(uint32_t) &SPI2_IRQHandler,                   /* SPI2                         */
	(uint32_t) &USART1_IRQHandler,                 /* USART1                       */
	(uint32_t) &USART2_IRQHandler,                 /* USART2                       */
	(uint32_t) &LPUART1_IRQHandler,                /* LPUART1                      */
	(uint32_t) 0,                                   /* reserved                     */
	(uint32_t) 0									/* reserved 					*/
};

void Reset_Handler(void){
	
	// copy .data from flash to ram
	uint32_t *flash_src = &_sdata_flash;
	uint32_t *ram_dst = &_sdata_sram;
	uint32_t len_bytes = (uint32_t)&_edata_flash - (uint32_t)&_sdata_flash;
	uint32_t len_4bytes = len_bytes >> 2;		// divide by 4
	
	for (uint32_t i = 0; i < len_4bytes; ++i){
		*ram_dst++ = *flash_src++;
	}
	
	// init .bss to 0
	ram_dst = &_sbss;
	len_bytes = (uint32_t)&_ebss - (uint32_t)&_sbss;
	len_4bytes = len_bytes >> 2;
	for (uint32_t i = 0; i < len_4bytes; ++i){
		*ram_dst++ = 0;
	}
	
	// call SystemInit to initialize the microcontroller
	SystemInit();
	
	// update the SystemCoreClock (not needed in this case)
	SystemCoreClockUpdate();
	
	// call main
	main();
}

// infinite loop is "ok" for debugging but must be replaced for production code.
void Default_Handler(void){
	while(1){
		
	}
}

