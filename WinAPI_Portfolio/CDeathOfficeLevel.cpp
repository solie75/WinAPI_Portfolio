#include "pch.h"
#include "CDeathOfficeLevel.h"

#include "CLevel.h"
#include "CEngine.h"
#include "CBackground.h"
#include "CBackgroundObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNPC.h"
#include "CTrigger.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

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
	CResourceMgr::GetInst()->LoadTexture(L"DeathChair", L"texture\\DeathChair.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"OfficeElevator", L"texture\\OfficeElevator.bmp");

	// Test Image 
	CResourceMgr::GetInst()->LoadTexture(L"TestMonster", L"texture\\Test2.bmp");

	Vec vResolution = CEngine::GetInst()->GetResolution();

	// Create BackGround
	CBackground* pBackground = new CBackground(L"DeathOffice");
	pBackground->SetScale(Vec(2048.f, 1024.f));
	Instantiate(pBackground, Vec(vResolution.x /2.f, vResolution.y / 2.f), LAYER::BACKGROUND);

	CBackgroundObject* pOfficeChair = new CBackgroundObject(L"DeathChair");
	pOfficeChair->SetScale(Vec(200.f, 350.f));
	Instantiate(pOfficeChair, Vec(625.f, 325.f), LAYER::BACKGROUNDOBJECT);

	CBackgroundObject* pOfficeElevator = new CBackgroundObject(L"OfficeElevator");
	pOfficeElevator->SetScale(Vec(270.f, 370.f));
	Instantiate(pOfficeElevator, Vec(2000.f, 650.f), LAYER::BACKGROUNDOBJECT);

	// Create Player
	CPlayer* pPlayer = new CPlayer(L"Player");
	pPlayer->SetScale(Vec(154.f, 158.f));
	Instantiate(pPlayer, Vec(650.f, 500.f), LAYER::PLAYER);

	// Create NPC
	CNPC* pNPC_Elevator = new CNPC(L"Elevator");
	pNPC_Elevator->SetScale(Vec(100.f, 100.f)); // 임시
	Instantiate(pNPC_Elevator, Vec(2000.f, 650.f), LAYER::NPC);


	// Play Animation of Death's Spawn
	pPlayer->GetAnimator()->Play(L"DeathSpawn", false);
	//pOfficeElevator->GetAnimator()->Play(L"OfficeElevator", false);
	pPlayer->SetKeyWorking(false);

	// Create Test Monster
	CMonster* pMonster = new CMonster(L"TestMonster");
	pMonster->SetScale(Vec(400.f, 130.f));
	Instantiate(pMonster, Vec(300.f, 100.f), LAYER::MONSTER);

	// Elevator Animation Trigger
	CTrigger* pElevatorAppearTrigger = new CTrigger(L"ElevatorAppearTrigger");
	pElevatorAppearTrigger->SetScale(Vec(50.f, 1000.f));
	Instantiate(pElevatorAppearTrigger, Vec(1550.f, 500.f), LAYER::TRIGGER);

	
	//CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
	CCameraMgr::GetInst()->SetLook(Vec(800.f, 450.f));

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BACKGROUND);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::TRIGGER);

}

void CDeathOfficeLevel::LevelTick()
{
	vector<CObject*> playerlayer = this->GetLayer(LAYER::PLAYER);
	vector<CObject*> NPClayer = this->GetLayer(LAYER::NPC);
	vector<CObject*> Triggerlayer = this->GetLayer(LAYER::TRIGGER);

	

	if (playerlayer.empty() == false) {
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(playerlayer[0]);
		if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathSpawn")
		{
			if (pPlayer->GetAnimator()->GetCurAnimation()->GetAnimCurFrame() == 77)
			{
				pPlayer->GetRigidBody()->SetGravity(true);
				pPlayer->GetRigidBody()->AddVelocity(Vec(10.f, -(pPlayer->GetRigidBody()->GetVelocity().y + 800.f)));
			}
			if (pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
			{
				pPlayer->m_bToIdle = true;
				pPlayer->SetKeyWorking(true);
			}
		}
		CTrigger* pOfficeElevatorTrigger = dynamic_cast<CTrigger*>(Triggerlayer[0]);
		if (NPClayer.empty() == false)
		{
			CNPC* pOfficeElevator = dynamic_cast<CNPC*>(NPClayer[0]);
			if (pOfficeElevatorTrigger->IsTriggerOn()) // 이 트리거가 EndOverlap 에서 setDead 하여 오류가 난다.
			{
				pOfficeElevator->GetAnimator()->Play(L"OfficeElevatorAppear", false);
			}
			
		}
	}
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


