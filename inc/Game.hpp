#ifndef GAME_HPP
#define GAME_HPP
#include "Utils.hpp"

struct GameContext
{

GameContext()
	: m_screenWidth{(int)sf::VideoMode::getDesktopMode().width},
	  m_screenHeight{(int)sf::VideoMode::getDesktopMode().height},
	  m_gameWindowWidth{m_screenWidth/2},
	  m_gameWindowHeigh{m_screenHeight},
	  m_characterInitPositionX{0},
	  m_characterInitPositionY{static_cast<int>(m_screenHeight*0.7)},
	  m_numberOfSecondsAfterGameStart{0},
	  m_numberOfCaughtItems{0},
	  m_maxNumberOfFallingObjectsCanSpawn{1},
	  m_minNumberOfFallingObjectsCanSpawn{1},
	  m_maxPeriodBetweenSpawning{3},
	  m_minPeriodBetweenSpawning{1},
	  m_maxFallingSpeed{MAX_FALLING_SPEED},
	  m_minFallingSpeed{MIN_FALLING_SPEED},
	  m_probabilityOfUnfriendlyObjectSpawn{PERCENT_OF_UNFRIENDLY_OBJECTS},
	  m_sheepsFalling{0},
	  m_gameRun{true}
{ srand(time(NULL)); }

~GameContext()
{}

void periodicalChangeOfDifficulty();

// function, which is called every second.
void everySecondCall() {
    m_numberOfSecondsAfterGameStart += 1;
    periodicalChangeOfDifficulty();

    if (m_sheepsFalling > 0) {
        m_sheepsFalling -= 1;
    }
}

int screenWidth() const
{ return m_screenWidth; }

int screenHeight() const
{ return m_screenHeight; }

int gameWindowWidth() const
{ return m_gameWindowWidth; }

int gameWindowHeigh() const
{ return m_gameWindowHeigh; }

int characterInitPositionX() const
{ return m_characterInitPositionX; }

int characterInitPositionY() const
{ return m_characterInitPositionY; }

int numberOfSecondsAfterGameStart() const
{ return m_numberOfSecondsAfterGameStart; }

int numberOfCaughtItems() const
{ return m_numberOfCaughtItems; }
 
void numberOfCaughtItems(int value)
{ m_numberOfCaughtItems = value; }

int maxNumberOfFallingObjectsCanSpawn() const
{ return m_maxNumberOfFallingObjectsCanSpawn; }

int minNumberOfFallingObjectsCanSpawn() const
{ return m_minNumberOfFallingObjectsCanSpawn; }

int maxPeriodBetweenSpawning() const
{ return m_maxPeriodBetweenSpawning; }

int minPeriodBetweenSpawning() const
{ return m_minPeriodBetweenSpawning; }

int maxFallingSpeed() const
{ return m_maxFallingSpeed; }

int minFallingSpeed() const
{ return m_minFallingSpeed; }

int probabilityOfUnfriendlyObjectSpawn() const
{ return m_probabilityOfUnfriendlyObjectSpawn; }

int sheepsFalling() const
{ return m_sheepsFalling; }

void sheepsFalling(int value)
{ m_sheepsFalling = value; }

bool gameRun() const
{ return m_gameRun; }

void gameRun(bool value)
{ m_gameRun = value; }

private:
	// Height/Width of computer screen
	int m_screenWidth;
	int m_screenHeight;

	// Height/Width of game screen
	int m_gameWindowWidth;
	int m_gameWindowHeigh;

	// Position X,Y where character spawns.
	int m_characterInitPositionX;
	int m_characterInitPositionY;
 
	int m_numberOfSecondsAfterGameStart; // game timer
	int m_numberOfCaughtItems; // score

	// Periodical settings.
	int m_maxNumberOfFallingObjectsCanSpawn;
	int m_minNumberOfFallingObjectsCanSpawn;
	int m_maxPeriodBetweenSpawning;
	int m_minPeriodBetweenSpawning;

	// between 1 and 4 is noraml. 5 is too fast.
	int m_maxFallingSpeed;
	int m_minFallingSpeed;

	// if 2 => propapility=1/2;3=>1/3;4=>1/4...x=>1/x 
	int m_probabilityOfUnfriendlyObjectSpawn;

	// counter, that means number of seconds sheeps will fall.
	int m_sheepsFalling;

	bool m_gameRun;
};

struct Game
{
	Game()
    : m_ctx{new GameContext},
      m_window{sf::VideoMode(m_ctx->gameWindowWidth(),
                             m_ctx->screenHeight()), 
                             GAME_NAME},
      m_character{m_ctx->characterInitPositionX(),
                  m_ctx->characterInitPositionY(),
                  static_cast<float>(m_ctx->gameWindowWidth())},
      m_background{BACK_GROUND_PATH, 1.85, 1.85},
      m_score{SCORE_FONT_PATH,
              sf::Color::Black,
              (m_ctx->gameWindowWidth())-(m_ctx->gameWindowWidth()/2) - 55,
              0},
      m_gameoverText{"Game Over", 
                      SCORE_FONT_PATH,
                      sf::Color::Black,
                      (m_ctx->gameWindowWidth())-(m_ctx->gameWindowWidth()/2) - 90, 
                      m_ctx->gameWindowHeigh()/3},
      m_texturesForFallingObjects{loadFallingObjectTextures()},
      m_fallingObjectsArr{}      
	{}

	~Game()
	{ delete m_ctx; }

	void loop();

	typedef std::map<std::string, sf::Texture> TextureMapType;

private:
	void restart();

private:
	GameContext 			*m_ctx;
	sf::RenderWindow 		m_window;
	Character 				m_character;	
	Background 				m_background;
	Score 					m_score;
	Text 					m_gameoverText;
	TextureMapType 			m_texturesForFallingObjects;
	FallingObjectArrayType 	m_fallingObjectsArr;
};

#endif//GAME_HPP
