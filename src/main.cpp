#include "main.hpp"
#include <vector>

int screenWidth;
int screenHeight;
int characterInitPositionX;
int characterInitPositionY;
int gameWindowWidth;
int gameWindowHeigh;
int numberOfSecondsAfterGameStart;

void initGlobalVariables() {
    screenWidth = sf::VideoMode::getDesktopMode().width;
    screenHeight = sf::VideoMode::getDesktopMode().height;

    characterInitPositionX = 0;
    characterInitPositionY = screenHeight-(screenHeight*0.3);

    gameWindowWidth = screenWidth/2;
    gameWindowHeigh = screenHeight;

    srand(time(NULL));

    numberOfSecondsAfterGameStart = 0;
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

    int numberOfCaughtItems = 0;
    int maxNumberOfFallingObjectsCanSpawn = 1;

    FallingObject hink = FallingObject("textures/fallingObjects/hink.png", rand() % (gameWindowWidth-10), 0);
    
    FallingObject fallingObjects[20];
    std::string texturePath = "textures/fallingObjects/hink.png";
    sf::Texture texture;
    texture.loadFromFile(texturePath);

    while (window.isOpen()) {
        time = clockForAnimation.getElapsedTime().asMilliseconds();
        clockForAnimation.restart();

        // event for closing window
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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

        if(character.sprite.getGlobalBounds().intersects(hink.sprite.getGlobalBounds())) {
            hink.spawn(gameWindowWidth); // respawn
            numberOfCaughtItems += 1;
            score.setScore(numberOfCaughtItems);
            // falling object.isFalling = false
        }
        else if (hink.sprite.getPosition().y > character.sprite.getPosition().y+100) {
            hink.spawn(gameWindowWidth);
        }
        else {  
            hink.fall(time);
        }

        // drawing objects
        window.clear();
        window.draw(background.sprite);
        window.draw(character.sprite);
        window.draw(hink.sprite);
        if (timeClock.getElapsedTime().asSeconds() > 1) {
            timeClock.restart();
            numberOfSecondsAfterGameStart += 1;
            if (maxNumberOfFallingObjectsCanSpawn < 5 
                && numberOfSecondsAfterGameStart%10) {
                maxNumberOfFallingObjectsCanSpawn += 1;
            }
        }
        window.draw(score.text);
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
