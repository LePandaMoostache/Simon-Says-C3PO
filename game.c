#include "tivaSetup.h"

float randomLED = 0;
int comArray[10];
int userArray[10];
int correct = 0; 
bool wonRound = false;

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

// ledSwitchCases returns an int, so UARTprintf() will not work here.
// comArray did not keep all the contents of the array
// WAS ABLE TO CLEAR userARRAY
bool roundCheck(void) {

    for (int i = 1; i < currentRound + 1; i++) {
						UARTprintf("\r\nIndex: %i", i);
            UARTprintf("\r\nOrder of LED was: %i", comArray[i]);
            UARTprintf("\r\nUser Order of LED was: %i", userArray[i]);
        if (comArray[i] == userArray[i]) {
            wonRound = true;
						correct++;
        } 
				if (comArray[i] != userArray[i]) {
            lostRound = true;
						correct--;
        }
    }
    if (wonRound == true && correct == currentRound) {
        currentRound++; // Counts up to show the next round
        userCount = 0;
        position = 1;
				correct = 0;
        memset(userArray, 0, sizeof(userArray)); // clear userArray
        roundStart(currentRound); // Jumps back to roundStart
    }
		if (lostRound == true && correct != currentRound) {
			UARTprintf("\r\nGAME OVER");
		}
    return lostRound;
}
