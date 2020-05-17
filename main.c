#include "tivaSetup.h"
	
int main(void) {
		unsigned long period = 10000000;
		// Set the clock to 10Mhz
		SysCtlClockSet(SYSCTL_SYSDIV_20|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		PortFunctionInit();
		UART_int_init();
		GPIOF_Interrupt_Init();
		Timer0A_Init(period);


		UARTprintf("\r\n----Simon Says Game by C3PO---\n");
		UARTprintf("\r\nInstructions: Follow the LEDs in order on the LaunchPad, then match the colors!\n");
		UARTprintf("\r\nSW1 is to select a color. SW2 is to confirm color press.\n");
	
		UARTprintf("\r\nPlease type your name. Then, press enter key to play!\n");

		while (1) //let interrupt handler do the UART echo function
		{

	}
}
