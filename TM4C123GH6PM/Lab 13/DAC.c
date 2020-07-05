// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"
/*#define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))*/
// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){volatile unsigned long  delay;
	SYSCTL_RCGC2_R |= 0x00000002;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_DR8R_R |= 0x0F;	// enable 8 mA drive on PB0,1,2,3
	GPIO_PORTB_DIR_R |= 0x0F;
	GPIO_PORTB_AFSEL_R &= ~0x0F;
	GPIO_PORTB_DEN_R |= 0x0F;
	GPIO_PORTB_PCTL_R &= ~0x0000FFFF;
	GPIO_PORTB_AMSEL_R &= ~0x0F;
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  outB = data;
}
