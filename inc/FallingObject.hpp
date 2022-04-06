#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class FallingObject {
private:
    bool mustBeDrew;
public:
    sf::Texture texture;
    sf::Sprite sprite;
    FallingObject(std::string texturePath, int posX, int posY);

    FallingObject();

    void setDraw(bool val);

    bool getDraw();

    void fall(float time);

    FallingObject(const FallingObject &other) {
        std::cout<<"copy"<<std::endl;
    }

    ~FallingObject() {
        std::cout << "Destructor: " << this << std::endl;
    }
};
