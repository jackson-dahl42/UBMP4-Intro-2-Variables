/*==============================================================================
 Project: Intro-2-Variables
 Date:    May 16, 2021
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (Boolean, or bool) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world toggle button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

#define pressed 0
#define notPressed 1
#define A1
#ifdef ProgramAnalysis
// Program constant definitions
const unsigned char maxCount = 50;

// Program variable definitions
unsigned char SW2Count = 0;
bool SW2Pressed = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices

    // Code in this while loop runs repeatedly.
    while(1)
	{

   // Count new SW2 button presses
       if(SW2 == pressed && SW2Pressed == false)
       {
           LED3 = 1;
           if(SW2Count < 255 )
           {
               SW2Count += 1;
           }
           SW2Pressed = true;
       }
 
    // Clear pressed state if released
       if(SW2 == notPressed)
       {
           LED3 = 0;
           SW2Pressed = false;
       }

       if(SW2Count >= maxCount)
       {
           LED4 = 1;
       }
       else
       {
           LED4 = 0;
       }
        
     // Reset count and turn off LED D4
        if(SW3 == pressed)
        {
            LED4 = 0;
            SW2Count = 0;
        }
        
     // Add a short delay to the main while loop.
        __delay_ms(10);
        
     // Activate bootloader if SW1 is pressed.
        if(SW1 == pressed)
        {
            RESET();
        }
    }
}
#endif
#ifdef A1
// Two Player clicker game
// Program constant definitions
const unsigned char maxCount = 50;

// Program variable definitions
unsigned char SW2Count = 0;
bool SW2Pressed = false;
unsigned char SW5Count = 0;
bool SW5Pressed = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices

    // Code in this while loop runs repeatedly.
    while(1)
	{
    // Player 1
    // Count new SW2 button presses
       if(SW2 == pressed && SW2Pressed == false)
       {
           LED3 = 1;
           if(SW2Count < 255)
           {
               SW2Count += 1;
           }
           SW2Pressed = true;
       }
    // Clear pressed state if released
       if(SW2 == notPressed)
       {
           LED3 = 0;
           SW2Pressed = false;
       }
    //Player 1 wins
       if(SW2Count >= maxCount && LED5 == 0)
       {
           LED4 = 1;
       }
       else
       {
           LED4 = 0;
       }
    // Player 2
       if(SW5 == pressed && SW5Pressed == false)
       {
           LED6 = 1;
           if(SW5Count < 255)
           {
               SW5Count += 1;
           }
           SW5Pressed = true;
       }
    // Clear pressed state if released
       if(SW5 == notPressed)
       {
           LED6 = 0;
           SW5Pressed = false;
       }
    // Player 2 wins
       if(SW5Count >= maxCount && LED4 == 0)
       {
           LED5 = 1;
       }
       else
       {
           LED5 = 0;
       }
        
     // Reset game
        if(SW3 == pressed || SW4 == pressed)
        {
            LED4 = 0;
            SW2Count = 0;
            LED5 = 0;
            SW5Count = 0;
        }
        
     // Add a short delay to the main while loop.
        __delay_ms(10);
        
     // Activate bootloader if SW1 is pressed.
        if(SW1 == pressed)
        {
            RESET();
        }
    }
}
#endif
#ifdef A2
// Toggle button that turns an LED on when pressed, then off when pressed again.
// Variables
bool SW2Pressed = false;
//Toggle button that turns an LED on when pressed, then off when pressed again.
//Variables
bool LED3light = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    while(1)
    {
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = !LED3;
            SW2Pressed = true;
        }

        if(SW2 == !pressed)
        {
            SW2Pressed = false;
        }

        if(SW1 == pressed)
        {
            RESET();
        }
    }
}
#endif
#ifdef A3
// Multi-function button, lights one button when pressed and another when held for more than a second.
// Variables
const unsigned char timeCount = 150;
unsigned char SW2Count = 0;
int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    while(1)
    {
        if(SW2 == pressed)
        {
            LED3 = 1;
            SW2Count += 1;
        }

        if(SW2Count >= timeCount)
        {
            LED4 = 1;
        }

        if(SW2 == !pressed)
        {
            LED3 = 0;
            LED4 = 0;
            SW2Count = 0;
        }

        __delay_ms(10);

        if(SW1 == pressed)
        {
            RESET();
        }
    }
}
#endif
#ifdef A4
// A program that tests for switch bounce. Press SW2 and if LED4 lights there is switch bounce.
// Variables
const char timeCount = 2;
unsigned char SW2Count = 0;
bool SW2Pressed = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    while(1)
    {

    // Count new SW2 button presses
       if(SW2 == pressed && SW2Pressed == false)
       {
           LED3 = 1;
           if(SW2Count < 255)
           {
               SW2Count += 1;
           }
           SW2Pressed = true;
       }
 
    // Clear pressed state if released
       if(SW2 == notPressed)
       {
           LED3 = 0;
           SW2Pressed = false;
       }

       if(SW2Count >= timeCount)
       {
           LED4 = 1;
       }
       else
       {
           LED4 = 0;
       }
        
    // Reset count and turn off LED D4
        if(SW3 == pressed)
        {
            LED4 = 0;
            SW2Count = 0;
        }

        if(SW1 == pressed)
        {
            RESET();
        }
    }
}
#endif
#ifdef A5
// The push buttons didn't bounce because when I held down the button the second light didn't 
// turn on. Because of that I know that only one event happened when I pressed the button.
// If two or more events happened when I pressed the button then the second light would turn on
// and it would mean there was switch bounce in the push buttons. You could create a program that
// ignores switch bounce in a time span. The program is below. The light will only activate after
// the amount of time in the variable and will ignore the switch bounce.

// Variables
const unsigned char timeCount = 50;
unsigned char SW2Count = 0;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    while(1)
    {
	if(SW2 == pressed)
	{
	    SW2Count += 1;
	}
	if(SW2 == !pressed)
	{
	    SW2Count = 0;
	    LED3 = 0;
	}
	if(SW2Count >= timeCount)
	{
	    LED3 = 1;
	}
        if(SW1 == pressed)
        {
            RESET();
        }
    }
}

#endif
/* Program Analysis
 * 
 * 1. The 'SW2Count' variable is created within RAM as an 8-bit memory location
 *    by the declaration: 'unsigned char SW2Count = 0;'
 *    What is the the maximum value an 8-bit variable can store?
 *    What are some benefits and drawbacks of using 8-bit variables in an 8-bit
 *    microcontroller?

    The maximum value an 8-bit variable can store is 255. A drawback of using an 8-bit 
variable is that you cannot represent numbers over 255, but I could not think of any 
benefits that come with an 8-bit variable other than that it is compatible with the hardware 
that is the UBMP4. The number 255 also resetsto 0 when you add 1 to the variable which may 
be useful.

 * 2. The constant 'maxCount' is defined using a declaration similar to that
 *    used for the SW2Count variable, but with the 'const' prefix added in the
 *    declaration. Can you think of some advantages of declaring a constant like
 *    this, using a separate statement above the main code, rather than just
 *    embedding the value of the constant where it is needed in the code?

    There are many advantages to declaring a constant variable rather than writing the number 
 in the code. An example could be if you want to change the number of the constant later in 
 your code. If you didn’t set up a variable you would have to go through the code and change 
 all of the numbers. With a constant variable you only have to change one number to affect 
 all the other variables. Another advantage of a constant variable is that it could be useful 
 if you are dealing with a large number you do not want to keep writing. An example could be 
 calculating the area of a circle you would have to use pi = 3.14159… And so on. With a constant 
 variable you would only have to write pi in place of the number.

 * 3. This program should light LED D3 every time SW2 is pressed, and light
 *    LED D4 once the count reaches 50. Try it, and count how many times you
 *    have to press the button until LED D4 turns on. SW3 resets the count so
 *    you can perform repeated attempts.
 * 
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: try pressing and releasing the button at different rates of speed.)

 When I press and release the button at different speeds LED D4 will turn on after a different 
 number of presses. I can turn it on with a 1-7 push of the button. I could not get the light 
 to turn on after 50 presses because the code is flawed. The light would turn on after less than 
 50 button presses. You can even turn the light on with one press simply by holding down.
 
 * 
 * 4. Modify the second 'if' structure to add the else block, as shown below:

        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D4. LED D4 should stay on continuously while the value of SW2Count is
 *    higher than maxCount. If LED D4 turns off, what can you infer about the
 *    value of the SW2Count variable? Can you explain what happens to the
 *    SW2Count variable as the SW2 button is held?

 When LED D4 turns off I can infer that the value of the SW2 variable is less than the maxCount 
 variable. I’m inferring that after the highest number of SW2 is reached when you add one to the 
 highest number it resets to zero.

 * 
 * 5. We can set a limit on the SW2Count variable by encapsulating its increment
 *    statement inside a conditional statement. In your program, replace the
 *    line 'SW2Count = SW2Count + 1;' with the code, below:
 
            if(SW2Count < 255)
            {
                SW2Count += 1;
            }

 *    This code demonstrates the use of the assignment operator '+=' to shorten
 *    the statement 'SW2Count = SW2Count + 1;' The same operation is performed,
 *    but in a more compact form. After adding this code, what is the maximum
 *    value that the SW2Count variable will reach? How does this affect the
 *    operation of LED D4 when SW2 is held?

 The maximum value SW2Count variable will reach is 255. This will affect the operation of LED D4 
 when SW2 is held because when SW2 is held and LED D4 turns on the light will stay on because the 
 variable will never add 1 to 255 and reset to 0. 

Questions 6 and 7 were completed in the code Program Analysis.

 *
 * 6. The fundamental problem with this program is that pushbutton SW2 is sensed
 *    in each cycle of the loop and if its state is read as pressed, another
 *    count is added to the SW2Count variable. Rather than responding to state,
 *    the program needs to be made to respond only to each new press -- in other
 *    words, a *change* of SW2 state, from not-pressed to pressed. Doing this
 *    requires the use of another variable to store the prior state of SW2, so
 *    that its current state can be evaluated as being the same, or different
 *    from its state in the previous loop. Replace the initial if-else condition 
 *    with the following two if conditions:

        // Count new SW2 button presses
        if(SW2 == 0 && SW2Pressed == false)
        {
            LED3 = 1;
            SW2Pressed = true;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
        }

        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 *    These two if conditions make use of the Boolean SW2Pressed variable to
 *    store the current state of SW2 for the next cycle of the main while loop.
 *    Boolean variables can store 0/false or 1/true, interchangeably. The first
 *    if condition, above, compares the current SW2 state with the previously
 *    stored SW2Pressed variable so that a new count is only added when the SW2
 *    button is pressed and SW2Pressed is false. In the if structure, SW2Pressed
 *    is set to true before a count is added. The following if structure resets
 *    SW2Pressed to false when the button is released. Try the code to verify
 *    that it works.
 * 
 *    The conditional statement in the first if condition can also be written:

        if(SW2 == 0 && !SW2Pressed)

 *    The '!SW2Pressed' expression is read as 'not SW2Pressed' and is equivalent
 *    to SW2Pressed being false. Similarly, using the variable name by itself
 *    (eg. SW2Pressed) in a condition is equivalent to SW2Pressed being true.
 * 
 * 7. A pushbutton's logic state can also be defined as a word in a similar way
 *    to a variable (eg. the way SW2Pressed represents 1 or 0, or true or false)
 *    which can help to make the code more readable. Add the following lines to
 *    the 'Program constant definitions' section at the top of the code:
 
 #define pressed 0
 #define notPressed 1

 *    Now, instead of comparing the state of the button to 0 or 1, the button
 *    input can be compared with the named definition for 0 or 1, making the
 *    program more readable at the expense of hiding the actual switch value in
 *    the definition statement instead of making it obvious in the if structure.
 *    Try it in your code, and modify the SW3 reset button to work with the same
 *    pressed adn notPressed definitions.
 
        // Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 * 
 * Programming Activities
 The program activities were completed in the code.
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Let's use SW5 for the second player's pushbutton so that
 *    the two players can face each other from across the UBMP4 circuit board.
 *    Duplicate SW2Count and SW2Pressed to create SW5Count and SW5Pressed
 *    variables. Then, duplicate the required if condition structures and modify
 *    the variable names to represent the second player. LED D4 can still light
 *    if player 1 is the first to reach maxCount. Use LED D5 to show if the
 *    second palyer wins. Use a logical condition statement to reset the game
 *    by clearing the count and turning off the LEDs if either SW3 or SW4 is
 *    pressed.
 * 
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button will 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)
 * 
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just as the first
 *    program unitentionally did, because of the loop structure). Make a
 *    multifunction button that lights one LED when a button is pressed, and
 *    lights a second LED after the button is held for more that one second.
 * 
 * 4. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, but switch bounce can be an issue in a toggle button
 *    because the speed of a microcontroller lets it see each bounce as a new,
 *    separate event. Use a variable to count the number of times a pushbutton
 *    is pressed and display the count on the LEDs. Use a separate pushbutton
 *    to reset the count and turn off the LEDs so that the test can be repeated.
 *    To determine if your switches bounce, try pressing them at various speeds
 *    and using different amounts of force.
 * 
 * 5. Did your pushbuttons bounce? Can you think of a technique similar to the
 *    multi-function button that could be implemented to make your program
 *    ignore switch bounces. Multiple switch activations within a 50ms time span
 *    might indicate switch bounce and can be safely ignored.
 

 */
