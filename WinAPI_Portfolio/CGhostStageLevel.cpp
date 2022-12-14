#include "pch.h"
#include "CGhostStageLevel.h"

#include "CLevel.h"
#include "CEngine.h"
#include "CBackground.h"
#include "CForwardground.h"
#include "CBackgroundObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CGhostWoman.h"
#include "CGhostBook.h"
#include "CNPC.h"
#include "CTrigger.h"
#include "CBlind.h"
#include "CDialog.h"
#include "CWall.h"

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
	CCameraMgr::GetInst()->SetLook(Vec(812.f, 934.f));

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
	
	CWall* Wall_1 = new CWall(L"Wall_1");
	Wall_1->SetScale(Vec(40.f, 3000.f));
	Instantiate(Wall_1, Vec(0.f, 1500.f), LAYER::WALL);

	CWall* Wall_test = new CWall(L"Wall_test");
	Wall_test->SetScale(Vec(40.f, 1000.f));
	Instantiate(Wall_test, Vec(2400.f, 1400.f), LAYER::WALL);  /// test

	CWall* Wall_2 = new CWall(L"Wall_2");
	Wall_2->SetScale(Vec(40.f, 810.f));
	Instantiate(Wall_2, Vec(5330.f, 2130.f), LAYER::WALL);

	CWall* Wall_3 = new CWall(L"Wall_3");
	Wall_3->SetScale(Vec(40.f, 430.f));
	Instantiate(Wall_3, Vec(10070.f, 2320.f), LAYER::WALL);

	CWall* Wall_4 = new CWall(L"Wall_4");
	Wall_4->SetScale(Vec(40.f, 190.f));
	Instantiate(Wall_4, Vec(10787.f, 2011.f), LAYER::WALL);

	CWall* Wall_5 = new CWall(L"Wall_5");
	Wall_5->SetScale(Vec(40.f, 1000.f));
	Instantiate(Wall_5, Vec(12000.f, 1500.f), LAYER::WALL);


	// Create BackObject
	CBackgroundObject* pElevator = new CBackgroundObject(L"Elevator");
	pElevator->SetScale(Vec(270.f, 370.f));
	Instantiate(pElevator, Vec(620.f, 964.f), LAYER::BACKGROUNDOBJECT);

	pElevator->GetAnimator()->Play(L"ElevatorDigOut", false);


	// Create Monster
	CGhostWoman* pGhostWoman = new CGhostWoman(L"GhostWoman");
	pGhostWoman->SetScale(Vec(80.f, 220.f));
	Instantiate(pGhostWoman, Vec(1300.f, 1000.f), LAYER::MONSTER);

	CGhostBook* pGhostBook = new CGhostBook(L"GhostBook");
	pGhostBook->SetScale(Vec(100.f, 80.f));
	Instantiate(pGhostBook, Vec(1200.f, 900.f), LAYER::MONSTER);


	// create Playera
	CPlayer* pPlayer = new CPlayer(L"Player");
	pPlayer->SetScale(Vec(154.f, 158.f));
	Instantiate(pPlayer, Vec(670.f, 1104.f), LAYER::PLAYER);

	pPlayer->GetAnimator()->Play(L"DeathRemove", false);
	pPlayer->SetKeyWorking(false);

	
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BACKGROUND);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::BACKGROUND);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER , LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER , LAYER::WALL);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::WALL);


	
	
}

void CGhostStageLevel::LevelTick()
{

	vector<CObject*> BackgroundLayer = this->GetLayer(LAYER::BACKGROUND);
	vector<CObject*> PlayerLayer = this->GetLayer(LAYER::PLAYER);
	vector<CObject*> BackgroundObjectLayer = this->GetLayer(LAYER::BACKGROUNDOBJECT);

	CBackground* _background  = nullptr;
	CPlayer* _player = nullptr ;
	CBackgroundObject* _backObject_Elevator = nullptr;

	Vec vResolution = CEngine::GetInst()->GetResolution();
	Vec vCameraPos = CCameraMgr::GetInst()->GetCameraLook();
	Vec vCameraRealPos = CCameraMgr::GetInst()->GetRealPos(vCameraPos);

	if (BackgroundLayer.size() != 0)
	{
		_background = dynamic_cast<CBackground*>(BackgroundLayer[2]);
	}
	if (PlayerLayer.size() != 0)
	{
		_player = dynamic_cast<CPlayer*>(PlayerLayer[0]);
	}
	if (BackgroundObjectLayer.size() != 0)
	{
		_backObject_Elevator = dynamic_cast<CBackgroundObject*>(BackgroundObjectLayer[0]);
	}
	
	if (_backObject_Elevator != nullptr && _player != nullptr && _background != nullptr)
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

		Vec vDeathRealPos = CCameraMgr::GetInst()->GetRealPos(_player->GetPos());
		Vec vBackgroundRealPos = CCameraMgr::GetInst()->GetRealPos(_background->GetPos());
		CCameraMgr::GetInst()->SetCameraWorkRow(true);
		CCameraMgr::GetInst()->SetCameraWorkCol(true);
		// ???????? ???? ???? ?????? ?????? ????
		if ((vBackgroundRealPos.y - (_background->GetScale().y / 2.f) + 2000.f > vCameraRealPos.y - (vResolution.y / 2.f)) && (vDeathRealPos.y  < vBackgroundRealPos.y - (_background->GetScale().y / 2.f) + (vResolution.y / 2.f))) // ???? ???????? ???? y ?????? ?????? ?? ???? ???? y ???????? ?????? ???? ????
		{ // ??
			CCameraMgr::GetInst()->SetCameraWorkCol(false);
		}
		if ((vBackgroundRealPos.y + (_background->GetScale().y / 2.f)  < vCameraRealPos.y + (vResolution.y / 2.f)) && (vDeathRealPos.y  > vBackgroundRealPos.y + (_background->GetScale().y / 2.f) - (vResolution.y / 2.f)))
		{ // ??
			CCameraMgr::GetInst()->SetCameraWorkCol(false);
		}
		if ((vBackgroundRealPos.x - (_background->GetScale().x / 2.f) + 20.f > vCameraRealPos.x - (vResolution.x / 2.f)) && (vDeathRealPos.x  < vBackgroundRealPos.x - (_background->GetScale().x / 2.f) + (vResolution.x / 2.f)))
		{ // ??
			CCameraMgr::GetInst()->SetCameraWorkRow(false);
		}
		if ((vBackgroundRealPos.x + (_background->GetScale().x / 2.f)  < vCameraRealPos.x + (vResolution.x / 2.f)) && (vDeathRealPos.x  > vBackgroundRealPos.x + (_background->GetScale().x / 2.f) - (vResolution.x / 2.f)))
		{ // ??
			CCameraMgr::GetInst()->SetCameraWorkRow(false);
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


