#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>


#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define 	RED_MASK 		0x02
#define 	BLUE_MASK 		0x04
#define 	GREEN_MASK 		0x08
#define 	OFF 				0x00

#define		SW2					0x01 // PF0, 2^0 = 1
#define 	SW1					0x10 // PF4, 2^4 = 16
extern void PortFunctionInit(void);
extern void UART_int_init(void);
extern void UARTIntHandler(void);
extern void UARTSwitchCases(void);
extern void IntGlobalEnable(void); 
extern void IntGlobalDisable(void);
extern void GPIOF_Interrupt_Init(void);
extern void GPIOPortF_Handler(void);
extern void ledSwitchCases(void);
extern void roundStart(void);

extern int count;
extern bool startGame;
