#include "pch.h"
#include "CStartLevel.h"
#include "CBackground.h"
#include "CEngine.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CBlind.h"
#include "CLevelMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	CCameraMgr::GetInst()->SetLook(Vec(800.f, 450.f));
	
	Vec vCameraLook = CCameraMgr::GetInst()->GetCameraLook();
	
	CResourceMgr::GetInst()->LoadTexture(L"StartBackground", L"texture\\StartMenuBackground.bmp");
	Vec vResolution = CEngine::GetInst()->GetResolution();
	
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);

	CBackground* pBackground = new CBackground(L"StartBackground");
	pBackground->SetScale(vResolution);
	Instantiate(pBackground, vCameraLook, LAYER::BACKGROUND);;

	CBlind* pBlind = new CBlind(L"Blind");
	pBlind->SetScale(Vec(1600.f, 900.f));
	Instantiate(pBlind, vCameraLook, LAYER::BLIND);

	bgm1 = CResourceMgr::GetInst()->LoadSound(L"BGM1", L"sound\\StartBGM.wav");
	bgm1->SetPosition(0);

	bgm1->PlayToBGM(true);
}

void CStartLevel::LevelTick()
{
	vector<CObject*> BlindLayer = this->GetLayer(LAYER::BLIND);
	if (IsTap(KEY::A))
	{
		if (!BlindLayer.empty())
		{
			CBlind* pBlind = dynamic_cast<CBlind*>(BlindLayer[0]);
			if (pBlind->CurEffect == (UINT)Blind_Effect::NONE)
			{
				pBlind->FadeOut(0.7f);
				CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::DEATHOFFICE);
			}
		}
	}

	CLevel::LevelTick();
}

void CStartLevel::LevelEnter()
{
	LevelInit();
}

void CStartLevel::LevelExit()
{
	DeleteAllObject();
}
