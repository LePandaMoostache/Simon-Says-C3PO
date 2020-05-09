#include "tivaSetup.h"

float PI=3.141593;
	
int main(void) {

		PortFunctionInit();
		UART_int_init();
		GPIOF_Interrupt_Init();
		Timer0A_Init(16000000);
		
	  //
    // Set the clocking to run directly from the crystal.
    //
		//SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
		UARTprintf("\r\n----Simon Says Game by C3PO---\n");
		UARTprintf("\r\nInstructions: Follow the LEDs in order on the LaunchPad, then match the colors!\n");
		UARTprintf("\r\nSW1 is to select a color. SW2 is to confirm color press.\n");
	
		UARTprintf("\r\nPlease press ENTER Key to start game!\n");
		

		while (1) //let interrupt handler do the UART echo function
		{
			
		}

	}
