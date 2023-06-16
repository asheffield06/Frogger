#include "..\include\Graphics.h"

Graphics* Graphics::m_sInstance = NULL;
bool Graphics::m_bInitialised = false;

Graphics* Graphics::Instance()
{
	// Creates a instance of graphics
	if (m_sInstance == NULL) 
	{
		m_sInstance = new Graphics();
	}
	return m_sInstance;
}

void Graphics::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
	m_bInitialised = false;

}

bool Graphics::Initialised()
{
	return m_bInitialised;
}

void Graphics::Render()
{
	SDL_RenderPresent(m_rRenderer);
}

SDL_Texture* Graphics::LoadTexture(std::string a_sPath)
{
	// Loads the texture up 
	SDL_Texture* tTexture = NULL;

	SDL_Surface* sSurface = IMG_Load(a_sPath.c_str());

	// Puts text into the debug depending on if there is any errors
	if (sSurface == NULL)
	{
		printf("Image Load Error: PATH(%s), Error(%s)\n", a_sPath.c_str(), IMG_GetError());

		return tTexture;
	}

	tTexture = SDL_CreateTextureFromSurface(m_rRenderer, sSurface);
	if (tTexture == NULL) 
	{
		printf("Texture Create Error: %s\n", IMG_GetError());
	}

	SDL_FreeSurface(sSurface);
	return tTexture;
}

void Graphics::ClearBackBuffer()
{
	// Clears the screen ready for a new screen
	SDL_RenderClear(m_rRenderer);
}

void Graphics::DrawTexture(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
	// Draws the texture oput 
	SDL_Rect renderQuad = { a_vPos.x, a_vPos.y, a_iWidth, a_iHeight };
	SDL_RendererFlip rFlip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(m_rRenderer, a_tTexture, NULL, &renderQuad, a_fRot, NULL, rFlip);
}

Graphics::Graphics()
{
	m_bBackBuffer = NULL;
	m_bInitialised = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(m_wWindow);
	m_wWindow = NULL;

	SDL_DestroyRenderer(m_rRenderer);
	m_rRenderer = NULL;

	IMG_Quit();

	SDL_Quit();
}

bool Graphics::Init()
{
	// Prints out errors based on what happens in the game
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("Initialisation Error: %s\n", SDL_GetError);
		return false;
	}

	m_wWindow = SDL_CreateWindow("Frogger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_wWindow == NULL) 
	{
		printf("Window Creation Error: %s\n", SDL_GetError);
		return false;
	}

	m_rRenderer = SDL_CreateRenderer(m_wWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_rRenderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_rRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int iFlag = IMG_INIT_PNG;
	if (!(IMG_Init(iFlag) & iFlag)) 
	{
		printf("Image Initialisation Error: %s\n", IMG_GetError());
	}

	m_bBackBuffer = SDL_GetWindowSurface(m_wWindow);
	return true;

}
