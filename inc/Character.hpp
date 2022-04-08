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
    bool isDead;
public:
    sf::Sprite sprite;
    std::map<std::string, std::vector<sf::Texture> > textures;
    Character(int posX, int posY, float rightBoarder);
    void move_right(float time);
    void move_left(float time);
    void die(float time);
    void setIsDead(bool val);
    bool getIsDead();
    void stay();
};
