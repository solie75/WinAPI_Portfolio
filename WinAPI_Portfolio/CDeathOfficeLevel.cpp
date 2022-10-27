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
	CResourceMgr::GetInst()->LoadTexture(L"OfficeChair", L"texture\\OfficeChair.bmp");

	// Create BackGround
	CBackgroundTexture* pBackground = new CBackgroundTexture(L"DeathOffice");
	pBackground->SetScale(Vec(2048.f, 1024.f));
	Instantiate(pBackground, Vec(800.f, 450.f), LAYER::BACKGROUND);

	CBackgroundTexture* pOfficeChair = new CBackgroundTexture(L"OfficeChair");
	pOfficeChair->SetScale(Vec(256.f, 512.f));
	Instantiate(pOfficeChair, Vec(800.f, 400.f), LAYER::BACKGROUND);

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


