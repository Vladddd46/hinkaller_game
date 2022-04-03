#include "main.hpp"

int screenWidth;
int screenHeight;

void initGlobalVariables() {
    screenWidth = sf::VideoMode::getDesktopMode().width;
    screenHeight = sf::VideoMode::getDesktopMode().height;
}

void printGlobalVariables() {
    std::cout << "screenWidth=" << screenWidth << std::endl;
    std::cout << "screenHeight=" << screenHeight << std::endl;
}


/* Loads character textures.
 * 
 * return:
 *      map<type_of_texture, vector<Texture>>
 */
std::map<std::string, std::vector<sf::Texture> > loadCharacterTextures() {
    std::map<std::string, std::vector<sf::Texture> > textures;

    std::vector<sf::Texture> runForwardTextures;
    for(int i=0;i<9;i++) {
        sf::Texture runForward;
        runForward.loadFromFile("./textures/character/Run__00"+std::to_string(i)+".png");
        runForwardTextures.push_back(runForward);
    }
    textures["runForward"]=runForwardTextures;

    std::vector<sf::Texture> runBackTextures;
    for(int i=0;i<9;i++) {
        sf::Texture runBack;
        runBack.loadFromFile("./textures/character/Runback__00"+std::to_string(i)+".png");
        runBackTextures.push_back(runBack);
    }
    textures["runBack"]=runBackTextures;

    std::vector<sf::Texture> idleTextures;
    sf::Texture idle;
    idle.loadFromFile("./textures/character/Idle__000.png");
    idleTextures.push_back(idle);
    textures["idle"]=idleTextures;

    std::vector<sf::Texture> idleBackTextures;
    sf::Texture idleback;
    idleback.loadFromFile("./textures/character/Idleback__000.png");
    idleBackTextures.push_back(idleback);
    textures["idleback"]=idleBackTextures;

    return textures;
}



class Character {
private:
    sf::Sprite sprite;
    std::map<std::string, std::vector<sf::Texture> > textures;
public:

    Character() {
        textures = loadCharacterTextures();
        sprite.setTexture(textures["idle"][0]);
        sprite.setPosition(0, 300);
        sprite.scale(0.2, 0.2);
    }

};

int main() {
    initGlobalVariables();
    printGlobalVariables();

    sf::RenderWindow window(sf::VideoMode(screenWidth/2, screenHeight), "Rocking");
    std::map<std::string, std::vector<sf::Texture> > rf = loadCharacterTextures();    
    


    sf::Sprite characterSprite;
    characterSprite.setTexture(rf["idle"][0]);
    characterSprite.setPosition(0, 650);
    characterSprite.scale(0.2, 0.2);

    bool leftIdle = true;



    float currentFrame;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            characterSprite.move(-1,0);
            currentFrame += 0.04;
            if (currentFrame > 6) currentFrame -= 6;
            characterSprite.setTexture(rf["runBack"][int(currentFrame)]);
            leftIdle = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            characterSprite.move(1,0);
        
            currentFrame += 0.04;
            if (currentFrame > 6) currentFrame -= 6;
            leftIdle = false;

            characterSprite.setTexture(rf["runForward"][int(currentFrame)]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            // characterSprite.move(0,-0.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            // characterSprite.move(0,0.1);
        }


        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (!leftIdle)
                characterSprite.setTexture(rf["idle"][0]);
            else
                characterSprite.setTexture(rf["idleback"][0]);
        }



        window.clear();
        window.draw(characterSprite);
        window.display();
    }

    return 0;
}
