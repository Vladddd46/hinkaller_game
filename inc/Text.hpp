#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Text {
private:
    sf::Font MyFont;
public:
    sf::Text text;

    Text(std::string msg, std::string fontPath, sf::Color color, int posX, int posY);
    
    void setText(std::string msg);
};