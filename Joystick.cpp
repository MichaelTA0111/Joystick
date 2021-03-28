#include "Joystick.h"


Joystick::Joystick()
{
    debounceDelay = 100;
    lowLimitX = 0.12;
    highLimitX = 0.88;
    lowLimitY = 0.12;
    highLimitY = 0.88;
    prevDebounceTime = 0;
    direction = NONE;
    prevDirection = NONE;
    wasDebounced = false;
}

Joystick::Joystick(long long debounceDelay, float lowLimitX, float highLimitX,
                   float lowLimitY, float highLimitY)
 : debounceDelay(debounceDelay), lowLimitX(lowLimitX), highLimitX(highLimitX),
   lowLimitY(lowLimitY), highLimitY(highLimitY)
{
    prevDebounceTime = 0;
    direction = NONE;
    prevDirection = NONE;
    wasDebounced = false;
}

Direction Joystick::directionPressed(float xPos, float yPos, long long runtime)
{
    Direction currentDirection = calculateDirection(xPos, yPos);
    
    if (!wasDebounced && debounce(currentDirection, runtime))
    {
        // Debounce if no previous input is being held after it was debounced
        direction = currentDirection;
        wasDebounced = true;
    }
    
    if (wasDebounced && direction != currentDirection)
    {
        // Return the direction held after release, after debouncing
        currentDirection = prevDirection;
        wasDebounced = false;
        return currentDirection;
    }
    
    return NONE;
}

Direction Joystick::calculateDirection(float xPos, float yPos)
{
    switch (direction)
    {
        // Test the direction that is currently held first to see if it is still
        // held. This helps for transitioning from a horizontal direction to a
        // vertical direction
        case LEFT:
            if (xPos < lowLimitX)
            {
                return LEFT;
            }
            break;
            
        case RIGHT:
            if (xPos > highLimitX)
            {
                return RIGHT;
            }
            break;
            
        case UP:
            if (yPos < lowLimitY)
            {
                return UP;
            }
            break;
            
        case DOWN:
            if (yPos > highLimitY)
            {
                return DOWN;
            }
            break;
            
        default:
            break;
    }
    
    if (xPos < lowLimitX)
    {
        return LEFT;
    }
    else if (xPos > highLimitX)
    {
        return RIGHT;
    }
    else if (yPos < lowLimitY)
    {
        return UP;
    }
    else if (yPos > highLimitY)
    {
        return DOWN;
    }
    
    return NONE;
}

bool Joystick::debounce(Direction currentDirection, long long runtime)
{
    switch (currentDirection)
    {
        case NONE:
            // If there is no direction being held, do not attempt to debounce
            prevDirection = NONE;
            return false;
            
        case LEFT:
            if (prevDirection != LEFT)
            {
                prevDebounceTime = runtime;
                prevDirection = LEFT;
            }
            break;
            
        case RIGHT:
            if (prevDirection != RIGHT)
            {
                prevDebounceTime = runtime;
                prevDirection = RIGHT;
            }
            break;
            
        case UP:
            if (prevDirection != UP)
            {
                prevDebounceTime = runtime;
                prevDirection = UP;
            }
            break;
            
        case DOWN:
            if (prevDirection != DOWN)
            {
                prevDebounceTime = runtime;
                prevDirection = DOWN;
            }
            break;
    }
    
    if ((runtime - prevDebounceTime) > debounceDelay)
    {
        return true;
    }
    else
    {
        return false;
    }
}
