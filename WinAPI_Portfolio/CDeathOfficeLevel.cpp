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


CDeathOfficeLevel::CDeathOfficeLevel()
	: OnStage(false)
{
}

CDeathOfficeLevel::~CDeathOfficeLevel()
{
}

void CDeathOfficeLevel::LevelInit()
{
	Vec _resolution = CEngine::GetInst()->GetResolution();

	// Image Loading
	CResourceMgr::GetInst()->LoadTexture(L"DeathOffice", L"texture\\DeathOffice.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"DeathChair", L"texture\\DeathChair.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"OfficeElevator", L"texture\\OfficeElevator.bmp");
	CResourceMgr::GetInst()->LoadTexture(L"ElevatorDialog", L"texture\\ElevatorDialog.bmp");

	// Test Image 
	CResourceMgr::GetInst()->LoadTexture(L"TestMonster", L"texture\\Test2.bmp");

	Vec vResolution = CEngine::GetInst()->GetResolution();

	// Create BackGround
	CBackground* pBackground = new CBackground(L"DeathOffice");
	pBackground->SetScale(Vec(2048.f, 1024.f));
	Instantiate(pBackground, Vec(vResolution.x /2.f, vResolution.y / 2.f), LAYER::BACKGROUND);

	CBackgroundObject* pOfficeChair = new CBackgroundObject(L"DeathChair");
	pOfficeChair->SetScale(Vec(200.f, 350.f));
	pOfficeChair->SetBoolShow(true);
	Instantiate(pOfficeChair, Vec(625.f, 325.f), LAYER::BACKGROUNDOBJECT);

	CBackgroundObject* pOfficeElevator = new CBackgroundObject(L"OfficeElevator");
	pOfficeElevator->SetScale(Vec(270.f, 370.f));
	pOfficeElevator->SetBoolShow(true);
	Instantiate(pOfficeElevator, Vec(2000.f, 650.f), LAYER::BACKGROUNDOBJECT);

	

	// Create Player
	CPlayer* pPlayer = new CPlayer(L"Player");
	pPlayer->SetScale(Vec(154.f, 158.f));
	Instantiate(pPlayer, Vec(650.f, 500.f), LAYER::PLAYER);

	// Play Animation of Death's Spawn
	pPlayer->GetAnimator()->Play(L"DeathSpawn", false);
	pPlayer->SetKeyWorking(false);

	// Create Test Monster
	CMonster* pMonster = new CMonster(L"TestMonster");
	pMonster->SetScale(Vec(400.f, 130.f));
	//Instantiate(pMonster, Vec(300.f, 100.f), LAYER::MONSTER);

	// Create NPC
	CNPC* pElevator = new CNPC(L"Elevator");
	pElevator->SetScale(Vec(520.f, 370.f));
	Instantiate(pElevator, Vec(2000.f, 650.f), LAYER::NPC);
	

	// Elevator Animation Trigger
	CTrigger* pElevatorAppearTrigger = new CTrigger(L"ElevatorAppearTrigger");
	pElevatorAppearTrigger->SetScale(Vec(50.f, 1000.f));
	Instantiate(pElevatorAppearTrigger, Vec(1550.f, 500.f), LAYER::TRIGGER);

	// Blind
	CBlind* pBlind = new CBlind(L"Blind");
	pBlind->SetScale(Vec(1600.f, 900.f));
	Vec _v = CCameraMgr::GetInst()->GetCameraLook();
	Instantiate(pBlind, _v, LAYER::BLIND);

	CDialog* pElevatorDialog = new CDialog(L"ElevatorDialog");
	pElevatorDialog->SetScale(Vec(1080.f, 450.f));
	Instantiate(pElevatorDialog, Vec(vResolution.x / 2.f, vResolution.y / 2.f), LAYER::DIALOG);

	

	
	//CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
	CCameraMgr::GetInst()->SetLook(Vec(800.f, 450.f));
	/*Vec vPlayerRealPos = CCameraMgr::GetInst()->GetRealPos(pPlayer->GetPos());
	CCameraMgr::GetInst()->SetLook(Vec(vPlayerRealPos.x, vPlayerRealPos.y));*/

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BACKGROUND);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::TRIGGER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::NPC);

}

void CDeathOfficeLevel::LevelTick()
{
	vector<CObject*> pBackgroundLayer = this->GetLayer(LAYER::BACKGROUND);
	vector<CObject*> playerLayer = this->GetLayer(LAYER::PLAYER);
	vector<CObject*> NPCLayer = this->GetLayer(LAYER::NPC);
	vector<CObject*> TriggerLayer = this->GetLayer(LAYER::TRIGGER);
	vector<CObject*> BlindLayer = this->GetLayer(LAYER::BLIND);
	vector<CObject*> DialogLayer = this->GetLayer(LAYER::DIALOG);
	vector<CObject*> BackgroundObjectLayer = this->GetLayer(LAYER::BACKGROUNDOBJECT);

	
		if (!BlindLayer.empty())
		{
			CBlind* pBlind = dynamic_cast<CBlind*>(BlindLayer[0]);
			if (!pBackgroundLayer.empty())
			{
				CBackground* pBackground = dynamic_cast<CBackground*>(pBackgroundLayer[0]);
				Vec vBackgroundRealPos = CCameraMgr::GetInst()->GetRealPos(pBackground->GetPos());
				Vec vResolution = CEngine::GetInst()->GetResolution();
				Vec vCameraPos = CCameraMgr::GetInst()->GetCameraLook();
				Vec vCameraRealPos = CCameraMgr::GetInst()->GetRealPos(vCameraPos);

				// 화면 전환 애니메이션
				if (pBlind->GetAnimator()->GetCurAnimation() != nullptr)
				{
					if (pBlind->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"TransitionIn_Part1" && pBlind->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						pBlind->GetAnimator()->Play(L"TransitionIn_Part2", false);
					}
					if (pBlind->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"TransitionIn_Part2" && pBlind->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						pBlind->GetAnimator()->Play(L"TransitionIn_Part3", false);
					}
					if (pBlind->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"TransitionIn_Part3" && pBlind->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						pBlind->GetAnimator()->Play(L"TransitionIn_Part4", false);
					}
					if (pBlind->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"TransitionIn_Part4" && pBlind->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						pBlind->GetAnimator()->Play(L"TransitionIn_Part5", false);
					}
					if (pBlind->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"TransitionIn_Part5" && pBlind->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::GHOSTSTAGE);
						return;
					}
				}
				if (!BackgroundObjectLayer.empty())
				{
					CBackgroundObject* pBackgroundObject = dynamic_cast<CBackgroundObject*>(BackgroundObjectLayer[1]);
					if (nullptr != pBackgroundObject->GetAnimator()->GetCurAnimation())
					{
						if (pBackgroundObject->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorClose" && pBackgroundObject->GetAnimator()->GetCurAnimation()->IsFinish())
						{
							pBackgroundObject->m_bShow = false;
							pBackgroundObject->GetAnimator()->Play(L"ElevatorDigIn", false);
							pBlind->CurEffect = (UINT)Blind_Effect::NONE;

						}
						if (pBackgroundObject->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorDigIn" && pBackgroundObject->GetAnimator()->GetCurAnimation()->IsFinish())
						{
							if (pBlind->GetAnimator()->GetCurAnimation() == nullptr && pBlind->CurEffect == (UINT)Blind_Effect::NONE)
							{
								pBlind->FadeOut(0.7f);
								pBlind->GetAnimator()->Play(L"TransitionIn_Part1", false);
							}
						}
					}
				}

				if (!playerLayer.empty())
				{
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(playerLayer[0]);
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

					Vec vDeathRealPos = CCameraMgr::GetInst()->GetRealPos(pPlayer->GetPos());
					CCameraMgr::GetInst()->SetCameraWorkRow(true);
					CCameraMgr::GetInst()->SetCameraWorkCol(true);
					// 카메라의 시점 배경 이미지 안으로 제한
					if ((vBackgroundRealPos.y - (pBackground->GetScale().y / 2.f) - 200.f > vCameraRealPos.y - (vResolution.y / 2.f)) && (vDeathRealPos.y + 100.f < vBackgroundRealPos.y - (pBackground->GetScale().y / 2.f) + (vResolution.y / 2.f))) // 실제 이미지의 위쪽 y 좌표가 카메라 의 실제 위쪽 y 좌표보다 아래에 있는 경우
					{ // 상
						CCameraMgr::GetInst()->SetCameraWorkCol(false);
					}
					if ((vBackgroundRealPos.y + (pBackground->GetScale().y / 2.f) + 200.f < vCameraRealPos.y + (vResolution.y / 2.f)) && (vDeathRealPos.y - 200.f > vBackgroundRealPos.y + (pBackground->GetScale().y / 2.f) - (vResolution.y / 2.f)))
					{ // 하
						CCameraMgr::GetInst()->SetCameraWorkCol(false);
					}
					if ((vBackgroundRealPos.x - (pBackground->GetScale().x / 2.f) - 500.f > vCameraRealPos.x - (vResolution.x / 2.f)) && (vDeathRealPos.x + 500.f < vBackgroundRealPos.x - (pBackground->GetScale().x / 2.f) + (vResolution.x / 2.f)))
					{ // 좌
						CCameraMgr::GetInst()->SetCameraWorkRow(false);
					}
					if ((vBackgroundRealPos.x + (pBackground->GetScale().x / 2.f) + 500.f < vCameraRealPos.x + (vResolution.x / 2.f)) && (vDeathRealPos.x - 500.f > vBackgroundRealPos.x + (pBackground->GetScale().x / 2.f) - (vResolution.x / 2.f)))
					{ // 우
						CCameraMgr::GetInst()->SetCameraWorkRow(false);
					}

				}
			}

			if (!NPCLayer.empty())
			{
				CNPC* pNPC_Elevator = dynamic_cast<CNPC*>(NPCLayer[0]);
				if (!BackgroundObjectLayer.empty())
				{
					CBackgroundObject* pBackgroundObject = dynamic_cast<CBackgroundObject*>(BackgroundObjectLayer[1]);
					if (pBackgroundObject->m_bShow == false)
					{
						pNPC_Elevator->m_bInteraction = false;
					}
				}

				CTrigger* pOfficeElevatorTrigger = nullptr;
				if (!TriggerLayer.empty())
				{
					pOfficeElevatorTrigger = dynamic_cast<CTrigger*>(TriggerLayer[0]);
				}



				if (pOfficeElevatorTrigger != nullptr && pOfficeElevatorTrigger->Trigger) // 이 트리거가 EndOverlap 에서 setDead 하여 오류가 난다.
				{
					pNPC_Elevator->GetAnimator()->Play(L"ElevatorAppear", false);
					pOfficeElevatorTrigger->Trigger = false;
				}
				if (pNPC_Elevator->GetAnimator()->GetCurAnimation() != nullptr)
				{
					if (pNPC_Elevator->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorAppear" && pNPC_Elevator->GetAnimator()->GetCurAnimation()->IsFinish())
					{
						pNPC_Elevator->GetAnimator()->Play(L"ElevatorIdle", true);
					}
				}


				CDialog* pDialog = dynamic_cast<CDialog*>(DialogLayer[0]);

				if (pNPC_Elevator->m_bInteraction)
				{

					CPlayer* pPlayer = dynamic_cast<CPlayer*>(playerLayer[0]);

					if (pBlind->CurEffect == (UINT)Blind_Effect::FADE_OUT && pBlind->m_fAccTime > pBlind->m_fMaxTime / 2.f)
					{
						pDialog->CurAnim = 1;
					}



					// 다이얼 대화
					if (IsTap(KEY::F))
					{

						//pPlayer->SetKeyWorking(false);

						if (pBlind->CurEffect == (UINT)Blind_Effect::NONE)
						{
							pBlind->FadeOut(0.7f);
						}
						else if (pBlind->CurEffect == (UINT)Blind_Effect::FADE_OUT)
						{
							if (pBlind->m_fAccTime == 0.f)
							{
								pDialog->CurAnim++;
							}
							if (pDialog->CurAnim == 4)
							{
								pBlind->FadeIn(0.7f);
								pDialog->CurAnim = 0;
							}
						}
					}

					// 다이얼 종료시 애니메이션 시작
					if (pBlind->CurEffect == (UINT)Blind_Effect::DONE)
					{
						if (pNPC_Elevator->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorIdle")
						{
							pNPC_Elevator->GetAnimator()->Play(L"ElevatorDisappear", false);
						}
						if (pNPC_Elevator->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"ElevatorDisappear" && pNPC_Elevator->GetAnimator()->GetCurAnimation()->IsFinish())
						{
							Vec vElevatorPos = pNPC_Elevator->GetPos();
							Vec vPlayerPos = pPlayer->GetPos();

							// 데스가 왼쪽
							if (vPlayerPos.x < vElevatorPos.x - 50.f)
							{
								// 방향 전환
								if (pPlayer->DeathSight == (UINT)DEATH_SIGHT::LEFT)
								{
									if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() != L"DeathIdleRight")
									{
										pPlayer->GetAnimator()->Play(L"DeathIdleRight", true);
										pPlayer->DeathSight = (UINT)DEATH_SIGHT::RIGHT;
									}
								}

								// 이동
								pPlayer->SetPos(Vec(vPlayerPos.x += pPlayer->m_fSpeed * DT, vPlayerPos.y));

								// 진입 애니메이션
								if (vPlayerPos.x > vElevatorPos.x - 60.f && pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() != L"DeathElevatorInRight")
								{
									pPlayer->GetAnimator()->Play(L"DeathElevatorInRight", false);
								}

							}
							if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathElevatorInRight" && pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
							{
								pPlayer->GetAnimator()->Play(L"DeathElevatorIdleRight", false);
							}
							// 데스가 오른쪽
							if (vPlayerPos.x > vElevatorPos.x + 50.f)
							{
								// 방향 전환
								if (pPlayer->DeathSight == (UINT)DEATH_SIGHT::RIGHT)
								{
									if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() != L"DeathIdleLeft")
									{
										pPlayer->GetAnimator()->Play(L"DeathIdleLeft", true);
										pPlayer->DeathSight = (UINT)DEATH_SIGHT::LEFT;
									}

								}
								pPlayer->SetPos(Vec(vPlayerPos.x -= pPlayer->m_fSpeed * DT, vPlayerPos.y));

								if (vPlayerPos.x < vElevatorPos.x + 60.f && pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() != L"DeathElevatorInLeft")
								{
									pPlayer->GetAnimator()->Play(L"DeathElevatorInLeft", false);
								}

							}
							if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathElevatorInLeft" && pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
							{
								pPlayer->GetAnimator()->Play(L"DeathElevatorIdleLeft", false);
							}

							CBackgroundObject* pBackgroundObject = dynamic_cast<CBackgroundObject*>(BackgroundObjectLayer[1]);

							if (pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathElevatorIdleRight" || pPlayer->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathElevatorIdleLeft")
							{
								if (pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
								{
									pPlayer->GetAnimator()->Play(L"DeathRemove", true);
									pBackgroundObject->GetAnimator()->Play(L"ElevatorClose", false);
								}
							}
						}
					}
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
