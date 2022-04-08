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


inline void initGlobalVariables() {
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

    probabilityOfUnfriendlyObjectSpawn = PERCENT_OF_UNFRIENDLY_OBJECTS;
    gameRun = true;
}


inline void restartGame(Score &score, FallingObject fallingObjectsArr[]) {
    score.setScore(0);
    initGlobalVariables();

    // disable all falling objects.
    for (int i=0; i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        fallingObjectsArr[i].setIsFalling(false);
    }
}

/* @brief: periodically increments variables, which
 *         are responsible for game difficulty.
 */
void periodicalChangeOfDifficulty() {
    // each X seconds probabilityOfUnfriendlyObjectSpawn decrements
    if (probabilityOfUnfriendlyObjectSpawn>2 
        && numberOfSecondsAfterGameStart%PERIOD_DECREMENT_PROBABILITY_OF_SPAWN_UNFRIEND_OBJECTS==0) {
        probabilityOfUnfriendlyObjectSpawn-=1;
    }

    // each 10 seconds increment min falling speed.  
    if (minFallingSpeed<MIN_FALLING_SPEED+4 && numberOfSecondsAfterGameStart%PERIOD_INCREMENT_MIN_FALLING_SPEED==0) {
        minFallingSpeed+=1;
    }

    // increment max falling speed each 15 seconds.
    if (maxFallingSpeed<MAX_FALLING_SPEED+3 && (numberOfSecondsAfterGameStart%(PERIOD_INCREMENT_MIN_FALLING_SPEED+5))==0) {
        maxFallingSpeed+=1;
    }

    // each 10 seconds max period between spawning new falling object decrements by 1. 
    if (maxPeriodBetweenSpawning > 1 && numberOfSecondsAfterGameStart%PERIOD_DECREMENT_MAX_SEC_BETWEEN_SPAWNING_OBJECTS==0) {
        maxPeriodBetweenSpawning-=1;
    }

    // incrementing number of objects can spawn once
    if (maxNumberOfFallingObjectsCanSpawn < MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE) {
        if (maxNumberOfFallingObjectsCanSpawn<5) {
            if (numberOfSecondsAfterGameStart%PERIOD_INCREMENT_MAX_NUM_OF_FALLING_OBJECTS==0) {
                maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
        else {
            // 5 seconds longer incremental of maxNumberOfFallingObjectsCanSpawn.
            if (numberOfSecondsAfterGameStart%(PERIOD_INCREMENT_MAX_NUM_OF_FALLING_OBJECTS+5)==0) {
                maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
    }

    // incrementing min number of objects can spawn each 25 seconds.
    if (numberOfSecondsAfterGameStart%PREDIOD_INCREMENT_NUM_OF_MIN_OBJECTS_CAN_SPAWN_SEC==0 
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
               FallingObject fallingObjectsArr[],
               Text &gameoverText) {
    sf::Clock timeClock;
    timeClock.restart();

    sf::Clock clockForAnimation;
    float timeForAnimation;

    sf::SoundBuffer bufferForCaughtObjectSound;
    bufferForCaughtObjectSound.loadFromFile(CAUGHT_FRIENDLY_OBJECT_SOUND);
    sf::Sound caughtObjectSound(bufferForCaughtObjectSound);

    sf::SoundBuffer bufferForGameOverSound;
    bufferForGameOverSound.loadFromFile(GAME_OVER_SOUND);
    sf::Sound caughtBombSound(bufferForGameOverSound);

    while(window.isOpen()) {
        timeForAnimation = clockForAnimation.getElapsedTime().asMilliseconds();
        clockForAnimation.restart();
        closeWindowEventCheck(window);
        if (gameRun == false) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    restartGame(score, fallingObjectsArr);
                }
            }
            continue;
        }
        handleCharacterMovements(character, timeForAnimation);
        int caughtObjects = checkIfCharacterCaughtObject(character, 
                                                         fallingObjectsArr);
        if (caughtObjects == -1) {
            // -1 means, that user caught bomb.
            caughtBombSound.play();
            gameRun = false;
            goto draw;
        }
        else if (caughtObjects > 0) {
            caughtObjectSound.play();
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
        draw:
        window.clear();
        window.draw(background.sprite);
        window.draw(character.sprite);
        window.draw(score.text);
        drawFallingObjects(window, fallingObjectsArr);
        if (gameRun == false) window.draw(gameoverText.text);
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
    Background background = Background(BACK_GROUND_PATH, 1.85, 1.85);   
    Score score = Score(SCORE_FONT_PATH, 
                        sf::Color::Black, 
                        (gameWindowWidth)-(gameWindowWidth/2) - 55, 
                        0);
    Text gameoverText = Text("Game Over", 
                             SCORE_FONT_PATH, 
                             sf::Color::Black,
                             (gameWindowWidth)-(gameWindowWidth/2) - 90, 
                             gameWindowHeigh/3);

    std::map<std::string, sf::Texture> texturesForFallingObjects = loadFallingObjectTextures();
    FallingObject fallingObjectsArr[MAX_FALLING_OBJECTS_IN_ARRAY];

    // background music
    sf::Music mainMusic;
    mainMusic.openFromFile(BACKGROUND_MUSIC);
    mainMusic.setVolume(50.f);
    mainMusic.setLoop(true);
    mainMusic.play();

    game_loop(window, 
              character, 
              background, 
              score, 
              texturesForFallingObjects,
              fallingObjectsArr,
              gameoverText);
    return 0;
}
