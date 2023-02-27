#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include <SFML/Graphics.hpp>
#include "config.hpp"

class Background {
private:
    sf::Texture texture;
public:
    sf::Sprite sprite;
    Background(std::string pathToTexture, float scaleX, float scaleY);
};
#endif//BACKGROUND_HPP
