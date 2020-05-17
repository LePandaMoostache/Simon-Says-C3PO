#include "tivaSetup.h"

int userCount = 0;
bool startGame = false;
bool lostRound = false;
int currentRound = 1;
int position = 1;
int timerseconds = 30;
char charNum;
int nameNum = 0;

//Globally enable interrupts 
void IntGlobalEnable(void) {

    __asm("    cpsie   i\n");
}

//Globally disable interrupts 
void IntGlobalDisable(void) {

    __asm("    cpsid   i\n");
}

/** GPIOF PORT FUNCTION INITIALIZER **/
void PortFunctionInit(void) {

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

/** GPIOF INTERRUPT INITIALIZER **/
void GPIOF_Interrupt_Init(void) {

    NVIC_EN0_R |= 0x40000000; // enable interrupt 30 in NVIC address (GPIOF) 
    //NVIC_PRI7_R &= 0x00E0041C; // configure GPIOF interrupt priority as 0 global enable address

    GPIO_PORTF_IM_R |= 0x11; // arm interrupt on PF0 and PF4
    GPIO_PORTF_IS_R &= ~0x11; // PF0 and PF4 are edge-sensitive
    GPIO_PORTF_IBE_R &= ~0x11; // PF0 and PF4 NOT both edges trigger 
    GPIO_PORTF_IEV_R &= ~0x11; // PF0 and PF4 falling edge event
    IntEnable(INT_GPIOF);
}

/** GPIOF INTERRUPT HANDLER **/
void GPIOPortF_Handler(void) {

    //switch debounce
    NVIC_EN0_R &= ~0x40000000;
    SysCtlDelay(533333); // Delay for a while
    NVIC_EN0_R |= 0x40000000;

    if (startGame == true && lostRound == false) {

        //SW1 has action
        if (GPIO_PORTF_RIS_R & 0x10) {

            // acknowledge flag for PF4
            GPIO_PORTF_ICR_R |= 0x10;

            // SW1 is pressed
            // Remember: GPIOF switches use negative logic.
            if (((GPIO_PORTF_DATA_R & 0x10) == 0x00)) {
                //counter incremented by 1
                userCount++;
                userCount = userCount & 3;
                UARTprintf("\r\nColor currently selected: ");
                userLEDSwitchCases(userCount);
            }
        }

        // SW2 has action
        // Remember: GPIOF switches use negative logic.
        if (GPIO_PORTF_RIS_R & 0x01) {
            // acknowledge flag for PF0
            GPIO_PORTF_ICR_R |= 0x01;

            if (((GPIO_PORTF_DATA_R & 0x01) == 0x00)) {

                UARTprintf("\r\n----CONFIRM PRESS---");
                userArray[position] = userCount;
                userLEDSwitchCases(userCount);
                position++;
                if (position == currentRound + 1) {
                    roundCheck();
                }
            }
        }

    }
}

/** UART0 INTERRUPT INITIALIZER **/
void UART_int_init() {
    //
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);

		UARTFlowControlSet(UART0_BASE,UART_FLOWCONTROL_RX);
		IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
}

/** UART0 INTERRUPT HANDLER **/
void UARTIntHandler(void) {

    uint32_t ui32Status;
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTGetNum();

}

/** UARTGetNum gets the sum of the ASCII value of the player's name. **/
// Note: Player can enter anything, as this function takes the char from UART0.
void UARTGetNum(void) {
	
    charNum = UARTCharGet(UART0_BASE);
    char enter[] = "\r";
        if (strcmp(&charNum, enter) == 0) {
            //UARTprintf("\r\n%i", nameNum);
            UARTprintf("\r\nEnter Key Pressed\n");
            startGame = true;
            roundStart(currentRound);
        } else {
            UARTprintf("%c", charNum);
            nameNum = nameNum + charNum;
        }
        
}

/** TIMER0A INTERRUPT INITIALIZER **/
void Timer0A_Init(unsigned long period) {
    //
    // Enable Peripheral Clocks 
    //
    IntPriorityGroupingSet(0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // configure for 32-bit timer mode
    TimerLoadSet(TIMER0_BASE, TIMER_A, period - 1); //reload value
    IntEnable(INT_TIMER0A); // enable interrupt 19 in NVIC (Timer0A)
    IntPrioritySet(INT_TIMER0A, 0x00); // configure Timer0A interrupt priority as 0
    IntPriorityMaskSet(0x4); // 0100.0000 = 40 in hex
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // arm timeout interrupt
    TimerEnable(TIMER0_BASE, TIMER_A); // enable timer0A
}



/** TIMER0A INTERRUPT HANDLER **/
void Timer0A_Handler(void) {

    if (startGame == true && lostRound == false) {
        // acknowledge flag for Timer0A timeout
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        //decreases by integer 1 
        UARTprintf("\r\n%i", timerseconds);
        timerseconds--;

        if (timerseconds == 0) {
            roundCheck();
        }
    }

}


// Remember to remove the UARTprintf, exists right now for test cases. 
// Should use GPIOPinWrite on the ON stage, for consistency.
int ledSwitchCases(int count) {
    int clockDelay = ((SysCtlClockGet()) / 3);
    switch (count) {
    case 0:
        UARTprintf("Blank\n");
        GPIO_PORTF_DATA_R = 0x00;
        break;
    case 1:
        UARTprintf("Red\n");
        GPIO_PORTF_DATA_R = 0x02;
        SysCtlDelay(clockDelay);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
        break;
    case 2:
        UARTprintf("Blue\n");
        GPIO_PORTF_DATA_R = 0x04;
        SysCtlDelay(clockDelay);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
        break;
    case 3:
        UARTprintf("Green\n");
        GPIO_PORTF_DATA_R = 0x08;
        SysCtlDelay(clockDelay);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
        break;
    }
    return count;
}

// May need this again for the user side, that way can display confirmation of LED
// Currently using ledSwitchCases() for both comArray and userArray

int userLEDSwitchCases(int userCount) {

    switch (userCount) {
    case 0:
        UARTprintf("User: Blank\n");
        GPIO_PORTF_DATA_R = 0x00;
        break;
    case 1:
        UARTprintf("User: Red\n");
        GPIO_PORTF_DATA_R = 0x02;
        SysCtlDelay(2000000);
        GPIO_PORTF_DATA_R = 0x00;
        break;
    case 2:
        UARTprintf("User: Blue\n");
        GPIO_PORTF_DATA_R = 0x04;
        SysCtlDelay(2000000);
        GPIO_PORTF_DATA_R = 0x00;
        break;
    case 3:
        UARTprintf("User: Green\n");
        GPIO_PORTF_DATA_R = 0x08;
        SysCtlDelay(2000000);
        GPIO_PORTF_DATA_R = 0x00;
        break;
    }
    return userCount;
}
