#include "..\include\GameEntity.h"

GameEntity::GameEntity(float a_fX, float a_fY)
{
	// Default variables set for the game entity
	m_vPos.x = a_fX;
	m_vPos.y = a_fY;

	m_fRotation = 0.0f;

	m_bActive = true;

	m_oParent = NULL;
}

GameEntity::~GameEntity()
{
	m_oParent = NULL;
}

void GameEntity::Pos(Vector2 a_vPos)
{
	m_vPos = a_vPos;
}

void GameEntity::TranslatePos(float a_fX, float a_fY)
{
	m_vPos.x += a_fX;
	m_vPos.y -= a_fY;
}

Vector2 GameEntity::Pos(SPACE a_eSpace)
{
	if (a_eSpace == local || m_oParent == NULL) 
	{
		return m_vPos;
	}

	return m_oParent->Pos(world) + RotateVector(m_vPos, m_oParent->Rotation(local));
}

void GameEntity::Rotation(float a_fRot)
{
	// Rotates the gameobject 
	m_fRotation = a_fRot;

	if (m_fRotation > 360.0f) 
	{
		m_fRotation -= 360.0f;
	}
	if (m_fRotation < 0.0f) 
	{
		m_fRotation += 360.0f;
	}
}

float GameEntity::Rotation(SPACE a_eSpace)
{
	if (a_eSpace == local || m_oParent == NULL) 
	{
		return m_fRotation;
	}

	return m_oParent->Rotation(world) + m_fRotation;
}

void GameEntity::SetActive(bool a_bActive)
{
	m_bActive = a_bActive;
}

bool GameEntity::IsActive()
{
	return m_bActive;
}

void GameEntity::Parent(GameEntity* a_oParent)
{
	m_vPos = Pos(world) - a_oParent->Pos(world);
	m_oParent = a_oParent;
}

GameEntity* GameEntity::Parent()
{
	return m_oParent;
}

void GameEntity::Update()
{
}

void GameEntity::Render()
{
}
