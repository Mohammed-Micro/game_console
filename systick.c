#include <stdint.h>
#include "systick.h"


void systick_set_source(char src){

	if(src == SYSTICK_SOURCE_PSC){
		*SYSTICK_CSR &= ~SYSTICK_SRC;
	}
	else{
		*SYSTICK_CSR |= SYSTICK_SRC;
	}
}

void systick_set_period(uint32_t period){

	if(*SYSTICK_CSR & SYSTICK_SRC){	//CORE CLOCK
		*SYSTICK_RELR = (period * (AHB_CLOCK / 1000000));
	}
	else{
		*SYSTICK_RELR = (period * (AHB_CLOCK / 8000000));
	}

}

void systick_wait(void){

	*SYSTICK_CSR &= ~SYSTICK_EN;
	*SYSTICK_CUR = *SYSTICK_RELR;
	*SYSTICK_CSR |= SYSTICK_EN;
	while(!(*SYSTICK_CSR & SYSTICK_CNTFLAG));
	*SYSTICK_CSR &= ~SYSTICK_EN;

}

void systick_enable_irq(void){

	*SYSTICK_CSR |= SYSTICK_TICKINT;
}

void systick_disable_irq(void){
	
	*SYSTICK_CSR &= ~SYSTICK_TICKINT;
}

