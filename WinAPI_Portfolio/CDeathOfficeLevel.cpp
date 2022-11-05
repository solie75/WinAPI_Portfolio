#include "pch.h"
#include "CDeathOfficeLevel.h"

#include "CLevel.h"
#include "CEngine.h"
#include "CBackground.h"
#include "CBackgroundObject.h"
#include "CPlayer.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"

#include "CAnimator.h"

CDeathOfficeLevel::CDeathOfficeLevel()
{
}

CDeathOfficeLevel::~CDeathOfficeLevel()
{
}

void CDeathOfficeLevel::LevelInit()
{
	// Image Loading
	CResourceMgr::GetInst()->LoadTexture(L"DeathOffice", L"texture\\DeathOffice.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"OfficeChair", L"texture\\OfficeChair.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"DeathSpawn", L"texture\\DeathSpawn.bmp");

	Vec vResolution = CEngine::GetInst()->GetResolution();

	// Create BackGround
	CBackground* pBackground = new CBackground(L"DeathOffice");
	pBackground->SetScale(Vec(2048.f, 1024.f));
	Instantiate(pBackground, Vec(vResolution.x /2.f, vResolution.y / 2.f), LAYER::BACKGROUND);

	CBackgroundObject* pOfficeChair = new CBackgroundObject(L"OfficeChair");
	pOfficeChair->SetScale(Vec(256.f, 512.f));
	Instantiate(pOfficeChair, Vec(625.f, 245.f), LAYER::BACKGROUNDOBJECT);

	// Create Player
	CPlayer* pPlayer = new CPlayer(L"Player");
	pPlayer->SetScale(Vec(154.f, 158.f));
	Instantiate(pPlayer, Vec(680.f, 500.f), LAYER::PLAYER);

	// Play Animation of Death's Spawn
	pPlayer->GetAnimator()->Play(L"DeathSpawn", false);

	
	//CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
	CCameraMgr::GetInst()->SetLook(Vec(800.f, 450.f));

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BACKGROUND);

}

void CDeathOfficeLevel::LevelTick()
{
	CLevel::LevelTick();
}

void CDeathOfficeLevel::LevelEnter()
{
	LevelInit();
}

void CDeathOfficeLevel::LevelExit()
{
	DeleteAllObject();
}


