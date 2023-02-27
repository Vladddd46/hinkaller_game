#include "Game.hpp"

int main() {
    Game game;

    // background music
    sf::Music mainMusic;
    mainMusic.openFromFile(BACKGROUND_MUSIC);
    mainMusic.setVolume(50.f);
    mainMusic.setLoop(true);
    mainMusic.play();

    game.loop();
    exit(0);
}
