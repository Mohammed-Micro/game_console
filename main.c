#include <stdint.h>
#include "rcc.h"
#include "vga.h"


void rcc_setup_hse_72mhz(void);

int main(void){
	
	rcc_setup_hse_72mhz();
	initscr();
	test_colors();
	while(1);
}

void rcc_setup_hse_72mhz(void){

        *RCC_CR |= HSION;
        while(!(*RCC_CR & HSIRDY));

        *RCC_CR |= HSEON;
        while(!(*RCC_CR & HSERDY));

        *RCC_CFGR |= (7<<18);   //PLLMUL = 9
        *RCC_CFGR |= PLLSRC;    //HSE
        *RCC_CFGR |= (3<<14);   //ADC / 8 = 9 MHZ
        *RCC_CFGR |= (1<<10);   //APB1 = 36 MHZ

        *RCC_CR |= PLLON;
        while(!(*RCC_CR & PLLRDY));

        *RCC_CFGR |= 2; //SYSCLOCK = PLL
        *FLASH_ACR |= 1; //TWO WAIT STATES

}

