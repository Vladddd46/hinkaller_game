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
int minPeriodBetweenSpawning;

// between 1 and 4 is noraml. 5 is too fast.
int maxFallingSpeed;
int minFallingSpeed;

// if 2 => propapility=1/2;3=>1/3;4=>1/4...x=>1/x 
int probabilityOfUnfriendlyObjectSpawn;

bool gameRun;


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
}


// function, which is called every second.
inline void everySecondCall() {
    numberOfSecondsAfterGameStart += 1;
    periodicalChangeOfDifficulty();
}


void game_loop(sf::RenderWindow &window, 
               Character &character, 
               Background &background, 
               Score &score,
               std::map<std::string, sf::Texture> &texturesForFallingObjects,
               FallingObject fallingObjectsArr[]) {
    sf::Clock timeClock;
    timeClock.restart();

    sf::Clock clockForAnimation;
    float timeForAnimation;

    while (window.isOpen()) {
        closeWindowEventCheck(window);
        if (gameRun == false) {
            continue;
        }
        timeForAnimation = clockForAnimation.getElapsedTime().asMilliseconds();
        clockForAnimation.restart();

        handleCharacterMovements(character, timeForAnimation);
        
        int caughtObjects = checkIfCharacterCaughtObject(character, fallingObjectsArr);
        if (caughtObjects == -1) {
            // -1 means, that user caught bomb.
            // TODO: game over logic.
            gameRun = false;
            continue;
        }
        numberOfCaughtItems += caughtObjects;
        score.setScore(numberOfCaughtItems);
        
        disableObjectsWhichAreOutOfScreen(fallingObjectsArr, gameWindowHeigh);
        makeObjectsFall(fallingObjectsArr, timeForAnimation);

        if (timeClock.getElapsedTime().asSeconds() > 1) {
            everySecondCall();
            if (numberOfSecondsAfterGameStart%(rand()%maxPeriodBetweenSpawning+minPeriodBetweenSpawning)==0) {
                enableNewFallingObjects(fallingObjectsArr, 
                                        rand()%maxNumberOfFallingObjectsCanSpawn+minNumberOfFallingObjectsCanSpawn, 
                                        gameWindowWidth,
                                        minFallingSpeed,
                                        maxFallingSpeed,
                                        probabilityOfUnfriendlyObjectSpawn,
                                        texturesForFallingObjects);
            }
            timeClock.restart();
        }

        // drawing objects
        window.clear();
        window.draw(background.sprite);
        window.draw(character.sprite);
        window.draw(score.text);
        drawFallingObjects(window, fallingObjectsArr);
        window.display();
    }
}


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
    minPeriodBetweenSpawning = 1;
    minFallingSpeed=MIN_FALLING_SPEED;
    maxFallingSpeed=MAX_FALLING_SPEED;

    probabilityOfUnfriendlyObjectSpawn = 2;
    gameRun = true;
}


int main() {
    initGlobalVariables();
    sf::RenderWindow window(sf::VideoMode(gameWindowWidth, screenHeight), 
                            GAME_NAME); 
    Character character = Character(characterInitPositionX,
                                    characterInitPositionY,
                                    gameWindowWidth); 
    Background background = Background(BACK_GROUND_PATH, 1.85, 1.85);   
    Score score = Score(SCORE_FONT_PATH, 
                        sf::Color::Black, 
                        (gameWindowWidth)-(gameWindowWidth/2) - 55, 
                        0);
    std::map<std::string, sf::Texture> texturesForFallingObjects = loadFallingObjectTextures();
    FallingObject fallingObjectsArr[MAX_FALLING_OBJECTS_IN_ARRAY];

    game_loop(window, 
              character, 
              background, 
              score, 
              texturesForFallingObjects,
              fallingObjectsArr);
    return 0;
}
