#include "include.h"


extern void PortFunctionInit(void);
extern void UART_int_init(void);
extern void UARTIntHandler(void);
extern void UARTSwitchCases(void);
extern void IntGlobalEnable(void); 
extern void IntGlobalDisable(void);
extern void GPIOF_Interrupt_Init(void);
extern void GPIOPortF_Handler(void);
extern int userLEDSwitchCases(int userCount);

extern int ledSwitchCases(int comCount);


extern int userCount;
extern bool startGame;
extern bool lostRound;

extern void roundStart(int roundNum);
extern void roundStartHelper(int currentRound);
extern bool roundCheck(void);
extern void roundWin(void);
extern void roundLose(void);


extern int comArray[];
extern int userArray[];

extern int randomLED;
extern int currentRound;

