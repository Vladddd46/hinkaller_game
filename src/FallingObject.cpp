#include "FallingObject.hpp"


FallingObject::FallingObject(std::string texturePath, int posX, int posY) {
    sprite.setPosition(posX, posY);
    texture.loadFromFile(texturePath);
    if (texturePath!="") {
        sprite.setTexture(texture);
    }
    sprite.scale(0.3, 0.3);
    isFalling = false;
    this->speed=rand()%4 + 3;
}

void FallingObject::fall(float time) {
    sprite.move(0,(this->speed*0.1)*time);
}

void FallingObject::setTexture(sf::Texture texture) {
    this->texture = texture;
    sprite.setTexture(this->texture);
    sprite.scale(0.3, 0.3);
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

FallingObject::FallingObject() {
    // std::cout << "Constructor" << std::endl; // debug
    this->posX=0;
    this->posY=0;
    this->isFalling = false;
    this->speed=rand()%4 + 3;
}

FallingObject::FallingObject(const FallingObject &other) {
    std::cout<<"Copy constructor"<<std::endl;
}

FallingObject::~FallingObject() {
    std::cout << "Destructor: " << this << std::endl;
}

