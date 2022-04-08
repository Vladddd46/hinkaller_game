#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "loadTextures.hpp"
#include "Character.hpp"
#include "config.hpp"
#include "Background.hpp"
#include "FallingObject.hpp"
#include "Score.hpp"
#include "Text.hpp"
#include <SFML/Audio.hpp>

void closeWindowEventCheck(sf::RenderWindow &window);
void handleCharacterMovements(Character &character, float time);
void makeObjectsFall(FallingObject fallingObjects[], float time);
void drawFallingObjects(sf::RenderWindow &window, FallingObject fallingObjects[]);
void disableObjectsWhichAreOutOfScreen(FallingObject fallingObjects[], int maxHighOfGameWindow);
int checkIfCharacterCaughtObject(Character &character, 
								 FallingObject fallingObjects[]);
void enableNewFallingObjects(FallingObject fallingObjects[], 
							 int number, 
							 int widthOfGameWindow, 
							 int minFallSpeed, 
							 int maxFallSpeed,
							 int probabilityOfUnfriendlyObjectSpawn,
							 std::map<std::string, sf::Texture> &texturesForFallingObjects);