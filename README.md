# stm32-waveshare-epaper-uart-lib

How to use:
  1. clone the repository to your stm32 project
  2. move the .h file to your includes
  3. move the .c file to your source
  4. include the stm32f1_epaper_display.h file to your main.c file

    void putchars(unsigned char * buffer, int size)
    {
	    HAL_UART_Transmit(&huart4, buffer, size, 10);
	}
5. find the place where your *UART_HandleTypeDef* is declared and define the function *putchars* - don't forget the prototype!
6. . . . 
7. profit
