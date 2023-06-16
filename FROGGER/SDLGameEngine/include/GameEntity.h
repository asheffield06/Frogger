#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_

#include "MathUtility.h"

class GameEntity 
{
public:
	enum SPACE 
	{
		local = 0,
	    world = 1
	};
	
	Vector2 m_vPos;
	int m_iWidth;
	int m_iHeight;
	float m_fRotation;
	int m_iDirection;
	int m_iSpeed;

	bool m_bActive;
	GameEntity* m_oParent;

public:
	GameEntity(float a_fX = 0.0f, float a_fY = 0.0f);
	~GameEntity();

	void Pos(Vector2 a_vPos);

	void TranslatePos(float a_fX, float a_fY);
	Vector2 Pos(SPACE a_eSpace = world);



	void Rotation(float a_fRot);
	float Rotation(SPACE a_eSpace = world);

	void SetActive(bool a_bActive);
	bool IsActive();

	void Parent(GameEntity* a_oParent);
	GameEntity* Parent();

	virtual void Update();
	virtual void Render();
};
#endif // !_GAMEENTITY_H_

