#include "Game.hpp"

/* @brief: periodically increments variables, which
 *         are responsible for game difficulty.
 */
void GameContext::periodicalChangeOfDifficulty() {
    // each X seconds probabilityOfUnfriendlyObjectSpawn decrements
    if (m_probabilityOfUnfriendlyObjectSpawn>2 
        && m_numberOfSecondsAfterGameStart%PERIOD_DECREMENT_PROBABILITY_OF_SPAWN_UNFRIEND_OBJECTS==0) {
        m_probabilityOfUnfriendlyObjectSpawn-=1;
    }

    // each 10 seconds increment min falling speed.  
    if (m_minFallingSpeed<MIN_FALLING_SPEED+4 && m_numberOfSecondsAfterGameStart%PERIOD_INCREMENT_MIN_FALLING_SPEED==0) {
        m_minFallingSpeed+=1;
    }

    // increment max falling speed each 15 seconds.
    if (m_maxFallingSpeed<MAX_FALLING_SPEED+3 && (m_numberOfSecondsAfterGameStart%(PERIOD_INCREMENT_MIN_FALLING_SPEED+5))==0) {
        m_maxFallingSpeed+=1;
    }

    // each 10 seconds max period between spawning new falling object decrements by 1. 
    if (m_maxPeriodBetweenSpawning > 1 && m_numberOfSecondsAfterGameStart%PERIOD_DECREMENT_MAX_SEC_BETWEEN_SPAWNING_OBJECTS==0) {
        m_maxPeriodBetweenSpawning-=1;
    }

    // incrementing number of objects can spawn once
    if (m_maxNumberOfFallingObjectsCanSpawn < MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE) {
        if (m_maxNumberOfFallingObjectsCanSpawn<5) {
            if (m_numberOfSecondsAfterGameStart%PERIOD_INCREMENT_MAX_NUM_OF_FALLING_OBJECTS==0) {
                m_maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
        else {
            // 5 seconds longer incremental of maxNumberOfFallingObjectsCanSpawn.
            if (m_numberOfSecondsAfterGameStart%(PERIOD_INCREMENT_MAX_NUM_OF_FALLING_OBJECTS+5)==0) {
                m_maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
    }

    // incrementing min number of objects can spawn each 25 seconds.
    if (m_numberOfSecondsAfterGameStart%PREDIOD_INCREMENT_NUM_OF_MIN_OBJECTS_CAN_SPAWN_SEC==0 
        && m_maxNumberOfFallingObjectsCanSpawn < MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE) {
        m_minNumberOfFallingObjectsCanSpawn+=1;
    }
}

void Game::restart()
{
    delete m_ctx;
    m_score.setScore(0);
    // disable all falling objects.
    for(FallingObjectArrayType::iterator iter = m_fallingObjectsArr.begin(),
                                         end = m_fallingObjectsArr.end();
                                         iter != end; ++iter)
    {
        iter->setIsFalling(false);
    }
    m_ctx = new GameContext;
}

void Game::loop()
{
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

    int caughtObjects = 0;
    while(m_window.isOpen()) {
        timeForAnimation = (float)clockForAnimation.getElapsedTime().asMicroseconds()/1000;
        clockForAnimation.restart();
        closeWindowEventCheck(m_window);

        if (m_ctx->gameRun() == false) {
            // checking if user has pressed the mouse btn.
            sf::Event event;
            while (m_window.pollEvent(event)) {
                // if user pressed btn -> restart game.
                if (event.type == sf::Event::MouseButtonPressed) {
                    restart();
                }
            }
            continue;
        }
        handleCharacterMovements(m_character, timeForAnimation);

        bool chachaCought = false;
        caughtObjects = checkIfCharacterCaughtObject(m_character, 
                                                     m_fallingObjectsArr,
                                                     chachaCought);
        if (chachaCought) {
            m_ctx->sheepsFalling(10);
        }

        if (caughtObjects == -1) {
            // -1 means, that user caught bomb.
            caughtBombSound.play();
            m_ctx->gameRun(false);
            goto draw;
        }
        else if (caughtObjects > 0) {
            caughtObjectSound.play();
        }
        m_ctx->numberOfCaughtItems(m_ctx->numberOfCaughtItems() + caughtObjects);
        m_score.setScore(m_ctx->numberOfCaughtItems());
                
        disableObjectsWhichAreOutOfScreen(m_fallingObjectsArr, m_ctx->gameWindowHeigh());
        makeObjectsFall(m_fallingObjectsArr, timeForAnimation);

        if (timeClock.getElapsedTime().asSeconds() > 1) {
            m_ctx->everySecondCall();
            if (m_ctx->numberOfSecondsAfterGameStart()%(rand()%m_ctx->maxPeriodBetweenSpawning()+m_ctx->minPeriodBetweenSpawning())==0) {
                enableNewFallingObjects(m_fallingObjectsArr, 
                                        rand()%m_ctx->maxNumberOfFallingObjectsCanSpawn()+m_ctx->minNumberOfFallingObjectsCanSpawn(), 
                                        m_ctx->gameWindowWidth(),
                                        m_ctx->minFallingSpeed(),
                                        m_ctx->maxFallingSpeed(),
                                        m_ctx->probabilityOfUnfriendlyObjectSpawn(),
                                        m_texturesForFallingObjects,
                                        m_ctx->sheepsFalling());
            }
            timeClock.restart();
        }

        // drawing objects
        draw:
        m_window.clear();
        m_window.draw(m_background.sprite);
        m_window.draw(m_score.text);
        drawFallingObjects(m_window, m_fallingObjectsArr);
        if (m_ctx->gameRun() == false) m_window.draw(m_gameoverText.text);
        m_window.draw(m_character.sprite);
        m_window.display();
    }
}
