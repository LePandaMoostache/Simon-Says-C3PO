#include "tivaSetup.h"

int randomLED = 0;
int comArray[20];
int userArray[20];
int correct = 0; 
void roundStart(int roundNum) {
    if (startGame == true) {

        UARTprintf("\r\n----ROUND %i ---\n", roundNum);

        for (int i = 1; i <= roundNum; i++) {
            UARTprintf("\r\nIndex: %i", i);
            randomLED = rand() % 3 + 1;
            comArray[i] = randomLED;
            ledSwitchCases(comArray[i]);
        }

        // Error case
        if (startGame == false) {
            UARTprintf("\r\n----NOTHING HAPPENS---\n");
        }
    }
}

// How to "clear" userArray to allow new inputs? 
// ledSwitchCases returns an int, so UARTprintf() will not work here.
// comArray did not keep all the contents of the array
// WAS ABLE TO CLEAR userARRAY
bool roundCheck(void) {

    for (int i = 1; i < currentRound + 1; i++) {
        if (comArray[i] == userArray[i]) {
            UARTprintf("\r\nIndex: %i", i);
            UARTprintf("\r\nCorrect! Order of LED was: %i", ledSwitchCases(comArray[i]));
            UARTprintf("\r\nCorrect, User Order of LED was: %i", ledSwitchCases(userArray[i]));
            lostRound = false;
						correct++;
        } 
				if (comArray[i] != userArray[i]) {
            UARTprintf("\r\nIndex: %i", i);
            UARTprintf("\r\nWrong! Order of LED was: %i", ledSwitchCases(comArray[i]));
            UARTprintf("\r\nWrong, User Order of LED was: %i", ledSwitchCases(userArray[i]));
            lostRound = true;
						correct--;
        }
    }
    if (lostRound == false && correct == currentRound) {
        currentRound++; // Counts up to show the next round
        userCount = 0;
        position = 1;
				correct = 0;
        memset(userArray, 0, sizeof(userArray)); // clear userArray
        roundStart(currentRound); // Jumps back to roundStart
    }
		if (lostRound == true) {
			UARTprintf("\r\nGAME OVER");
		}
    return lostRound;
}
