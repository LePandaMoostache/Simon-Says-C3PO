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
