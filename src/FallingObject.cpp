#include "FallingObject.hpp"


FallingObject::FallingObject(std::string texturePath, int posX, int posY) {
    sprite.setPosition(posX, posY);
    texture.loadFromFile(texturePath);
    if (texturePath!="") {
        sprite.setTexture(texture);
    }
    sprite.scale(0.3, 0.3);
    isFalling = false;
}

void FallingObject::fall(float time) {
    sprite.move(0,0.5*time);
}

void FallingObject::setTexture(sf::Texture texture) {
    this->texture = texture;
    sprite.setTexture(texture);
}

void FallingObject::setIsFalling(bool val) {
    this->isFalling=val;
}

int FallingObject::getIsFalling() {
    return this->isFalling;
}

void FallingObject::spawn(int gameWindowWidth) {
    this->sprite.setPosition(rand()%(gameWindowWidth-10), 0);
}

FallingObject::FallingObject() {
    // std::cout << "Constructor" << std::endl; // debug
    this->posX=0;
    this->posY=0;
    isFalling = false;
}

FallingObject::FallingObject(const FallingObject &other) {
    std::cout<<"Copy constructor"<<std::endl;
}

FallingObject::~FallingObject() {
    std::cout << "Destructor: " << this << std::endl;
}

