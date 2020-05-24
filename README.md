# Simon Says by Group C3PO for ENGR 478-04 Spring 2020
This project uses the EK-TM4C123GXL, aka the TM4C123G LaunchPad Evaluation Kit. It features using UART, TIMER0A, and GPIOF (Both Switches and LED) interrupts, and to verify the general purpose timer we used the [HiLetGo USB Logic Analyzer bought from Amazon](https://smile.amazon.com/gp/product/B077LSG5P2/). For software we used [Keil μVision v5.29 (or MDK-ARM on website)](https://www.keil.com/download/product/) with [Stellaris ICDI Debug Adapter Support](http://www.keil.com/support/docs/4196.htm) and [Tera Term v4.105](https://ttssh2.osdn.jp/index.html.en). 

## Version 9.0
May 24, 2020

*Final Commit for Project Submission*

INSTRUCTIONS
- Game will prompt user for their name
  - Note: This prompt uses ASCII values to gather the sum for our random number generator equation. 
- After user is done typing their name, they will need to press enter to start the game.
- For each round will correspond to how many LEDs are shown to the user, 1:1.
- New rounds will repeat the LEDs from previous run in that program run PLUS its new random LED.
- SW1: Scroll through the color: Red (01), Blue (10), Green (11), Blank (00)
- SW2: Adds color to their LED order, when have same number of rounds in LED order, program will check if user got correct/wrong order.
- If user got correct LED order: Move to next round
- If user got wrong LED order: Game over, need to reset
- If user ran our of time: Ran out of time, game over and need to reset
- Don't forget the timer! First round starts with 30 seconds, but the next rounds will be 30 - currentRound!

Please head on over to our [Github Wiki](https://github.com/LePandaMoostache/Simon-Says-C3PO/wiki) page for a detailed process/analysis on how we completed our project. 
