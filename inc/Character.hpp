#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "loadTextures.hpp"

class Character {
private:
    float currentFrame;
    bool turnsLeft;
    // int positionX;
    // int positionY;
public:
    sf::Sprite sprite;
    std::map<std::string, std::vector<sf::Texture> > textures;
    
    Character(int posX, int posY) {
        turnsLeft = true;
        textures = loadCharacterTextures();
        sprite.setTexture(textures["idle"][0]);
        sprite.setPosition(posX, posY);
        // positionX = posX;
        // positionY = posY;
        sprite.scale(0.2, 0.2);
    }

    void move_right() {
        sprite.move(1,0);
        currentFrame += 0.04;
        if (currentFrame > 6) currentFrame -= 6;
        sprite.setTexture(textures["runForward"][int(currentFrame)]);
        turnsLeft = false;
    }

    void move_left() {
        sprite.move(-1,0);
        currentFrame += 0.04;
        if (currentFrame > 6) currentFrame -= 6;
        sprite.setTexture(textures["runBack"][int(currentFrame)]);
        turnsLeft = true;   
    }

    void stay() {
        if (!turnsLeft)
            sprite.setTexture(textures["idle"][0]);
        else
            sprite.setTexture(textures["idleback"][0]);
    }
};
