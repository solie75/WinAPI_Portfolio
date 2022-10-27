#include "pch.h"
#include "CDeathOfficeLevel.h"

#include "CLevel.h"
#include "CEngine.h"
#include "CBackgroundTexture.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"

CDeathOfficeLevel::CDeathOfficeLevel()
{
}

CDeathOfficeLevel::~CDeathOfficeLevel()
{
}

void CDeathOfficeLevel::LevelInit()
{
	CResourceMgr::GetInst()->LoadTexture(L"DeathOffice", L"texture\\DeathOffice.bmp");

	// Create BackGround
	CBackgroundTexture* pBackground = new CBackgroundTexture;
	pBackground->SetScale(Vec(2048.f, 1024.f));
	Instantiate(pBackground, Vec(0.f, 0.f), LAYER::BACKGROUND);

	Vec vResolution = CEngine::GetInst()->GetResolution();
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
}

void CDeathOfficeLevel::LevelTick()
{
}

void CDeathOfficeLevel::LevelEnter()
{
	LevelInit();
}

void CDeathOfficeLevel::LevelExit()
{
	DeleteAllObject();
}


