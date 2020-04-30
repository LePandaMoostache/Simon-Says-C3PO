#include "tivaSetup.h"

int count = 0;
bool startGame = false;



void
PortFunctionInit(void) {

    volatile uint32_t ui32Loop;

    // Enable the clock of the GPIO port that is used for the on-board LED and switch.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;
	
	    // Unlock GPIO Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x01; // allow changes to PF0
    //
    // Enable pin PF0 for GPIOInput
    //

    //
    //First open the lock and select the bits we want to modify in the GPIO commit register.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

    //
    //Now modify the configuration of the pins that we unlocked.
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
     
		//
    // Enable pin PF4 for GPIOInput
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		//
    // Enable pin PF1 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
		
	  //
    // Enable pin PF2 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);


		//
    // Enable pin PF3 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

		// Set the direction of PF4 (SW1) and PF0 (SW2) as input by clearing the bit
    GPIO_PORTF_DIR_R &= ~0x11;

    // Enable PF4, and PF0 for digital function.
    GPIO_PORTF_DEN_R |= 0x11;

    //Enable pull-up on PF4 and PF0
    GPIO_PORTF_PUR_R |= 0x11;
}

void UART_int_init()
{
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
		UARTFlowControlSet(UART0_BASE,UART_FLOWCONTROL_RX);
		IntPrioritySet(INT_UART0, 0x00);
    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
	  
		//
    // Initialize the UART for console I/O. For uartstdio.c
    //
    UARTStdioConfig(0, 115200, 16000000);

}


void UARTIntHandler(void)
{
    uint32_t ui32Status;
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
		
		UARTSwitchCases();

}

void UARTSwitchCases(void)
{
		
		char newChar;
		newChar = UARTCharGet(UART0_BASE);
	
		if (newChar != NULL) {
			switch (newChar) {
			// Red LED is ON, prints R to terminal
			case '\r':
				UARTprintf("\r\nEnter Key Pressed\n");
				startGame = true;
				roundStart(); 
				break;

			// prints "Invalid Input" to terminal
			default: 
			UARTprintf("\r\nInvalid Input");
				break;
			}
			// set the char to NULL to get new inputs
			newChar = NULL; 
		}
}

//Globally enable interrupts 
void IntGlobalEnable(void) {
    __asm("    cpsie   i\n");
}

//Globally disable interrupts 
void IntGlobalDisable(void) {
    __asm("    cpsid   i\n");
}


/** GPIOF INTERRUPT INITIALIZATION***/
void GPIOF_Interrupt_Init(void) {

    NVIC_EN0_R |= 0x40000000; // enable interrupt 30 in NVIC address (GPIOF) 
    //NVIC_PRI7_R &= 0x00E0041C; // configure GPIOF interrupt priority as 0 global enable address
	
    GPIO_PORTF_IM_R |= 0x11; // arm interrupt on PF0 and PF4
    GPIO_PORTF_IS_R &= ~0x11; // PF0 and PF4 are edge-sensitive
    GPIO_PORTF_IBE_R &= ~0x11; // PF0 and PF4 NOT both edges trigger 
    GPIO_PORTF_IEV_R &= ~0x11;  	// PF0 and PF4 falling edge event
    IntGlobalEnable(); // globally enable interrupt 
}

/** GPIOF INTERRUPT HANDLER***/
void GPIOPortF_Handler(void)
{
	//switch debounce
	NVIC_EN0_R &= ~0x40000000; 
	SysCtlDelay(5333);	// Delay for a while
	NVIC_EN0_R |= 0x40000000; 
	if (startGame == true) {
  //SW1 has action
	if(GPIO_PORTF_RIS_R&0x10 )
	{
		//startGame = false;
		// acknowledge flag for PF4
		GPIO_PORTF_ICR_R |= 0x10; 
		
		//SW1 is pressed
		if(((GPIO_PORTF_DATA_R&0x10)==0x00)) 
		{
			//counter imcremented by 1
			count++;
			count = count & 3;
			//UARTprintf("\r\nColor currently selected: ");
		}
	}
	
	//SW2 has action
  if(GPIO_PORTF_RIS_R&0x01)
	{
		// acknowledge flag for PF0
		GPIO_PORTF_ICR_R |= 0x01; 
		
		if(((GPIO_PORTF_DATA_R&0x01)==0x00)) 
		{
			UARTprintf("----CONFIRM PRESS---");
		}
	}
	
	ledSwitchCases();
}
}

void ledSwitchCases(void) {
        switch (count) {

            case 0:
								UARTprintf("Blank\n");
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
                break;
            case 1:
								UARTprintf("Red\n");
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, RED_MASK);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
                break;
            case 2:
								UARTprintf("Blue\n");	
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, BLUE_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
                break;
            case 3:
								UARTprintf("Green\n");
							  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK);
                break;
		}
}

void roundStart(void) {
	
		if (startGame == true) {
			
			int roundNum = 1; 
			UARTprintf("\r\n----ROUND %i: ---\n", roundNum);

				int test = (rand() % 3) +1;
				UARTprintf("%i",test);
		}
		else {
		UARTprintf("\r\n----NOTHING HAPPENS---\n");
		}
	}

