#include "Game.hpp"
#include <iostream>

int main() {
    try {
        Game game;

        // background music
        sf::Music mainMusic;
        mainMusic.openFromFile(BACKGROUND_MUSIC);
        mainMusic.setVolume(50.f);
        mainMusic.setLoop(true);
        mainMusic.play();

        game.loop();
    }
    catch(std::bad_alloc &err)
    {
        std::cerr << "EXCEPTION: There was caught " << err.what() << " exception. Exiting...\n";
        exit(1);
    }
    catch(...)
    {
        std::cerr << "EXCEPTION: There was caught unknown exception. Exiting...\n";
        exit(1);
    }
    exit(0);
}
