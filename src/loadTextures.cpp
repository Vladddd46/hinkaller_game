#include "loadTextures.hpp"

/* @data: 04.03.2022
 * @author: vladddd46
 * @brief: 
 *          contains functions, which are responsible for loading textures.
 */


/* @data: 04.03.2022
 * @author: vladddd46
 * @brief:
 *        loads textures connected with character.
 * @description:
 *        textures["runForward"] => textures for running forward(right). (10 objects)
 *        textures["runBack"]    => textures for running back(left). (10 objects)
 *        textures["idle"]       => texture for idle state(turned right) (1 object)
 *        textures["idleback"]   => texture for idleback state(turned left) (1 object)
 * @return:
 *        type: map<string, vector<Textures>> 
 *        syntax: map<texture_type, vector<texture_objects>>
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

    std::vector<sf::Texture> dieTextures;
    for(int i=0;i<9;i++) {
        sf::Texture die;
        die.loadFromFile("./textures/character/Dead__00"+std::to_string(i)+".png");
        dieTextures.push_back(die);
    }
    textures["die"]=dieTextures;

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


/* @data: 06.03.2022
 * @author: vladddd46
 * @brief:
 *        loads textures for falling object
 * @description:
 *        textures["hinkalli"]  => texture of hinkalli
 *        textures["carrot"]    => texture of carrot.
 * @return:
 *        type: map<string, Texture> 
 *        syntax: map<texture_type, texture_objects>
 */
std::map<std::string, sf::Texture> loadFallingObjectTextures() {
    std::map<std::string, sf::Texture> textures;
    
    sf::Texture texture;
    if (!texture.loadFromFile("./textures/fallingObjects/hink.png")) {
        std::cout << "Can not load hink.png" << std::endl;
    };
    textures["hinkalli"] = texture;

    sf::Texture textureBomb;
    if (!textureBomb.loadFromFile("./textures/fallingObjects/bomb.png")) {
        std::cout << "Can not load bomb.png" << std::endl;
    };
    textures["bomb"] = textureBomb;

    sf::Texture textureChacha;
    if (!textureChacha.loadFromFile("./textures/fallingObjects/chacha.png")) {
        std::cout << "Can not load chacha.png" << std::endl;
    };
    textures["chacha"] = textureChacha;

    return textures;  
};










