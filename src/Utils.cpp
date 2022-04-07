#include "main.hpp"

void closeWindowEventCheck(sf::RenderWindow &window) {
    // event for closing window
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


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