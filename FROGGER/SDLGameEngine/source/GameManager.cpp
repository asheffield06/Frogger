#include "..\include\GameManager.h"
GameManager* GameManager::m_sInstance = NULL;


GameManager* GameManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new GameManager();
	}
	return m_sInstance;
}

void GameManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;

	Timer::Release();
}

void GameManager::Run()
{
	// Simple variables used to manipulate a test parts of code
	Vector2 vTranslation = Vector2(0, 0);
	bool frogInWater = false;
	bool spaceBar = false;
	int movementInt = 1;
	int iPlaceholder = 0;

	// Images for gameObjects that change in the update loop
	std::string frog = SDL_GetBasePath();
	frog.append("Assets/Frog.png");
	std::string frogJump = SDL_GetBasePath();
	frogJump.append("Assets/FrogJump.png");
	std::string scoreText = SDL_GetBasePath();
	scoreText.append("Assets/0.png");

	while (!m_bQuit)
	{
		// Updates timer
		m_tTimer->Update();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			if (m_sdlEvent.type == SDL_QUIT)
			{
				m_bQuit = true;
			}

			// For key presses
			if (m_sdlEvent.type == SDL_KEYDOWN) 
			{
				switch (m_sdlEvent.key.keysym.sym)
				{
				// Up Key
				case SDLK_UP:
					vTranslation.y = 40;
					vTranslation.x = 0;
					m_tPlayer->Rotation(0);
					m_tPlayer->changeImage(frogJump);
					break;
				// Down key
				case SDLK_DOWN:
					if (m_tPlayer->m_vPos.y < 560) {
						vTranslation.y = -40;
						vTranslation.x = 0;
					}
					m_tPlayer->Rotation(180);
					m_tPlayer->changeImage(frogJump);
					break;
				// Left key
				case SDLK_LEFT:
					if (m_tPlayer->m_vPos.x > 0)
					{
						vTranslation.x = -40;
						vTranslation.y = 0;
					}
					m_tPlayer->Rotation(270);
					m_tPlayer->changeImage(frogJump);
					break;
				// Right key 
				case SDLK_RIGHT:
					if (m_tPlayer->m_vPos.x < 480)
					{
						vTranslation.x = 40;
						vTranslation.y = 0;
					}
					m_tPlayer->Rotation(90);
					m_tPlayer->changeImage(frogJump);
					break;
				// Space key
				case SDLK_SPACE:
					spaceBar = true;
					break;
				default:
					break;
				}
			}

			// When key is not being pressed
			if (m_sdlEvent.type == SDL_KEYUP)
			{
				switch (m_sdlEvent.key.keysym.sym)
				{
				// Up key
				case SDLK_UP:
					vTranslation.y = 0;
					m_tPlayer->changeImage(frog);
					break;
				// Down key
				case SDLK_DOWN:
					vTranslation.y = 0;
					m_tPlayer->changeImage(frog);
					break;
				// Left Key
				case SDLK_LEFT:
					vTranslation.x = 0;
					m_tPlayer->changeImage(frog);
					break;
				// Right key
				case SDLK_RIGHT:
					vTranslation.x = 0;
					m_tPlayer->changeImage(frog);
					break;
				// Space Key
				case SDLK_SPACE:
					spaceBar = false;
					break;
				default:
					break;
				}
			}
		}

		// Updates the game
		if (m_tTimer->DeltaTime() >= 10.0f / FRAME_RATE)
		{
			// Switch statement to tell if in menu or not
			switch (currentGameState)
			{
			// In menu
			case MENU:
			{
				// If spacebar is pressed start game
				if (spaceBar) 
				{
					currentGameState = PLAY;
				}

				// Renders nessasary objects for the menu
				m_tBackground->Render();
				m_tTitle->Render();
				m_tStart->Render();
				m_gGraphics->Render();
				m_tTimer->Reset();
				break;
			}
			// In play
			case PLAY:
			{
				// Clears the previous frame 
				m_gGraphics->ClearBackBuffer();

				// Creates a array of textures for the Lillies
				Texture* Lilies[4] = { m_tLily1, m_tLily2, m_tLily3, m_tLily4 };
				// For loop lopping through each lily
				for (int i = 0; i < sizeof(Lilies) / sizeof(Lilies[0]); i++)
				{
					// Collision Detection
					if (((m_tPlayer->m_vPos.x >= Lilies[i]->m_vPos.x - 20) && (m_tPlayer->m_vPos.y == 40)) &&
						((m_tPlayer->m_vPos.x <= Lilies[i]->m_vPos.x + Lilies[i]->m_iWidth) && (m_tPlayer->m_vPos.y == 40)))
					{
						// Sets the frog at the start point and changes the lily so its full
						Lilies[i]->m_iHeight = 40;
						Lilies[i]->m_iWidth = 40;
						Lilies[i]->m_vPos = Vector2(Lilies[i]->m_vPos.x - 5, Lilies[i]->m_vPos.y - 5);
						Lilies[i]->changeImage(frog);
						Lilies[i]->m_iSpeed = 10;
						score = score + 1;
						lives = lives + 1;
					}
				}
				// Checks to see if the lillies are all full
				if ((m_tLily1->m_iSpeed == 10) && (m_tLily2->m_iSpeed == 10) && (m_tLily3->m_iSpeed == 10) && (m_tLily4->m_iSpeed == 10))
				{
					// Resets all the lillies back to empty 
					for (int i = 0; i < sizeof(Lilies) / sizeof(Lilies[0]); i++) 
					{
						Lilies[i]->m_iSpeed = 1;
						std::string Lily = SDL_GetBasePath();
						Lily.append("Assets/Lily.png");
						Lilies[i]->changeImage(Lily);
					}
				}

				// Creates a array for all the vechiles/obstacles
				Texture* Obstacles[9] = { m_tObstacle ,m_tObstacle2, m_tObstacle3 ,m_tObstacle4, m_tObstacle5, m_tObstacle6, m_tObstacle7, m_tObstacle8, m_tObstacle9 };
				// Loops through each of the vechiles
				for (int i = 0; i < sizeof(Obstacles) / sizeof(Obstacles[0]); i++)
				{
					// Gets the position of the vechile and makes it move across the screen
					Vector2 pos = Obstacles[i]->m_vPos;
					Obstacles[i]->m_vPos = Vector2(Obstacles[i]->m_vPos.x + (5 * Obstacles[i]->m_iDirection), Obstacles[i]->m_vPos.y);

					// Finds out which direction the vechile is moving and whether its moved off screen
					if (Obstacles[i]->m_iDirection == -1 && Obstacles[i]->m_vPos.x < 0)
					{
						// Sets vechiles position back to the start with a small amount of variance so they arnt in a pattern
						int rndValue = rand() % 4 + 1;
						Obstacles[i]->m_vPos = Vector2(480 + (40 * rndValue), Obstacles[i]->m_vPos.y);
					}
					if (Obstacles[i]->m_iDirection == 1 && Obstacles[i]->m_vPos.x > 520)
					{
						// Sets vechiles position back to the start with a small amount of variance so they arnt in a pattern
						int rndValue = rand() % 4 + 1;
						Obstacles[i]->m_vPos = Vector2(0 - (40 * rndValue), Obstacles[i]->m_vPos.y);
					}
					// Collision Detection
					if (((m_tPlayer->m_vPos.x >= Obstacles[i]->m_vPos.x - 20) && (m_tPlayer->m_vPos.y == Obstacles[i]->m_vPos.y)) &&
						((m_tPlayer->m_vPos.x <= Obstacles[i]->m_vPos.x + Obstacles[i]->m_iWidth) && (m_tPlayer->m_vPos.y == Obstacles[i]->m_vPos.y)))
					{
						// Collision means the player has died so calls death function
						Death();
					}

				}

				// Creates a array of textures for each log
				Texture* Logs[13] = { m_tLog1, m_tLog2, m_tLog3, m_tLog4, m_tLog5, m_tLog6, m_tLog7, m_tLog8, m_tLog9, m_tLog10, m_tLog11, m_tLog12, m_tLog13 };

				// Checks to see if the player is at a point where its passed the road and at water
				if (m_tPlayer->m_vPos.y <= 240) {
					frogInWater = true;
				}
				// Loops through each log
				for (int i = 0; i < sizeof(Logs) / sizeof(Logs[0]); i++)
				{
					// Makes the logs go across the screen
					Logs[i]->m_vPos = Vector2(Logs[i]->m_vPos.x + ((5 + Logs[i]->m_iSpeed) * Logs[i]->m_iDirection), Logs[i]->m_vPos.y);

					// Finds out which direction the log is moving and whether its moved off screen
					if (Logs[i]->m_iDirection == -1 && Logs[i]->m_vPos.x < -160)
					{
						// Sets logs position back to the start with a small amount of variance so they arnt in a pattern
						int rndValue = rand() % 4 + 1;
						Logs[i]->m_vPos = Vector2(480 + (40 * rndValue), Logs[i]->m_vPos.y);
					}
					if (Logs[i]->m_iDirection == 1 && Logs[i]->m_vPos.x > 600)
					{
						// Sets logs position back to the start with a small amount of variance so they arnt in a pattern
						int rndValue = rand() % 4 + 1;
						Logs[i]->m_vPos = Vector2(-160 - (40 * rndValue), Logs[i]->m_vPos.y);
					}

					// Checks whether or not the player is on the log
					if ((Logs[i]->m_iDirection == -1) && ((m_tPlayer->m_vPos.x >= Logs[i]->m_vPos.x - 10) && (m_tPlayer->m_vPos.y == Logs[i]->m_vPos.y)) &&
						((m_tPlayer->m_vPos.x <= Logs[i]->m_vPos.x + Logs[i]->m_iWidth - 30)))
					{
						// Makes the player move as the log moves
						m_tPlayer->m_vPos = Vector2(m_tPlayer->m_vPos.x + ((5 + Logs[i]->m_iSpeed) * Logs[i]->m_iDirection), m_tPlayer->m_vPos.y);

						// Changes the booleon so that the player will not die in water
						frogInWater = false;
					}
					if ((Logs[i]->m_iDirection == 1) && ((m_tPlayer->m_vPos.x >= Logs[i]->m_vPos.x - 10) && (m_tPlayer->m_vPos.y == Logs[i]->m_vPos.y)) &&
						((m_tPlayer->m_vPos.x <= Logs[i]->m_vPos.x + Logs[i]->m_iWidth - 30) && (m_tPlayer->m_vPos.y == Logs[i]->m_vPos.y)))
					{
						// Makes the player move as the log moves
						m_tPlayer->m_vPos = Vector2(m_tPlayer->m_vPos.x + ((5 + Logs[i]->m_iSpeed) * Logs[i]->m_iDirection), m_tPlayer->m_vPos.y);

						// Changes the booleon so that the player will not die in water
						frogInWater = false;
					}
				}

				// Moves the player every other frame so that it isnt too fast
				movementInt = movementInt * -1;
				if (movementInt > 0)
				{
					// Changes player position
					m_tPlayer->TranslatePos(vTranslation.x, vTranslation.y);

					// Increases the timer
					m_tTimeBar->m_iWidth = m_tTimeBar->m_iWidth - 2;
				}

				// Kills the player if they are in water
				if (frogInWater == true) {
					Death();
					frogInWater = false;
				}

				// If the timer runs out of time it kills the player
				if (m_tTimeBar->m_iWidth < 2)
				{
					Death();
				}

				// Changes the scores value 
				std::string str = std::to_string(score);
				scoreText = SDL_GetBasePath();
				scoreText.append("Assets/");
				scoreText.append(str);
				scoreText.append(".png");
				m_tScore->changeImage(scoreText);

				// All things to render in a specific order so that overlaps dont happen where they shouldnt
				m_tBackground->Render();
				// Renders logs
				for (int i = 0; i < sizeof(Logs) / sizeof(Logs[0]); i++)
				{
					Logs[i]->Render();
				}
				// Renders player
				m_tPlayer->Render();
				// Renders vechiles
				for (int i = 0; i < sizeof(Obstacles) / sizeof(Obstacles[0]); i++)
				{
					Obstacles[i]->Render();
				}
				// Renders Lillies
				for (int i = 0; i < sizeof(Lilies) / sizeof(Lilies[0]); i++)
				{
					Lilies[i]->Render();
				}

				// Only renders the lives depending on the value of lives
				if (lives == 3)
				{
					m_tLife1->Render();
					m_tLife2->Render();
					m_tLife3->Render();
				}
				else if (lives == 2)
				{
					m_tLife1->Render();
					m_tLife2->Render();
				}
				else if (lives == 1)
				{
					m_tLife1->Render();
				}
				
				// Renders everything else
				m_tTimeBar->Render();
				m_tScore->Render();
				m_gGraphics->Render();
				m_tTimer->Reset();

				break;
			}
			}
			
		}
	}
}

void GameManager::Death()
{
	// Checks if the player has lives left
	if (lives > 0) 
	{
		// Removes a live and resets the timer and frog position
		lives = lives - 1;
		m_tPlayer->m_vPos = Vector2(240, 560);
		m_tTimeBar->m_iWidth = 300;
	}
	else 
	{
		// Resets all essential variables and returns to menu
		lives = 3;
		score = 0;
		m_tPlayer->m_vPos = Vector2(240, 560);
		m_tTimeBar->m_iWidth = 300;
		currentGameState = MENU;
	}
}

GameManager::GameManager()
{
	m_bQuit = false;
	m_gGraphics = Graphics::Instance();

	if (!Graphics::Initialised())
	{
		m_bQuit = true;
	}
	m_tTimer = Timer::Instance();


	// Sets up the default images and position and sizes of every texture in the game
	std::string sPath = SDL_GetBasePath();
	sPath.append("Assets/Frog.png");
	Vector2 vTempPos = Vector2(240, 560);
	m_tPlayer = new Texture(sPath, vTempPos, 40, 40, 0.0f, 1, 0);
	
	std::string sPath2 = SDL_GetBasePath();
	sPath2.append("Assets/Background.png");
	vTempPos = Vector2(0, 0);
	m_tBackground = new Texture(sPath2, vTempPos, 520, 600, 0.0f, 1, 0);

	std::string sPath3 = SDL_GetBasePath();
	sPath3.append("Assets/Car.png");
	vTempPos = Vector2(200, 480);
	m_tObstacle = new Texture(sPath3, vTempPos, 40, 40, 0.0f , -1, 0);

	vTempPos = Vector2(440, 480);
	m_tObstacle2 = new Texture(sPath3, vTempPos, 40, 40, 0.0f , -1, 0);

	vTempPos = Vector2(560, 320);
	m_tObstacle3 = new Texture(sPath3, vTempPos, 40, 40, 0.0f , -1, 0);

	vTempPos = Vector2(120, 320);
	m_tObstacle4 = new Texture(sPath3, vTempPos, 40, 40, 0.0f , -1, 0);

	std::string sPath4 = SDL_GetBasePath();
	sPath4.append("Assets/Lorry.png");
	vTempPos = Vector2(240, 400);
	m_tObstacle5 = new Texture(sPath4, vTempPos, 80, 40, 0.0f, -1, 0);

	std::string sPath5 = SDL_GetBasePath();
	sPath5.append("Assets/CarPink.png");
	vTempPos = Vector2(480, 440);
	m_tObstacle6 = new Texture(sPath5, vTempPos, 40, 40, 180.0f, 1, 0);

	vTempPos = Vector2(240, 440);
	m_tObstacle7 = new Texture(sPath5, vTempPos, 40, 40, 180.0f, 1, 0);

	std::string sPath6 = SDL_GetBasePath();
	sPath6.append("Assets/CarWhite.png");
	vTempPos = Vector2(520, 360);
	m_tObstacle8 = new Texture(sPath6, vTempPos, 40, 40, 180.0f, 1, 0);

	vTempPos = Vector2(80, 360);
	m_tObstacle9 = new Texture(sPath6, vTempPos, 40, 40, 180.0f, 1, 0);

	std::string sPath7 = SDL_GetBasePath();
	sPath7.append("Assets/LogShort.png");
	vTempPos = Vector2(240, 200);
	m_tLog1 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, -1, -1);

	vTempPos = Vector2(480, 200);
	m_tLog2 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, -1, -1);

	vTempPos = Vector2(0, 200);
	m_tLog3 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, -1, -1);

	std::string sPath8 = SDL_GetBasePath();
	sPath8.append("Assets/LogLong.png");
	vTempPos = Vector2(0, 240);
	m_tLog4 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, 1, 0);

	vTempPos = Vector2(280, 240);
	m_tLog5 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, 1, 0);

	vTempPos = Vector2(600, 240);
	m_tLog6 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, 1, 0);

	vTempPos = Vector2(280, 160);
	m_tLog7 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, -1, 2);

	vTempPos = Vector2(40, 160);
	m_tLog8 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, -1, 2);

	vTempPos = Vector2(0, 120);
	m_tLog9 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, 1, 0);

	vTempPos = Vector2(320, 120);
	m_tLog10 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, 1, 0);

	vTempPos = Vector2(600, 120);
	m_tLog11 = new Texture(sPath7, vTempPos, 120, 40, 0.0f, 1, 0);

	vTempPos = Vector2(360, 80);
	m_tLog12 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, -1, 0);

	vTempPos = Vector2(40, 80);
	m_tLog13 = new Texture(sPath8, vTempPos, 200, 40, 0.0f, -1, 0);

	std::string sPath9 = SDL_GetBasePath();
	sPath9.append("Assets/Lily.png");
	vTempPos = Vector2(65, 45);
	m_tLily1 = new Texture(sPath9, vTempPos, 30, 30, 0.0f, -1, 0);

	vTempPos = Vector2(185, 45);
	m_tLily2 = new Texture(sPath9, vTempPos, 30, 30, 0.0f, -1, 0);

	vTempPos = Vector2(305, 45);
	m_tLily3 = new Texture(sPath9, vTempPos, 30, 30, 0.0f, -1, 0);

	vTempPos = Vector2(425, 45);
	m_tLily4 = new Texture(sPath9, vTempPos, 30, 30, 0.0f, -1, 0);


	vTempPos = Vector2(10, 0);
	m_tLife1 = new Texture(sPath, vTempPos, 20, 20, 0.0f, -1, 0);

	vTempPos = Vector2(35, 0);
	m_tLife2 = new Texture(sPath, vTempPos, 20, 20, 0.0f, -1, 0);

	vTempPos = Vector2(60, 0);
	m_tLife3 = new Texture(sPath, vTempPos, 20, 20, 0.0f, -1, 0);


	std::string sPath10 = SDL_GetBasePath();
	sPath10.append("Assets/Green.png");
	vTempPos = Vector2(100, 2);
	m_tTimeBar = new Texture(sPath10, vTempPos, 300, 15, 0.0f, -1, 0);

	std::string sPath11 = SDL_GetBasePath();
	sPath11.append("Assets/Title.png");
	vTempPos = Vector2(100, 160);
	m_tTitle = new Texture(sPath11, vTempPos, 340, 80, 0.0f, -1, 0);

	std::string sPath12 = SDL_GetBasePath();
	sPath12.append("Assets/Start.png");
	vTempPos = Vector2(180, 360);
	m_tStart = new Texture(sPath12, vTempPos, 160, 40, 0.0f, -1, 0);

	std::string sPath13 = SDL_GetBasePath();
	sPath13.append("Assets/0.png");
	vTempPos = Vector2(400, 3);;
	m_tScore = new Texture(sPath13, vTempPos, 80, 15, 0.0f, -1, 0);
}

GameManager::~GameManager()
{
	Graphics::Release();
	m_gGraphics = NULL;

	delete m_tPlayer;
	m_tPlayer = NULL;

	delete m_tBackground;
	m_tBackground = NULL;

	delete m_tObstacle;
	m_tObstacle = NULL;

	delete m_tObstacle2;
	m_tObstacle2 = NULL;

	delete m_tObstacle3;
	m_tObstacle3 = NULL;

	delete m_tObstacle4;
	m_tObstacle4 = NULL;

	delete m_tObstacle5;
	m_tObstacle5 = NULL;

	delete m_tObstacle6;
	m_tObstacle6 = NULL;

	delete m_tObstacle7;
	m_tObstacle7 = NULL;

	delete m_tObstacle8;
	m_tObstacle8 = NULL;

	delete m_tObstacle9;
	m_tObstacle9 = NULL;

	delete m_tLog1;
	m_tLog1 = NULL;

	delete m_tLog2;
	m_tLog2 = NULL;

	delete m_tLog3;
	m_tLog3 = NULL;

	delete m_tLog4;
	m_tLog4 = NULL;

	delete m_tLog5;
	m_tLog5 = NULL;

	delete m_tLog6;
	m_tLog6 = NULL;

	delete m_tLog7;
	m_tLog7 = NULL;

	delete m_tLog8;
	m_tLog8 = NULL;

	delete m_tLog9;
	m_tLog9 = NULL;

	delete m_tLog10;
	m_tLog10 = NULL;

	delete m_tLog11;
	m_tLog11 = NULL;

	delete m_tLog12;
	m_tLog12 = NULL;

	delete m_tLog13;
	m_tLog13 = NULL;

	delete m_tLily1;
	m_tLily1 = NULL;

	delete m_tLily2;
	m_tLily2 = NULL;

	delete m_tLily3;
	m_tLily3 = NULL;

	delete m_tLily4;
	m_tLily4 = NULL;

	delete m_tLife1;
	m_tLife1 = NULL;

	delete m_tLife2;
	m_tLife2 = NULL;

	delete m_tLife3;
	m_tLife3 = NULL;

	delete m_tTimeBar;
	m_tTimeBar = NULL;

	delete m_tTitle;
	m_tTitle = NULL;

	delete m_tStart;
	m_tStart = NULL;

	delete m_tScore;
	m_tScore = NULL;
}