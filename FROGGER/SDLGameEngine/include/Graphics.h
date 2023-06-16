#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>

#include "MathUtility.h"


class Graphics 
{
public:
	static const int SCREEN_WIDTH = 520;
	static const int SCREEN_HEIGHT = 600;

private:
	static Graphics* m_sInstance;
	static bool m_bInitialised;

	SDL_Window* m_wWindow;
	SDL_Surface* m_bBackBuffer;

	SDL_Renderer* m_rRenderer;

public:
	static Graphics* Instance();
	static void Release();
	static bool Initialised();

	void Render();

	SDL_Texture* LoadTexture(std::string a_sPath);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot);

private:
	Graphics();
	~Graphics();

	bool Init();
};

#endif // !_GRAPHICS_H_
