#include "main.hpp"

// Height/Width of computer screen
int screenWidth;
int screenHeight;

// Height/Width of game screen
int gameWindowWidth;
int gameWindowHeigh;

// Position X,Y where character spawns.
int characterInitPositionX;
int characterInitPositionY;

int numberOfSecondsAfterGameStart; // game timer
int numberOfCaughtItems; // score

// Periodical settings.
int maxNumberOfFallingObjectsCanSpawn;
int minNumberOfFallingObjectsCanSpawn;
int maxPeriodBetweenSpawning;

// between 1 and 4 is noraml. 5 is too fast.
int maxFallingSpeed;
int minFallingSpeed;


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
    minNumberOfFallingObjectsCanSpawn = 1;
    maxPeriodBetweenSpawning = 3;
    minFallingSpeed=MIN_FALLING_SPEED;
    maxFallingSpeed=MAX_FALLING_SPEED;
}

/*
 * increments global variables which are responsible for difficulty during time.
 */
void periodicalChangeOfDifficulty() {
    // each 10 seconds increment max falling speed.  
    if (minFallingSpeed<MIN_FALLING_SPEED+4 && numberOfSecondsAfterGameStart%10==0) {
        minFallingSpeed+=1;
    }

    // increment max falling speed each 15 seconds.
    if (maxFallingSpeed<MAX_FALLING_SPEED+3 && numberOfSecondsAfterGameStart%15==0) {
        maxFallingSpeed+=1;
    }


    // each 10 seconds max period between spawning new falling object decrements by 1. 
    if (maxPeriodBetweenSpawning > 1 && numberOfSecondsAfterGameStart%10==0) {
        maxPeriodBetweenSpawning-=1;
    }

    // incrementing number of objects can spawn once
    if (maxNumberOfFallingObjectsCanSpawn < MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE) {
        if (maxNumberOfFallingObjectsCanSpawn<5) {
            if (numberOfSecondsAfterGameStart%INCREMENT_PERIOD_OF_MAX_NUM_OF_FALLING_OBJECTS_IN_SEC==0) {
                maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
        else {
            // 5 seconds longer incremental of maxNumberOfFallingObjectsCanSpawn.
            if (numberOfSecondsAfterGameStart%(INCREMENT_PERIOD_OF_MAX_NUM_OF_FALLING_OBJECTS_IN_SEC+5)==0) {
                maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
    }
    // incrementing min number of objects can spawn each 20 seconds.
    if  (numberOfSecondsAfterGameStart%20==0 
        && maxNumberOfFallingObjectsCanSpawn < MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE) {
        minNumberOfFallingObjectsCanSpawn+=1;
    }
    // TODO: write in log.
    // std::cout << "Debug: Max Number Of Falling Objects: " << maxNumberOfFallingObjectsCanSpawn << std::endl;
}

// this function is called every second.
void everySecondCall() {
    numberOfSecondsAfterGameStart += 1;
    periodicalChangeOfDifficulty();
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
    FallingObject fallingObjects[MAX_FALLING_OBJECTS_IN_ARRAY];

    while (window.isOpen()) {
        time = clockForAnimation.getElapsedTime().asMilliseconds();
        clockForAnimation.restart();
        closeWindowEventCheck(window);

        handleCharacterMovements(character, time);
        int caughtObjects = checkIfCharacterCaughtObject(character,fallingObjects);
        if (caughtObjects == -1) {
            score.setScore(-1);
            int c;
            std::cin >> c;
        }
        numberOfCaughtItems+= caughtObjects;
        score.setScore(numberOfCaughtItems);
        disableObjectsWhichAreOutOfScreen(fallingObjects, gameWindowHeigh);
        makeObjectsFall(fallingObjects, time);

        if (timeClock.getElapsedTime().asSeconds() > 1) {
            everySecondCall();
            if (numberOfSecondsAfterGameStart%(rand()%maxPeriodBetweenSpawning+1)==0) {
                enableNewFallingObjects(fallingObjects, 
                                        rand()%maxNumberOfFallingObjectsCanSpawn+minNumberOfFallingObjectsCanSpawn, 
                                        gameWindowWidth,
                                        minFallingSpeed,
                                        maxFallingSpeed, texturesForFallingObjects);
            }
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
