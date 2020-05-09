# Simon-Says-C3PO

# Version 5.0

Working:
- tivaSetup.c: Included Timer0A
- main.c: Initialized Timer0A
- game.c: Updated game algorithm to correctly find if player wins/lose the round
(ie: Round 3: correct/wrong/correct = lose round, game over)
(ie #2: Round 4: wrong/wrong/wrong/correct = lose round, game over)
- game.c: Removed memset() as it is not needed and caused Keil to crash frequently upon downloading to LaunchPad

Need to improve:
- tivaSetup.c: Need to figure out to get correct countdown timer by a true second.
ie: Round 2 would UARTprintf "2928" very quickly, not being a true counter timer. 
- tivaSetup.c: Optimize UARTSwitchCases to disable UART0A interrupt after pressing Enter Key. Not sure if using boolean is okay.
- tivaSetup.c: Optimize GPIOF to have lower priority than TIMER0A. Using booleans to determine if SW1 and SW2 can continue to press if player won/lost round X. 
- Overall: Commenting to make project easier to read.
           Need to verify timing with Logic Analyzer, possibly improve TIMER0A interrupt
- game.c/tivaSetup.c: Still need to figure out how to get random numbers and keep them.....
