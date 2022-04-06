#include "FallingObject.hpp"


FallingObject::FallingObject(std::string texturePath, int posX, int posY) {
    sprite.setPosition(posX, posY);
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.scale(0.3, 0.3);
    this->mustBeDrew=true;
}

void FallingObject::setDraw(bool val) {
    this->mustBeDrew=val;
}

bool FallingObject::getDraw() {
    return this->mustBeDrew;
}

void FallingObject::fall(float time) {
    sprite.move(0,0.5*time);
}

