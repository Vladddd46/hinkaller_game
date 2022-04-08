#include "Character.hpp"

#define CHARACTER_IMAGE_SCALE 0.2

Character::Character(int posX, int posY, float rightBoarder) {
    turnsLeft = true;
    textures = loadCharacterTextures();
    sprite.setTexture(textures["idle"][0]);
    sprite.setPosition(posX, posY);
    sprite.scale(CHARACTER_IMAGE_SCALE, CHARACTER_IMAGE_SCALE);
    this->rightBoarder = rightBoarder;
    this->isDead=false;
}

void Character::move_right(float time) {
    // std::cout << sprite.getPosition().x << std::endl;
    if (sprite.getPosition().x < rightBoarder-(rightBoarder*0.09)) {
        sprite.move(1*time,0);
    }
    currentFrame += 0.04*time;
    if (currentFrame >= 9) currentFrame -= 9;
    sprite.setTexture(textures["runForward"][int(currentFrame)]);
    turnsLeft = false;
}

void Character::move_left(float time) {
    // std::cout << sprite.getPosition().x << std::endl;
    if (sprite.getPosition().x > 0) {
        sprite.move(-1*time,0);
    }
    currentFrame += 0.04*time;
    if (currentFrame >= 9) currentFrame -= 9;
    sprite.setTexture(textures["runBack"][int(currentFrame)]);
    turnsLeft = true;   
}

void Character::die(float time) {
    // TODO: needed to write logic for die.
    // if (this->isDead==true) {
    //     sprite.setTexture(textures["die"][7]);
    // }
    // currentFrame += 0.04*time;
    // if (currentFrame >= 9) {
    //     currentFrame -= 9;
    //     this->isDead=true;
    // };
    // sprite.setTexture(textures["die"][int(5)]);
}

void Character::setIsDead(bool val) {
    this->isDead = val;
}

bool Character::getIsDead() {
    return this->isDead;
}


void Character::stay() {
    if (!turnsLeft)
        sprite.setTexture(textures["idle"][0]);
    else
        sprite.setTexture(textures["idleback"][0]);
}
