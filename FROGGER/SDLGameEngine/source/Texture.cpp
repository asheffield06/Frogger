#include "..\include\Texture.h"

Texture::Texture(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_Height, float a_fRot, int a_iDirection, int a_iSpeed)
{
	m_gGraphics = Graphics::Instance();

	// Sets all nessarary variables for a texture
	m_vPos = a_vPos;
	m_iWidth = a_iWidth;
	m_iHeight = a_Height;
	m_fRotation = a_fRot;
	m_iDirection = a_iDirection;
	m_iSpeed = a_iSpeed; 

	m_tTexture = m_gGraphics->LoadTexture(a_sPath);
}

Texture::~Texture()
{
	// Deletes the texture
	SDL_DestroyTexture(m_tTexture);
	m_tTexture = NULL;
	m_gGraphics = NULL;
}

void Texture::Render()
{
	// Renders the texture to the screen
	m_gGraphics->DrawTexture(m_tTexture, m_vPos, m_iWidth, m_iHeight, m_fRotation);
}

void Texture::changeImage(std::string a_sPath)
{
	// Changes the image 
	m_gGraphics->ClearBackBuffer();
	m_tTexture = m_gGraphics->LoadTexture(a_sPath);
}
