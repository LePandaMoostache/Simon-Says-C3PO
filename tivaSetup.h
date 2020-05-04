#include "include.h"


extern void PortFunctionInit(void);
extern void UART_int_init(void);
extern void UARTIntHandler(void);
extern void UARTSwitchCases(void);
extern void IntGlobalEnable(void); 
extern void IntGlobalDisable(void);
extern void GPIOF_Interrupt_Init(void);
extern void GPIOPortF_Handler(void);
extern void ledSwitchCases(void);
extern void userLEDSwitchCases(int test);
extern void roundStart(void);

extern int count;
extern bool startGame;
