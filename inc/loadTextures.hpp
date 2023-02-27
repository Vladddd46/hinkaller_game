#ifndef LOAD_TEXTURES_HPP
#define LOAD_TEXTURES_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

std::map<std::string, std::vector<sf::Texture> > loadCharacterTextures();

std::map<std::string, sf::Texture> loadFallingObjectTextures();

#endif//LOAD_TEXTURES_HPP
