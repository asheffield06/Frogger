#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GameEntity.h"
#include "Graphics.h"

class Texture : public GameEntity 
{
private:
	SDL_Texture* m_tTexture;

	Graphics* m_gGraphics;

public:
	Texture(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_Height, float a_fRot , int a_iDirection, int a_iSpeed);
	~Texture();

	virtual void Render();
	void changeImage(std::string a_sPath);
};

#endif // !_TEXTURE_H_
