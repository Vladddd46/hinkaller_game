#include "main.hpp"

int screenWidth;
int screenHeight;
int charPosX;
int charPosY;

void initGlobalVariables() {
    screenWidth = sf::VideoMode::getDesktopMode().width;
    screenHeight = sf::VideoMode::getDesktopMode().height;
    charPosX = 0;
    charPosY = screenHeight-(screenHeight*0.35);
}

void game_loop(sf::RenderWindow &window, Character &character) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.move_left();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.move_right();
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                 !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.stay();
        }

        window.clear();
        window.draw(character.sprite);
        window.display();
    }
}



int main() {
    initGlobalVariables();
    sf::RenderWindow window(sf::VideoMode(screenWidth/2, screenHeight), 
                            GAME_NAME);    
    Character character = Character(charPosX,charPosY);    
    game_loop(window, character);
    return 0;
}
