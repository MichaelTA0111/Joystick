# Joystick
A generic joystick class for use in C++ which can return the direction held, after debouncing, as one of five directions (NONE, LEFT, RIGHT, UP, DOWN).
Inspired by the Button class which can be found here: https://github.com/drlim2u/button

## Example
This code was written for use in the official online compiler for Mbed:

```C++
#include "mbed.h"
#include "Joystick.h"


int main()
{
    // Initialise the PuTTY terminal
    Serial pc = Serial(USBTX, USBRX, 9600);
    
    // Initialise analogue inputs for the joystick x and y positions
    AnalogIn joyX = AnalogIn(p18);
    AnalogIn joyY = AnalogIn(p19);
    
    // Initialise the timer
    Timer runtime;
    runtime.start();
    
    // Initialise the joystick
    Joystick js1 = Joystick();  // Default joystick
    // Joystick js2 = Joystick(50, 0.3, 0.7, 0.3, 0.7);  // Custom joystick
    
    while (true)
    {
        // Find the direction held
        Direction currentDirection = js1.directionPressed(joyX.read(),
                                                          joyY.read(),
                                                          runtime.read_ms());
        
        if (currentDirection == LEFT)
        {
            pc.printf("Left\n\r");
            // pc.printf("X: %.3f, Y: %.3f\n\r\n", joyX.read(), joyY.read());
        }
        else if (currentDirection == RIGHT)
        {
            pc.printf("Right\n\r");
            // pc.printf("X: %.3f, Y: %.3f\n\r\n", joyX.read(), joyY.read());
        }
        else if (currentDirection == UP)
        {
            pc.printf("Up\n\r");
            // pc.printf("X: %.3f, Y: %.3f\n\r\n", joyX.read(), joyY.read());
        }
        else if (currentDirection == DOWN)
        {
            pc.printf("Down\n\r");
            // pc.printf("X: %.3f, Y: %.3f\n\r\n", joyX.read(), joyY.read());
        }
    }
}

```
