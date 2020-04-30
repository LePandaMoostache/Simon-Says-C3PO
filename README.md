# Simon-Says-C3PO

- Version 0.01A
* Using Lab 9 as structure.
* Separated main() and interrupt functions.
* Use Enter Key to "start game".

NEED TO DO:
* Timing (Do that last).
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
