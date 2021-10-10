

#include "include/main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


// Verify the initialized data is properly initialized.
// This verifies the linker script and startup code
uint32_t DataTest1 = 1;
uint32_t DataTest2 = 2;
uint32_t DataTest3 = 3;

// verify the .bss section is set to 0
uint32_t zero0;
uint32_t zero1;
uint32_t zero2;
uint32_t zero3;


// verify the .no_init section is not initializing data
__attribute__((section(".no_init")))
uint32_t NoInit0;

__attribute__((section(".no_init")))
uint32_t NoInit1;

__attribute__((section(".no_init")))
uint32_t NoInit2;

__attribute__((section(".no_init")))
uint32_t NoInit3;

int main(void){
	
	// verify that dividing works
	uint32_t divideTest1 = 56;
	divideTest1 = divideTest1 / 5;
	
	uint32_t myClockSpeed = SystemCoreClock;
	
	float pi = 3.1415;
	float mathTest1;
	mathTest1 = sinf(pi / 4);	// verify the math library works
	// sin(PI/4) should be 0.7071067812 (radians)
	
	
	//GPIO_Output_Example();
	//GPIO_Input_Example();
	
	init_pwm();
	
	// loop forever
	int i = 0;
	while(1){
		i++;
	}
}


