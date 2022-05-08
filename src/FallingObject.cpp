#include "FallingObject.hpp"

FallingObject::FallingObject(std::string texturePath, int posX, int posY)
    : posX{posX}, posY{posY}, isFalling{false}, isFriendly{true}, speed{rand()%4 + 3}, isMagicObject{false}
{
    sprite.setPosition(posX, posY);
    texture.loadFromFile(texturePath);
    if (texturePath!="") {
        sprite.setTexture(texture);
    }
    sprite.scale(0.3, 0.3); // TODO: move scaling in constructor args.
}

void FallingObject::fall(float time) {
    sprite.move(0,(this->speed*0.1)*time);
}

void FallingObject::setTexture(sf::Texture texture) {
    this->texture = texture;
    sprite.setTexture(this->texture);
}

void FallingObject::setIsFalling(bool val) {
    this->isFalling=val;
}

int FallingObject::getIsFalling() {
    return this->isFalling;
}

void FallingObject::spawn(int x, int y) {
    this->sprite.setPosition(x, y);
}

void FallingObject::setSpeed(int speed) {
    this->speed = speed;
}

void FallingObject::setIsFriendly(bool val) {
    this->isFriendly = val;
}

bool FallingObject::getIsFriendly() {
    return this->isFriendly;
}

FallingObject::FallingObject()
    : posX{0}, posY{0}, isFalling{false}, isFriendly{true}, speed{rand()%4 + 3}, isMagicObject{false}
{
    sprite.scale(0.3, 0.3); // object scaling
}

FallingObject::FallingObject(const FallingObject &other) {
    // TODO: add debugger
    // std::cout<<"Copy constructor"<<std::endl;
}

FallingObject::~FallingObject() {
    // TODO: add debugger
    // std::cout << "Destructor: " << this << std::endl;
}


void FallingObject::setIsMagicObject(bool val) {
    this->isMagicObject = val;
}

bool FallingObject::getIsMagicObject() {
    return this->isMagicObject;
}
