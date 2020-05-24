#include "include.h"

extern void PortFunctionInit(void);
extern void UART0_init(void);
extern void UART0_Handler(void);
extern void UARTGetNum(void);

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
extern int currentRound;
extern int timerSeconds;
extern int nameNum;

extern void roundStart(int roundNum);
extern void roundCheck(void);

extern int comArray[];
extern int userArray[];

