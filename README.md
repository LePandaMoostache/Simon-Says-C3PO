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
1. PortFunctionInit()
     1. Initialize GPIOF using PinMux Utility 
1. GPIOF_Interrupt_Init()
     1. Enables GPIOF in NVIC address
     1. Arm interrupt on PF0 and PF4
     1. PF0 and PF4 set to edge sensitive
     1. PF0 and PF4 are falling edge trigger ONLY
1. GPIOPortF_Handler()
     1. Use switch debounces
     1. Is startGame true AND lostRound is false?
          - YES 
               - Action on SW1?
                    - YES
                         - Updates userCount by 1
                         - userCount is within 3, so 00 -> 01 -> 10 -> 11 -> 00 -> etc
                         - Prints "Color currectly selected: "
                         - Goes to userLEDSwitchCases with userCount number
               - Action on SW2?
                    - YES
                         - Prints "Confirm Press"
                         - Adds userCount to userArray's current position
                         - Displays user's confirmed LED number
                         - Updates position by 1
                         - Is position equal to currentRound + 1? 
                              - YES
                                   - Go to roundCheck()
                              - NO
                                   - Return to interrupt
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
          
