#include "game.h"
#include "tivaSetup.h"


void roundStart(void) {
	
		if (startGame == true) {
			//srand(time(NULL));
			int roundNum = 1; 
			UARTprintf("\r\n----ROUND %i: ---\n", roundNum);

				int test = (rand() % 3) +1;
				UARTprintf("%i",test);
				userLEDSwitchCases(test);
				SysCtlDelay(2000000);
				test = (rand() % 3) +1;
				userLEDSwitchCases(test);
		}
		else {
		UARTprintf("\r\n----NOTHING HAPPENS---\n");
		}
	}
