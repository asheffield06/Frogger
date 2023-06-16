#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"

class GameManager
{
private:
	// Makes a instance of the game
	static GameManager* m_sInstance;

	// Sets frame rate and timer
	const int FRAME_RATE = 120;
	Timer* m_tTimer;

	bool m_bQuit = false;
	Graphics* m_gGraphics;

	SDL_Event m_sdlEvent;

	// All textures
	Texture* m_tBackground;
	Texture* m_tPlayer;
	Texture* m_tObstacle;
	Texture* m_tObstacle2;
	Texture* m_tObstacle3;
	Texture* m_tObstacle4;
	Texture* m_tObstacle5;
	Texture* m_tObstacle6;
	Texture* m_tObstacle7;
	Texture* m_tObstacle8;
	Texture* m_tObstacle9;
	Texture* m_tLog1;
	Texture* m_tLog2;
	Texture* m_tLog3;
	Texture* m_tLog4;
	Texture* m_tLog5;
	Texture* m_tLog6;
	Texture* m_tLog7;
	Texture* m_tLog8;
	Texture* m_tLog9;
	Texture* m_tLog10;
	Texture* m_tLog11;
	Texture* m_tLog12;
	Texture* m_tLog13;
	Texture* m_tLily1;
	Texture* m_tLily2;
	Texture* m_tLily3;
	Texture* m_tLily4;
	Texture* m_tLife1;
	Texture* m_tLife2;
	Texture* m_tLife3;
	Texture* m_tTimeBar;
	Texture* m_tTitle;
	Texture* m_tStart;
	Texture* m_tScore;
	
	// Enum for game state
	enum GAME_STATE
	{
		MENU,
		PLAY,
	};

	// Used for switch statement
	GAME_STATE currentGameState = MENU;

public:
	// Public variables nessasary for game
	int lives = 3;
	int score = 0;

	// Instant of game
	static GameManager* Instance();
	static void Release();

	// Functions used in game loop
	void Run();
	void Death();

private:
	// Constructor and destructor
	GameManager();
	~GameManager();
};



#endif // !_GAMEMANAGER_H_