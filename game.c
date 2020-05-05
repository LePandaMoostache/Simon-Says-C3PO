#include "tivaSetup.h"
int randomLED = 0;
int comArray[20];
int userArray[20];

void roundStart(int roundNum) {
		if (startGame == true) {


			//srand(time(0));
			UARTprintf("\r\n----ROUND %i ---\n", roundNum);
			//comArray();
			
			//	randomLED = (rand() % 3) +1;
			//	ledSwitchCases(randomLED);
			
			for(int i = 0; i < roundNum; ++i) {
				randomLED = (rand() % 3) +1;
				comArray[roundNum] = randomLED; // keep randomLED to computer's array
				ledSwitchCases(randomLED);
			}

		// Error case
		if (startGame == false) {
		UARTprintf("\r\n----NOTHING HAPPENS---\n");
		}
	}
}

bool roundCheck(void) {
	for (int i = 0; i <= currentRound; ++i) {
			if (comArray[i] == userArray[i]){
				UARTprintf("\r\nRight");
				currentRound++;
				roundStart(currentRound); // Jumps back to roundStart
				lostRound = false;
				} else { 
					UARTprintf("\r\nWrong");
				lostRound = true;
				}
			}
	return lostRound;
}
