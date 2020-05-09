# Simon-Says-C3PO

# Version 5.0
* Using Lab 9 as structure.
* Separated main() and interrupt functions.
* Use Enter Key to "start game".

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

NEED TO DO:
* Timing vary during rounds?
* Create an array to HOLD COM and USER LED .
** Compare the arrays.
* Have Enter Key to NOT work anymore after game has started AS WELL as letting other interrupts go through.
** (Using IntDisable(UART0_BASE) also disabled the GPIOF Switches.....)
* Get the game to work properly for ONE ROUND then expand, max can be 5???
* ALSO WHY SRAND() DOESN'T WORK?? Really need to have rand() to work base on time, not calculated. 
* Need to add error cases....
* ALSO WHY THE SWITCH KEEP BOUNCING WHEN THERE IS A SLIGHT DEBOUNCE ALREADY?
* Need to format code better, probably can put the game function into a dedicated .h/.c files for our eyes.
* Also I want to do fun easter eggs because tired.
