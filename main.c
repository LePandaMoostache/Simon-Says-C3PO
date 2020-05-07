#include "tivaSetup.h"

int main(void) {
	
		//time_t t;
		//srand((unsigned) time(NULL));
	//May need to configure the memory
	// implement pi
		PortFunctionInit();
		UART_int_init();
		GPIOF_Interrupt_Init();
		
	  //
    // Set the clocking to run directly from the crystal.
    //
   //SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |SYSCTL_OSC_MAIN);
		UARTprintf("\r\n----Simon Says Game by C3PO---\n");
		UARTprintf("\r\nInstructions: Follow the LEDs in order on the LaunchPad, then match the colors!\n");
		UARTprintf("\r\nSW1 is to select a color. SW2 is to confirm color press.\n");
	
		UARTprintf("\r\nPlease press ENTER Key to start game!\n");
		

		while (1) //let interrupt handler do the UART echo function
		{
			
		}

	}
