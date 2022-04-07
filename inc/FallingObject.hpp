#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class FallingObject {
private:
    int posX;
    int posY;
    bool isFalling;
    bool isFriendly;
    int speed;
public:
    sf::Texture texture;
    sf::Sprite sprite;
    FallingObject(std::string texturePath, int posX, int posY);

    FallingObject();

    void fall(float time);

    void setTexture(sf::Texture texture);

    void spawn(int x, int y);

    void setIsFalling(bool val);

    void setSpeed(int speed);

    int getIsFalling();

    void setIsFriendly(bool val);

    bool getIsFriendly();
    
    FallingObject(const FallingObject &other);

    ~FallingObject();
};
