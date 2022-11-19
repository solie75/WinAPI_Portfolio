#include "pch.h"
#include "CGhostStageLevel.h"

#include "CLevel.h"
#include "CEngine.h"
#include "CBackground.h"
#include "CForwardground.h"
#include "CBackgroundObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNPC.h"
#include "CTrigger.h"
#include "CBlind.h"
#include "CDialog.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"


CGhostStageLevel::CGhostStageLevel()
	: OnStage(false)
{
}

CGhostStageLevel::~CGhostStageLevel()
{
}

void CGhostStageLevel::LevelInit()
{
	Vec _vResolution = CEngine::GetInst()->GetResolution();

	// Image BackGround Loading
	CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer1", L"texture\\Ghost_Stage_Layer1.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer2", L"texture\\Ghost_Stage_Layer2.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer3", L"texture\\Ghost_Stage_Layer3.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer4", L"texture\\Ghost_Stage_Layer4.bmp");

	// Camera Position
	CCameraMgr::GetInst()->SetLook(Vec(900.f, 800.f));

	// Create BackGround
	CBackground* Ghost_Stage_Layer1 = new CBackground(L"Ghost_Stage_Layer1"); // create Line Collider here
	Ghost_Stage_Layer1->SetScale(Vec(12000.f, 3000.f));
	Instantiate(Ghost_Stage_Layer1, Ghost_Stage_Layer1->GetScale()/2.f, LAYER::BACKGROUND);
	
	CBackground* Ghost_Stage_Layer2 = new CBackground(L"Ghost_Stage_Layer2");
	Ghost_Stage_Layer2->SetScale(Vec(12000.f, 3000.f));
	Instantiate(Ghost_Stage_Layer2, Ghost_Stage_Layer1->GetScale() / 2.f, LAYER::BACKGROUND);
	
	CBackground* Ghost_Stage_Layer3 = new CBackground(L"Ghost_Stage_Layer3");
	Ghost_Stage_Layer3->SetScale(Vec(12000.f, 3000.f));
	Instantiate(Ghost_Stage_Layer3, Ghost_Stage_Layer1->GetScale() / 2.f, LAYER::BACKGROUND);

	CForwardground* Ghost_Stage_Layer4 = new CForwardground(L"Ghost_Stage_Layer4");
	Ghost_Stage_Layer4->SetScale(Vec(12000.f, 3000.f));
	Instantiate(Ghost_Stage_Layer4, Ghost_Stage_Layer1->GetScale() / 2.f, LAYER::FORWARDGROUND);

	CBackgroundObject* pElevator = new CBackgroundObject(L"Elevator");
	pElevator->SetScale(Vec(270.f, 370.f));
	Instantiate(pElevator, Vec(620.f, 964.f), LAYER::BACKGROUNDOBJECT);

	pElevator->GetAnimator()->Play(L"ElevatorDigOut", false);

	// create Playera
	CPlayer* pPlayer = new CPlayer(L"Player");
	pPlayer->SetScale(Vec(154.f, 158.f));
	Instantiate(pPlayer, Vec(pElevator->GetPos().x + 50.f, pElevator->GetPos().y + 140.f), LAYER::PLAYER);

	pPlayer->GetAnimator()->Play(L"DeathRemove", false);
	pPlayer->SetKeyWorking(false);

	
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BACKGROUND);
	
}

void CGhostStageLevel::LevelTick()
{
	vector<CObject*> BackgroundLayer = this->GetLayer(LAYER::BACKGROUND);
	vector<CObject*> PlayerLayer = this->GetLayer(LAYER::PLAYER);
	vector<CObject*> BackgroundObjectLayer = this->GetLayer(LAYER::BACKGROUNDOBJECT);

	CBackground* _background  = nullptr;
	CPlayer* _player = nullptr ;
	CBackgroundObject* _backObject_Elevator = nullptr;

	if (BackgroundLayer.size() != 0)
	{
		_background = dynamic_cast<CBackground*>(BackgroundLayer[0]);
	}
	if (PlayerLayer.size() != 0)
	{
		_player = dynamic_cast<CPlayer*>(PlayerLayer[0]);
	}
	if (BackgroundObjectLayer.size() != 0)
	{
		_backObject_Elevator = dynamic_cast<CBackgroundObject*>(BackgroundObjectLayer[0]);
	}
	
	if (_backObject_Elevator != nullptr && _player != nullptr)
	{
		if (_backObject_Elevator->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorDigOut" && _backObject_Elevator->GetAnimator()->GetCurAnimation()->IsFinish())
		{
			_backObject_Elevator->GetAnimator()->Play(L"ElevatorOpen", false);
		}
		if (_backObject_Elevator->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorOpen" && _backObject_Elevator->GetAnimator()->GetCurAnimation()->IsFinish())
		{
			_backObject_Elevator->SetBoolShow(true);
			if (_player->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathRemove" && _player->GetAnimator()->GetCurAnimation()->IsFinish())
			{
				_player->GetAnimator()->Play(L"DeathElevatorOut", false);
			}
		}
		if (_player->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathElevatorOut" && _player->GetAnimator()->GetCurAnimation()->IsFinish())
		{
			_player->GetAnimator()->Play(L"DeathIdleRight", true);
			_player->SetKeyWorking(true);
			_player->GetRigidBody()->SetGravity(true);
		}
	}
	
	
	CLevel::LevelTick();
}

void CGhostStageLevel::LevelEnter()
{
	LevelInit();
}

void CGhostStageLevel::LevelExit()
{
	DeleteAllObject();
}


