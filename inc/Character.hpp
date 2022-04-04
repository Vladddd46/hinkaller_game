#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "loadTextures.hpp"

class Character {
private:
    float currentFrame;
    bool turnsLeft;
    float rightBoarder;
public:
    sf::Sprite sprite;
    std::map<std::string, std::vector<sf::Texture> > textures;
    
    Character(int posX, int posY, float rightBoarder) {
        turnsLeft = true;
        textures = loadCharacterTextures();
        sprite.setTexture(textures["idle"][0]);
        sprite.setPosition(posX, posY);
        sprite.scale(0.2, 0.2);
        this->rightBoarder = rightBoarder;
    }

    void move_right() {
        if (sprite.getPosition().x < rightBoarder-(rightBoarder*0.09)) {
            sprite.move(2.5,0);
        }
        currentFrame += 0.1;
        if (currentFrame > 8) currentFrame -= 8;
        sprite.setTexture(textures["runForward"][int(currentFrame)]);
        turnsLeft = false;
    }

    void move_left() {
        if (sprite.getPosition().x > 0) {
            sprite.move(-2.5,0);
        }
        currentFrame += 0.1;
        if (currentFrame > 8) currentFrame -= 8;
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
