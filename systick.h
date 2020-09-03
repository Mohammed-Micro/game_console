#ifndef _SYSTICK_H
#define _SYSTICK_H

#define SYSTICK_CSR 	((volatile uint32_t*)0xE000E010)
#define SYSTICK_RELR	((volatile uint32_t*)0xE000E014)
#define SYSTICK_CUR	((volatile uint32_t*)0XE000E018)

//bit fields

#define SYSTICK_EN	(1<<0)
#define SYSTICK_TICKINT	(1<<1)
#define SYSTICK_SRC	(1<<2)
#define SYSTICK_CNTFLAG	(1<<16)


//Constants

#define SYSTICK_SOURCE_PSC	0
#define SYSTICK_SOURCE_CORE	1

extern uint32_t AHB_CLOCK;
//API Fucntions

void systick_set_source(char);
void systick_set_period(uint32_t);
void systick_wait(void);
void systick_enable_irq(void);
void systick_disable_irq(void);

#endif

