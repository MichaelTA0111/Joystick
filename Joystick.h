#ifndef JOYSTICK_H
#define JOYSTICK_H


/**
 * An enum for the possible directions for a joystick to be held in
 */
enum Direction { NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };


/**
 * A joystick which can be used to check the direction a joystick is held
 * Inspired by the Button class which can be found here:
 * https://github.com/drlim2u/button
 * @author - MichaelTA
 */
class Joystick
{
public:
    /**
     * Default constructor for the Joystick object
     */
    Joystick();
    
    /**
     * Constructor for the Joystick object
     * @param debounceDelay - The debounce delay (ms) as a long long
     * @param lowLimitX - The boundary (between 0 and 1) such that if it is
     *                    above the x position of the joystick, a left press
     *                    will be registered
     * @param highLimitX - The boundary (between 0 and 1) such that if it is
     *                     below the x position of the joystick, a right press
     *                     will be registered
     * @param lowLimitY - The boundary (between 0 and 1) such that if it is
     *                    above the y position of the joystick, an up press
     *                    will be registered
     * @param highLimitY - The boundary (between 0 and 1) such that if it is
     *                     below the y position of the joystick, a down press
     *                     will be registered
     */
    Joystick(long long debounceDelay, float lowLimitX, float highLimitX,
             float lowLimitY, float highLimitY);
    
    /**
     * Method to determine the direction held on the joystick after debouncing
     * @param xPos - The x position (between 0 and 1) of the joystick
     * @param yPos - The y position (between 0 and 1) of the joystick
     * @param runtime - The time the program has been running for (ms)
     * @return - The direction the joystick was held
     */
    Direction directionPressed(float xPos, float yPos, long long runtime);
    
private:
    /**
     * Private helper method to determine the direction held on the joystick at
     * a specific moment in time
     * @param xPos - The x position (between 0 and 1) of the joystick
     * @param yPos - The y position (between 0 and 1) of the joystick
     * @return - The direction the joystick was held
     */
    Direction calculateDirection(float xPos, float yPos);
    
    /**
     * Private helper method to debounce the direction input from the joystick
     * @param currentDirection - The current direction the joystick is being
     *                           held in
     * @param runtime - The time the program has been running for (ms)
     * @return - If the direction of the button has remained unchanged for the
     *           duration of the debounce delay
     */
    bool debounce(Direction currentDirection, long long runtime);
    
    long long prevDebounceTime;
    long long debounceDelay;
    float lowLimitX;
    float highLimitX;
    float lowLimitY;
    float highLimitY;
    Direction direction;
    Direction prevDirection;
    bool wasDebounced;
};


#endif
