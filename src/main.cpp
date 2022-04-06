#include "main.hpp"
#include <vector>

int screenWidth;
int screenHeight;
int charPosX;
int charPosY;

void initGlobalVariables() {
    screenWidth = sf::VideoMode::getDesktopMode().width;
    screenHeight = sf::VideoMode::getDesktopMode().height;
    charPosX = 0;
    charPosY = screenHeight-(screenHeight*0.3);
    srand(time(NULL));
}

void game_loop(sf::RenderWindow &window, Character &character) {
    Background bg = Background();

    FallingObject hink = FallingObject("textures/fallingObjects/hink.png", rand() % (screenWidth/2), 0);

    sf::Clock clockForSpawning;
    clockForSpawning.restart();

    sf::Clock clock;
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
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
            hink.setDraw(1);
            hink.sprite.setPosition(rand()%(screenWidth/2), 0);
        }
        else if ( hink.sprite.getPosition().y > character.sprite.getPosition().y+100){
            hink.sprite.setPosition(rand()%(screenWidth/2), 0);
        }
        else {  
            hink.fall(time);
        }
        window.clear();
        window.draw(bg.sprite);
        window.draw(character.sprite);
        window.draw(hink.sprite);
        if (clockForSpawning.getElapsedTime().asSeconds() > 1) {
            clockForSpawning.restart();
        }
        window.display();
    }
}



int main() {
    initGlobalVariables();
    sf::RenderWindow window(sf::VideoMode(screenWidth/2, screenHeight), 
                            GAME_NAME);    
    Character character = Character(charPosX,charPosY,screenWidth/2);    
    game_loop(window, character);
    return 0;
}
