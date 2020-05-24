# Simon Says by Group C3PO

## Version 8.0

**main.c**
1. Set period to 10000000
2. Set the clock to 10MHz
3. Call PortFunctionInit()
4. Call UART_init()
5. Call GPIOF_Interrupt_Init()
6. Timer0A_Init(period)
7. Print statement to UART, uses Tera Term
     - Title of the Game
     - Instructions
     - Prompts user to type their name
8. While loop to allow interrupt handlers function until user gets a game over.

**tivaSetup.c**
1. IntGlobalEnable()
1. IntGlobalDisable()
1. 
**game.c**
1. roundStart()
     1. If bool startGame is true
          - Prints "ROUND %i", depends on currentRound, default is 1.
          - If as long not the first round: repeat the LED order
          - First round and new rounds: 
               - randomLED = (nameNum+rand()) % 3 + 1 (Uses our own random equation)
               - Add randomLED number to COM array
               - For demo purposes: Print color statement on TeraTerm 
     1. If bool start is false, if by any chance while running
          - Error case: Prints "NOTHING HAPPENS"
               
1. roundCheck()
     1. For loop: Prints index number of COM array and user Array
     1. Is COM array same as user array?
          - YES: Increase correct count
          - NO: Decrease correct count
     1. Is correct count match with currentRound?
          - YES
               - Reset userCount
               - Reset position
               - Decrease timerSeconds by 1, that way next round is "faster"
               - Increase currentRound by 1, to indicate correct next round number
               - Jump to roundStart()
          
