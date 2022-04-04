#include <SFML/Graphics.hpp>
#include "config.hpp"


class Background {
public:
    sf::Texture bg;
    sf::Sprite sprite;
    Background() {
        bg.loadFromFile(BACK_GROUND_PATH);
        sprite.setTexture(bg);
        sprite.scale(1.85, 1.85);
    }
};