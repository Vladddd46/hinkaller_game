#include "main.hpp"
#include <vector>

int screenWidth;
int screenHeight;
int characterInitPositionX;
int characterInitPositionY;
int gameWindowWidth;
int gameWindowHeigh;
int numberOfSecondsAfterGameStart;
int numberOfCaughtItems;
int maxNumberOfFallingObjectsCanSpawn;

#define MAX_FALLING_OBJECTS 30

void initGlobalVariables() {
    screenWidth = sf::VideoMode::getDesktopMode().width;
    screenHeight = sf::VideoMode::getDesktopMode().height;

    characterInitPositionX = 0;
    characterInitPositionY = screenHeight-(screenHeight*0.3);

    gameWindowWidth = screenWidth/2;
    gameWindowHeigh = screenHeight;

    srand(time(NULL));

    numberOfSecondsAfterGameStart = 0;
    numberOfCaughtItems = 0;
    maxNumberOfFallingObjectsCanSpawn = 1;
}

// this function is called every second.
void everySecondCall() {
    numberOfSecondsAfterGameStart += 1;
    if (maxNumberOfFallingObjectsCanSpawn < 5 
        && numberOfSecondsAfterGameStart%10==0) {
        maxNumberOfFallingObjectsCanSpawn += 1;
    }
    std::cout << "Debug: Max Number Of Falling Objects: " << maxNumberOfFallingObjectsCanSpawn << std::endl;
}


/* @brief: makes fall all objects, which have attribute isFalling==true
 * @param:
 *        fallingObjects - list of objects, which can fall.
 *        time - ...
 */
void objectsFall(FallingObject fallingObjects[], float time) {
    for (int i=0;i<MAX_FALLING_OBJECTS; i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            fallingObjects[i].fall(time);
        }
    }
}


void drawFallingObjects(sf::RenderWindow &window, FallingObject fallingObjects[]) {
    for (int i=0;i<MAX_FALLING_OBJECTS;i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            window.draw(fallingObjects[i].sprite);
        }
    }
}

void checkIfCharacterCaughtObject(Character &character, FallingObject fallingObjects[]) {
    for (int i=0;i<MAX_FALLING_OBJECTS;i++) {
        if(character.sprite.getGlobalBounds().intersects(fallingObjects[i].sprite.getGlobalBounds()) 
            && fallingObjects[i].getIsFalling()==true) {
            numberOfCaughtItems += 1;
            fallingObjects[i].setIsFalling(false);                
            // score.setScore(numberOfCaughtItems);
        }
    }
}

void disableObjectsWhichAreOutOfScreen(FallingObject fallingObjects[]) {
    // out of screen
    for (int i=0;i<MAX_FALLING_OBJECTS;i++) {
        if (fallingObjects[i].sprite.getPosition().y > gameWindowHeigh+100) {
            fallingObjects[i].setIsFalling(false);
        }
    }
}


void enableNewFallingObjects(FallingObject fallingObjects[], int number) {
    for (int i=0;i<MAX_FALLING_OBJECTS;i++) {
        if (fallingObjects[i].getIsFalling()==false && number > 0) {
            fallingObjects[i].setIsFalling(true);
            fallingObjects[i].spawn(gameWindowWidth);
            number--;   
        }
    }
}


void game_loop(sf::RenderWindow &window, Character &character) {
    Background background = Background(BACK_GROUND_PATH, 1.85, 1.85);
    Score score = Score(SCORE_FONT_PATH, 
                        sf::Color::Black, 
                        (gameWindowWidth)-(gameWindowWidth/2) - 55, 
                        0);
    sf::Clock timeClock;
    timeClock.restart();
    
    sf::Clock clockForAnimation;
    float time;

    
    std::map<std::string, sf::Texture> texturesForFallingObjects = loadFallingObjectTextures();

    FallingObject fallingObjects[MAX_FALLING_OBJECTS];
    for (int i =0;i<MAX_FALLING_OBJECTS;i++) {
        fallingObjects[i].setTexture(texturesForFallingObjects["hinkalli"]);
    }

    while (window.isOpen()) {
        time = clockForAnimation.getElapsedTime().asMilliseconds();
        clockForAnimation.restart();
        closeWindowEventCheck(window);

        handleCharacterMovements(character, time);
        checkIfCharacterCaughtObject(character,fallingObjects);
        score.setScore(numberOfCaughtItems);
        disableObjectsWhichAreOutOfScreen(fallingObjects);
        objectsFall(fallingObjects, time);

        if (timeClock.getElapsedTime().asSeconds() > 1) {
            everySecondCall();
            enableNewFallingObjects(fallingObjects, rand()%maxNumberOfFallingObjectsCanSpawn+1);
            timeClock.restart();
        }

        // drawing objects
        window.clear();
        window.draw(background.sprite);
        window.draw(character.sprite);
        window.draw(score.text);
        drawFallingObjects(window, fallingObjects);
        window.display();
    }
}


int main() {
    initGlobalVariables();
    sf::RenderWindow window(sf::VideoMode(gameWindowWidth, screenHeight), 
                            GAME_NAME); 

    Character character = Character(characterInitPositionX,
                                    characterInitPositionY,
                                    gameWindowWidth);    
    game_loop(window, character);
    return 0;
}
