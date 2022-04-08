#include "Text.hpp"

Text::Text(std::string msg,
           std::string fontPath, 
           sf::Color color, 
           int posX, 
           int posY) {
    if (!MyFont.loadFromFile(fontPath)) {
        // TODO: debug msg should be written in log.
        exit(1);
    }
    text.setString(msg);
    text.setFillColor(color);
    text.setCharacterSize(30);
    text.setFont(MyFont);
    text.setStyle(sf::Text::Bold);
    text.setPosition(posX,posY);
}


void Text::setText(std::string msg) {
    text.setString(msg);
};
