# operation-calculator-embedded-system-
Project Objective : To solve the mathematical operations 
 
Project Components:
1. An ATmega microcontroller board interfaced to an LCD 
2. Keypad 
3.  Potentiometer 
4. Resistors. 

Project Description: 
1) first of all , we initialize the hardware setting up all the bits according  with the write and read necessities for each port’s pin
2) setup the default output values for each port, and initialize the calculator variables 
3) We check if the power button was pressed so the variable power is    set to On, if not we wait until we press.
4) If power is On we check if there’s some key pressed.
5) If there’s some key pressed we get the ID of that key and we send to be processed by the calculator’s main function. 
6) After that we get from the calculator program the number that we need to show and we send to the display function  
7) We use functions which solve the operations << +  -  *  / >> 
8) And solve a lot of operation together like a function and give the result 
