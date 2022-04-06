#include "Background.hpp"

Background::Background(std::string pathToTexture, 
                      float scaleX, 
                      float scaleY) {
    texture.loadFromFile(pathToTexture);
    sprite.setTexture(texture);
    sprite.scale(scaleX, scaleY);
}
