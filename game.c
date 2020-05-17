#include "tivaSetup.h"

int comArray[10];
int userArray[10];

void roundStart(int roundNum) {
	
    float randomLED = 0;
    if (startGame == true) {

        UARTprintf("\r\n----ROUND %i ----\n", roundNum);

        // As long it is not the first round, repeat the LED order
        for (int i = 1; i < roundNum; i++) {
            UARTprintf("\r\nIndex: %i", i);
            ledSwitchCases(comArray[i]);
        }

        // First round: Gives first LED
        // Subsequent rounds: Add new element to comArray by 1
        UARTprintf("\r\nIndex: %i", currentRound);
        randomLED = (nameNum+rand()) % 3 + 1; // >:C
        comArray[currentRound] = randomLED;
        ledSwitchCases(comArray[currentRound]);

        // Error case
        if (startGame == false) {
            UARTprintf("\r\n----NOTHING HAPPENS----\n");
        }
    }
}

void roundCheck(void) {
	
    // Initialized and reset each round
    int correct = 0;

    //
    for (int i = 1; i < currentRound + 1; i++) {
        UARTprintf("\r\nIndex: %i", i);
        UARTprintf("\r\nOrder of LED was: %i", comArray[i]);
        UARTprintf("\r\nUser Order of LED was: %i", userArray[i]);

        // For every time computer and user arrays are equal, add 1 to correct counter. 
        if (comArray[i] == userArray[i]) {
            correct++;
        }

        // For every time computer and user arrays are NOT equal, decrease 1 from correct counter. 
        // lostRound is now true, prevent player to go to next round.
        if (comArray[i] != userArray[i]) {
            lostRound = true;
            correct--;
        }
    }

    // If correct counter equals to the current round, player won that round, can continue.
    if (correct == currentRound) {
				UARTprintf("\r\nCorrect! Start next round...\n");
				SysCtlDelay(2000000);
        userCount = 0; // Reset position of user LED currently selected
        position = 1; // Clears userArray's contents
        timerseconds = 30 - currentRound; // Decrease timer by 1 for next round
        currentRound++; // Counts up to show the next round
        roundStart(currentRound); // Jumps back to roundStart
    }

    // If player did not get correct order AND correct counter is NOT equal to current round,
    // Display Game Over
    if (lostRound == true && correct != currentRound) {

        UARTprintf("\r\nGAME OVER");
		}
    // If player ran out of time, will display below statement.
    // Note: Game Over UARTprintf statement will also print, since it fits. 
    if (timerseconds == 0) {
        UARTprintf("\r\nRAN OUT OF TIME");
    }
}
