
#include "include/proc_exceptions.h"



// infinite loop is "ok" for debugging but must be replaced for production code.

void NMI_Handler(void){
	while(1);
}

void HardFault_Handler(void){
	while(1);
}

void MemManage_Handler(void){
	while(1);
}










