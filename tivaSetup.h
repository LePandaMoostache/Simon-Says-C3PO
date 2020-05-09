#include "include.h"


extern void PortFunctionInit(void);
extern void UART_int_init(void);
extern void UARTIntHandler(void);
extern void UARTSwitchCases(void);

extern void IntGlobalEnable(void); 
extern void IntGlobalDisable(void);

extern void Timer0A_Init(unsigned long period);
extern void Timer0A_Handler (void); 
extern void GPIOF_Interrupt_Init(void);
extern void GPIOPortF_Handler(void);

extern int userLEDSwitchCases(int userCount);
extern int ledSwitchCases(int comCount);


extern int userCount;
extern bool startGame;
extern bool lostRound;
extern int position;

extern void roundStart(int roundNum);
extern bool roundCheck(void);

extern int comArray[];
extern int userArray[];

extern float randomLED;
extern int currentRound;

extern int timerseconds;
