#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <array>
#include "Character.hpp"
#include "config.hpp"
#include "Background.hpp"
#include "FallingObject.hpp"
#include "Score.hpp"
#include "Text.hpp"

typedef std::array<FallingObject, MAX_FALLING_OBJECTS_IN_ARRAY> FallingObjectArrayType;


void closeWindowEventCheck(sf::RenderWindow &window);
void handleCharacterMovements(Character &character, float time);
void makeObjectsFall(FallingObjectArrayType &fallingObjects, float time);

void drawFallingObjects(sf::RenderWindow &window, FallingObjectArrayType &fallingObjects);

void disableObjectsWhichAreOutOfScreen(FallingObjectArrayType &fallingObjects, int maxHighOfGameWindow);
int checkIfCharacterCaughtObject(Character &character, 
                                 FallingObjectArrayType &fallingObjects,
                                 bool &chachaCought);
void enableNewFallingObjects(FallingObjectArrayType &fallingObjects, 
							 int number, 
							 int widthOfGameWindow, 
							 int minFallSpeed, 
							 int maxFallSpeed,
							 int probabilityOfUnfriendlyObjectSpawn,
							 std::map<std::string, sf::Texture> &texturesForFallingObjects,
							 bool sheepsFalling);


#endif//UTILS_HPP
