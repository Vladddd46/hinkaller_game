#include "main.hpp"

// closes window if user exit window.
void closeWindowEventCheck(sf::RenderWindow &window) {
    // event for closing window
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


// Moves character depending on button user press.
void handleCharacterMovements(Character &character, float time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        character.move_left(time);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        character.move_right(time);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        character.stay();
    }
}


/* @brief: makes fall all objects, which have attribute isFalling==true
 * @param:
 *        fallingObjects - list of objects, which can fall.
 *        time - ...
 */
void makeObjectsFall(FallingObject fallingObjects[], float time) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY; i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            fallingObjects[i].fall(time);
        }
    }
}


// draws each falling object.
void drawFallingObjects(sf::RenderWindow &window, FallingObject fallingObjects[]) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            window.draw(fallingObjects[i].sprite);
        }
    }
}

// Falling objects, which are out of screen become not falling.
// Property ifFalling in this objects is set false.
void disableObjectsWhichAreOutOfScreen(FallingObject fallingObjects[], int maxHighOfGameWindow) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].sprite.getPosition().y > maxHighOfGameWindow+100) {
            fallingObjects[i].setIsFalling(false);
        }
    }
}

// Checks whether user object and falling object intersects.
// returns number of intersections.
int checkIfCharacterCaughtObject(Character &character, FallingObject fallingObjects[]) {
    int caught = 0;
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if(character.sprite.getGlobalBounds().intersects(fallingObjects[i].sprite.getGlobalBounds()) 
            && fallingObjects[i].getIsFalling()==true) {
            caught += 1;
            fallingObjects[i].setIsFalling(false);                
        }
    }
    return caught;
}


void enableNewFallingObjects(FallingObject fallingObjects[], int number, int widthOfGameWindow, int minFallSpeed, int maxFallSpeed) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].getIsFalling()==false && number > 0) {
            fallingObjects[i].setIsFalling(true);
            fallingObjects[i].spawn(rand()%(widthOfGameWindow-15), -10);
            fallingObjects[i].setSpeed(rand()%maxFallSpeed+minFallSpeed);
            number--;   
        }
    }
}

