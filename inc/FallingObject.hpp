#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class FallingObject {
private:
    int posX;
    int posY;
    bool isFalling;
    int speed;
public:
    sf::Texture texture;
    sf::Sprite sprite;
    FallingObject(std::string texturePath, int posX, int posY);

    FallingObject();

    void fall(float time);

    void setTexture(sf::Texture texture);

    void spawn(int gameWindowWidth);

    void setIsFalling(bool val);

    int getIsFalling();

    FallingObject(const FallingObject &other);

    ~FallingObject();
};
