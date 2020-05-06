#include "tivaSetup.h"
int randomLED = 0;
int comArray[20];
int userArray[20];

void roundStart(int roundNum) {
		if (startGame == true) {


			//srand(time(0));
			UARTprintf("\r\n----ROUND %i ---\n", roundNum);
			
			//	randomLED = (rand() % 3) +1;
			//	ledSwitchCases(randomLED);
			
			for(int i = 0; i < roundNum; ++i) {
				randomLED = (rand() % 3) +1;
				comArray[i] = randomLED; // keep randomLED to computer's array
				ledSwitchCases(randomLED);
			}
		}
		
		// Error case
		if (startGame == false) {
		UARTprintf("\r\n----NOTHING HAPPENS---\n");
		}
}

// How to "clear" userArray to allow new inputs? 
// ledSwitchCases returns an int, so UARTprintf() will not work here.
// comArray did not keep all the contents of the array, but userArray DOES
bool roundCheck(void) {
	for (int i = 0; i <= currentRound; ++i) {
		UARTprintf("\r\nColor: ", randomLED);
			if (comArray[i] == userArray[i]){
				UARTprintf("\r\nCorrect! Order of LED was: %i", ledSwitchCases(comArray[i]));
				UARTprintf("\r\nCorrect, User Order of LED was: %i", ledSwitchCases(userArray[i]));
				lostRound = false;
				break;
				} else { 
				UARTprintf("\r\nWrong, Order of LED was: %i", ledSwitchCases(comArray[i]));
				UARTprintf("\r\nWrong,User Order of LED was: %i", ledSwitchCases(userArray[i]));
				lostRound = true;
				}
			}
	if (lostRound == false){
				currentRound++; // Counts up to show the next round
				memset(userArray, 0, sizeof(userArray));
				roundStart(currentRound); // Jumps back to roundStart
	}
	return lostRound;
}
