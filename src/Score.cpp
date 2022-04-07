#include "Score.hpp"

Score::Score(std::string fontPath, 
             sf::Color color, 
             int posX, 
             int posY) {
    if (!MyFont.loadFromFile(fontPath)) {
        // debug msg.
        exit(1);
    }
    text.setString("score: 0");
    text.setFillColor(color);
    text.setCharacterSize(30);
    text.setFont(MyFont);
    text.setStyle(sf::Text::Bold);
    text.setPosition(posX,posY);
}

void Score::setScore(int score) {
    std::string scoreStr= std::to_string(score);
    text.setString("score: " + scoreStr);
};

void Score::setScore(std::string score) {
    text.setString(score);
};
