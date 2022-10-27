#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCameraMgr.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	// Texture Loading

	// print BackGround

	// Create Object

	Vec vResolution = CEngine::GetInst()->GetResolution();
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::LevelTick()
{
	CLevel::LevelTick();
	if (nullptr)
	{
		ChangeLevel(LEVEL_TYPE::END);
	}
}

void CStartLevel::LevelEnter()
{
	LevelInit();
}

void CStartLevel::LevelExit()
{
	DeleteAllObject();
}
