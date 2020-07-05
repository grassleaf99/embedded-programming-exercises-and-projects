// PROJECT NÀY DÙNG ÐUOC

// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
#define PE0_SW 						      (*((volatile unsigned long *)0x40024004))
#define PE1_LED       					(*((volatile unsigned long *)0x40024008))
	
// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****
void delayms(unsigned long ms){
  unsigned long count;
  while(ms > 0 ) { // repeat while there are still ms to delay
		// án vào Project -> Option for Target 'Lab8'. Tai muc Target tháy Xtal (MHz) = 16 MHz -> có ve tan so dang duoc su dung là 16 MHz
		// mà hàm TExaS_Init() cài dat clock he thong là 80 MHz
		// -> tính thoi gian delay voi tan so (16 + 80) / 2 = 48 MHz
    count = 16000; // number of counts to delay 1 ms at 80MHz ((80 + 16) / 2 = 48 -> 48MHz -> 16000*3*(1/48M) = 1 ms)
    while (count > 0) { 
      count--;							// phép trù này tôn 1 chu ky
														// quay lai dâu vong lap ton 2 chu ky
    } // This while loop takes approximately 3 cycles
    ms--;
  }
}
// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ volatile unsigned long delay;
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  EnableInterrupts();           // enable interrupts for the grader
  SYSCTL_RCGC2_R |= 0x00000010;    
  delay = SYSCTL_RCGC2_R;           
	GPIO_PORTE_CR_R |= 0x03;           // allow changes to E0, E1
  GPIO_PORTE_AMSEL_R &= ~0x03;        // 3) disable analog function
	GPIO_PORTE_PCTL_R &= ~0x000000FF;   // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R &= ~0x01;          // 5.1) PE0 input, 
  GPIO_PORTE_DIR_R |= 0x02;          // 5.2) PE1 output  
  GPIO_PORTE_AFSEL_R &= ~0x03;        // 6) no alternate function   
  GPIO_PORTE_DEN_R |= 0x03;          // 7) enable digital pins PF4-PF0   
	PE1_LED = 0x02;
  while(1){
		delayms(100);
		if(PE0_SW == 1)
			PE1_LED ^= 0x02;
		else
			PE1_LED = 0x02;
  }
  
}
