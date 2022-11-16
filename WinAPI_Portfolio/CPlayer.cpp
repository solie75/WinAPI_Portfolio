#include "pch.h"
#include "CPlayer.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CLineCollider.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"

CTexture* m_pTexture;
CTexture* m_pDeathSpawn;

CTexture* m_pDeathIdleRight;
CTexture* m_pDeathIdleLeft;

CTexture* m_pDeathIdleRightToLeft;
CTexture* m_pDeathIdleLeftToRight;

CTexture* m_pDeathIdleToRunRight;
CTexture* m_pDeathIdleToRunLeft;

CTexture* m_pDeathRunRightToIdle;
CTexture* m_pDeathRunLeftToIdle;

CTexture* m_pDeathRunRight;
CTexture* m_pDeathRunLeft;

CTexture* m_pDeath;

enum class DEATH_STATE
{
	IDLE,
	RUN,
	DASH,
	ATTACK,

	NONE, // during Animation
};

enum class ATTACK_COMBO
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	
	NONE
};


CPlayer::CPlayer()
	: m_pTexture(nullptr)
	, m_pDeathSpawn(nullptr)
	, m_pDeathIdleRight(nullptr)
	, m_pDeathIdleLeft(nullptr)
	, m_pDeathIdleLeftToRight(nullptr)
	, m_pDeathIdleRightToLeft(nullptr)
	, m_pDeathIdleToRunRight(nullptr)
	, m_pDeathIdleToRunLeft(nullptr)
	, m_pDeathRunRightToIdle(nullptr)
	, m_pDeathRunLeftToIdle(nullptr)
	, m_pDeathRunRight(nullptr)
	, m_pDeathRunLeft(nullptr)
	, m_pDeathRunLeftToRunRight(nullptr)
	, m_pDeathRunRightToRunLeft(nullptr)
	, m_pDeathJumpRight(nullptr)
	, m_pDeathJumpLeft(nullptr)
	, m_pDeathLandingRight(nullptr)
	, m_pDeathLandingLeft(nullptr)
	, m_pDeathFallingRight(nullptr)
	, m_pDeathFallingLeft(nullptr)
	, m_pDeathAttackBasicCombo1Right(nullptr)
	, m_pDeathAttackBasicCombo1Left(nullptr)
	, m_pDeathAttackBasicCombo2Right(nullptr)
	, m_pDeathAttackBasicCombo2Left(nullptr)
	, m_pDeathAttackBasicCombo3Right(nullptr)
	, m_pDeathAttackBasicCombo3Left(nullptr)
	, m_pDeathAttackBasicCombo4Right(nullptr)
	, m_pDeathAttackBasicCombo4Left(nullptr)
	, m_pDeathDashRight(nullptr)
	, m_pDeathDashLeft(nullptr)
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
	, m_bToIdle(false)
	, m_bOnIdle(false)
	, m_iJumpCount(0)
	, DeathSight((UINT)DEATH_SIGHT::RIGHT)
	, DeathAttackCombo((UINT)ATTACK_COMBO::NONE)
	, DeathState((UINT)DEATH_STATE::NONE)

	//, m_vecPlayerEffect{}
{
}

CPlayer::CPlayer(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pDeathSpawn(nullptr)
	, m_pDeathIdleRight(nullptr)
	, m_pDeathIdleLeft(nullptr)
	, m_pDeathIdleLeftToRight(nullptr)
	, m_pDeathIdleRightToLeft(nullptr)
	, m_pDeathIdleToRunRight(nullptr)
	, m_pDeathIdleToRunLeft(nullptr)
	, m_pDeathRunRightToIdle(nullptr)
	, m_pDeathRunLeftToIdle(nullptr)
	, m_pDeathRunRight(nullptr)
	, m_pDeathRunLeft(nullptr)
	, m_pDeathRunLeftToRunRight(nullptr)
	, m_pDeathRunRightToRunLeft(nullptr)
	, m_pDeathJumpRight(nullptr)
	, m_pDeathJumpLeft(nullptr)
	, m_pDeathLandingRight(nullptr)
	, m_pDeathLandingLeft(nullptr)
	, m_pDeathFallingRight(nullptr)
	, m_pDeathFallingLeft(nullptr)
	, m_pDeathAttackBasicCombo1Right(nullptr)
	, m_pDeathAttackBasicCombo1Left(nullptr)
	, m_pDeathAttackBasicCombo2Right(nullptr)
	, m_pDeathAttackBasicCombo2Left(nullptr)
	, m_pDeathAttackBasicCombo3Right(nullptr)
	, m_pDeathAttackBasicCombo3Left(nullptr)
	, m_pDeathAttackBasicCombo4Right(nullptr)
	, m_pDeathAttackBasicCombo4Left(nullptr)
	, m_pDeathDashRight(nullptr)
	, m_pDeathDashLeft(nullptr)
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
	, m_bToIdle(false)
	, m_bOnIdle(false)
	, m_iJumpCount(0)
	, DeathSight((UINT)DEATH_SIGHT::RIGHT)
	, DeathAttackCombo((UINT)ATTACK_COMBO::NONE)
	, DeathState((UINT)DEATH_STATE::NONE)
	//, m_vecPlayerEffect{}
{
	CreateAnimator();
	CreateSquareCollider();
	CreateRigidBody();

	GetColliderVector()[0]->SetColliderOffSetPos(Vec(-5.f, -25.f));
	GetColliderVector()[0]->SetColliderScale(Vec(80.f, 100.f));
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::OBJECT);

	//m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);
	m_pDeathSpawn = CResourceMgr::GetInst()->LoadTexture(L"DeathSpawn", L"texture\\DeathSpawn.bmp");
	m_pDeathIdleRight = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleRight", L"texture\\DeathIdleRight.bmp");
	m_pDeathIdleLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleLeft", L"texture\\DeathIdleLeft.bmp");
	m_pDeathIdleLeftToRight = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleLeftToRight", L"texture\\DeathIdleLeftToRight.bmp");
	m_pDeathIdleRightToLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleRightToLeft", L"texture\\DeathIdleRightToLeft.bmp");
	m_pDeathIdleToRunRight = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleToRunRight", L"texture\\DeathIdleToRunRight.bmp");
	m_pDeathIdleToRunLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathIdleToRunLeft", L"texture\\DeathIdleToRunLeft.bmp");
	m_pDeathRunRightToIdle = CResourceMgr::GetInst()->LoadTexture(L"DeathRunRightToIdle", L"texture\\DeathRunRightToIdle.bmp");
	m_pDeathRunLeftToIdle = CResourceMgr::GetInst()->LoadTexture(L"DeathRunLeftToIdle", L"texture\\DeathRunLeftToIdle.bmp");
	m_pDeathRunRight = CResourceMgr::GetInst()->LoadTexture(L"DeathRunRight", L"texture\\DeathRunRight.bmp");
	m_pDeathRunLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathRunLeft", L"texture\\DeathRunLeft.bmp");
	m_pDeathRunLeftToRunRight = CResourceMgr::GetInst()->LoadTexture(L"DeathRunLeftToRunRight", L"texture\\DeathRunLeftToRunRight.bmp");
	m_pDeathRunRightToRunLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathRunRightToRunLeft", L"texture\\DeathRunRightToRunLeft.bmp");
	m_pDeathJumpRight = CResourceMgr::GetInst()->LoadTexture(L"DeathJumpRight", L"texture\\DeathJumpRight.bmp");
	m_pDeathJumpLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathJumpLeft", L"texture\\DeathJumpLeft.bmp");
	m_pDeathLandingRight = CResourceMgr::GetInst()->LoadTexture(L"DeathLandingRight", L"texture\\DeathLandingRight.bmp");
	m_pDeathLandingLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathLandingLeft", L"texture\\DeathLandingLeft.bmp");
	m_pDeathFallingRight = CResourceMgr::GetInst()->LoadTexture(L"DeathFallingRight", L"texture\\DeathFallingRight.bmp");
	m_pDeathFallingLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathFallingLeft", L"texture\\DeathFallingLeft.bmp");
	m_pDeathAttackBasicCombo1Right = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo1Right", L"texture\\DeathAttackBasicCombo1Right.bmp");
	m_pDeathAttackBasicCombo1Left = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo1Left", L"texture\\DeathAttackBasicCombo1Left.bmp");
	m_pDeathAttackBasicCombo2Right = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo2Right", L"texture\\DeathAttackBasicCombo2Right.bmp");
	m_pDeathAttackBasicCombo2Left = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo2Left", L"texture\\DeathAttackBasicCombo2Left.bmp");
	m_pDeathAttackBasicCombo3Right = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo3Right", L"texture\\DeathAttackBasicCombo3Right.bmp");
	m_pDeathAttackBasicCombo3Left = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo3Left", L"texture\\DeathAttackBasicCombo3Left.bmp");
	m_pDeathAttackBasicCombo4Right = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo4Right", L"texture\\DeathAttackBasicCombo4Right.bmp");
	m_pDeathAttackBasicCombo4Left = CResourceMgr::GetInst()->LoadTexture(L"DeathAttackBasicCombo4Left", L"texture\\DeathAttackBasicCombo4Left.bmp");
	m_pDeathDashRight = CResourceMgr::GetInst()->LoadTexture(L"DeathDashRight", L"texture\\DeathDashRight.bmp");
	m_pDeathDashLeft = CResourceMgr::GetInst()->LoadTexture(L"DeathDashLeft", L"texture\\DeathDashLeft.bmp");

	SetName(_pstring);

	GetAnimator()->CreateAnimation(L"DeathSpawn", m_pDeathSpawn, Vec(0.f, 0.f), Vec(130.f, 166.f), Vec(0.f, 0.f), 99, 0.025f);
	GetAnimator()->CreateAnimation(L"DeathIdleRight", m_pDeathIdleRight, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeft", m_pDeathIdleLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeftToRight", m_pDeathIdleLeftToRight, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathIdleRightToLeft", m_pDeathIdleRightToLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunRight", m_pDeathIdleToRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 4, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunLeft", m_pDeathIdleToRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 4, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunRightToIdle", m_pDeathRunRightToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 9, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunLeftToIdle", m_pDeathRunLeftToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 9, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunRight", m_pDeathRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 5, 0.08f);
	GetAnimator()->CreateAnimation(L"DeathRunLeft", m_pDeathRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 5, 0.08f);
	GetAnimator()->CreateAnimation(L"DeathRunLeftToRunRight", m_pDeathRunLeftToRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunRightToRunLeft", m_pDeathRunRightToRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), Vec(0.f, 0.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathJumpRight", m_pDeathJumpRight, Vec(0.f, 0.f), Vec(120.f, 170.f), Vec(0.f, 0.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathJumpLeft", m_pDeathJumpLeft, Vec(0.f, 0.f), Vec(120.f, 170.f), Vec(0.f, 0.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathLandingRight", m_pDeathLandingRight, Vec(0.f, 0.f), Vec(116.f, 130.f), Vec(0.f, 0.f), 4, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathLandingLeft", m_pDeathLandingLeft, Vec(0.f, 0.f), Vec(116.f, 130.f), Vec(0.f, 0.f), 4, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathFallingRight", m_pDeathFallingRight, Vec(0.f, 0.f), Vec(114.f, 116.f), Vec(0.f, 0.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathFallingLeft", m_pDeathFallingLeft, Vec(0.f, 0.f), Vec(114.f, 116.f), Vec(0.f, 0.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo1Right", m_pDeathAttackBasicCombo1Right, Vec(0.f, 0.f), Vec(400.f, 140.f), Vec(50.f, 0.f), 18, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo1Left", m_pDeathAttackBasicCombo1Left, Vec(0.f, 0.f), Vec(400.f, 140.f), Vec(-50.f, 0.f), 18, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo2Right", m_pDeathAttackBasicCombo2Right, Vec(0.f, 0.f), Vec(340.f, 280.f), Vec(50.f, -50.f), 15, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo2Left", m_pDeathAttackBasicCombo2Left, Vec(0.f, 0.f), Vec(340.f, 280.f), Vec(-50.f, -50.f), 15, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo3Right", m_pDeathAttackBasicCombo3Right, Vec(0.f, 0.f), Vec(640.f, 110.f), Vec(20.f, -20.f), 9, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo3Left", m_pDeathAttackBasicCombo3Left, Vec(0.f, 0.f), Vec(640.f, 110.f), Vec(-20.f, -20.f), 9, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo4Right", m_pDeathAttackBasicCombo4Right, Vec(0.f, 0.f), Vec(444.f, 360.f), Vec(70.f, -120.f), 18, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathAttackBasicCombo4Left", m_pDeathAttackBasicCombo4Left, Vec(0.f, 0.f), Vec(444.f, 360.f), Vec(-70.f, -120.f), 18, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathDashRight", m_pDeathDashRight, Vec(0.f, 0.f), Vec(320.f, 130.f), Vec(0.f, 0.f), 8, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathDashLeft", m_pDeathDashLeft, Vec(0.f, 0.f), Vec(320.f, 130.f), Vec(0.f, 0.f), 8, 0.04f);
	
	//GetAnimator()->FindAnimation(L"DeathIdleRight")->Save(L"animation\\DeathIdleRight.anim");
	//GetAnimator()->FindAnimation(L"DeathIdleLeft")->Save(L"animation\\DeathIdleLeft.anim");
	//GetAnimator()->FindAnimation(L"DeathSpawn")->Save(L"animation\\DeathSpawn.anim");
	//GetAnimator()->FindAnimation(L"DeathIdleRight")->Save(L"animation\\DeathIdleRight.anim");

	/*GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");*/
	 

	// Gravity Setting
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetGravityAccel(1200.f);
	GetRigidBody()->SetGravityVelocityLimit(1400.f);
}

CPlayer::~CPlayer()
{
}


void CPlayer::ObjectTick()
{
	Vec vPos = GetPos();

	CAnimation* CurAnim = this->GetAnimator()->GetCurAnimation();
	wstring CurAnimName = CurAnim->GetCurAnimName();

	// after animation
	if (true == GetKeyWorking())
	{

		if (CurAnimName == L"DeathAttackBasicCombo4Right")
		{
			if (10 <= CurAnim->GetAnimCurFrame() && CurAnim->GetAnimCurFrame() <= 14)
			{
				this->GetColliderVector()[1]->SetColliderScale(Vec(400.f, 350.f));
				this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(100.f, -130.f));
			}
			else
			{
				this->GetColliderVector()[1]->SetColliderScale(Vec(140.f, 130.f));
				this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(0.f, -50.f));
			}
		}
		else if (CurAnimName == L"DeathAttackBasicCombo4Left")
		{
			if (10 <= CurAnim->GetAnimCurFrame() && CurAnim->GetAnimCurFrame() <= 14)
			{
				this->GetColliderVector()[1]->SetColliderScale(Vec(-400.f, 350.f));
				this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(-100.f, -130.f));
			}
			else
			{
				this->GetColliderVector()[1]->SetColliderScale(Vec(-140.f, 130.f));
				this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(0.f, -50.f));
			}
		}

		if ((DeathAttackCombo != (UINT)ATTACK_COMBO::NONE)) // 캐릭터의 콤보 애니메이션 하나가 끝났음.
		{
			if (CurAnim->IsFinish())
			{
				this->SetScale(Vec(154.f, 158.f));

				this->GetRigidBody()->SetGravity(true);

				DeathAttackCombo = (UINT)ATTACK_COMBO::NONE;

				// 공격 Collider 지우기
				if (GetColliderVector()[1]->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
				{
					DeleteLastCollider();
				}

				if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathIdleRight", true);
				}
				if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathIdleLeft", true);
				}
				
			}
			else
			{
				if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					vPos.x += (m_fSpeed / 4.f) * DT;
				}
				if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					vPos.x -= (m_fSpeed / 4.f) * DT;
				}
			}
		}

		//Attack Basic
		if (IsTap(KEY::Z))
		{
			
			this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
			this->GetRigidBody()->SetGravity(false);

			if (DeathAttackCombo == (UINT)ATTACK_COMBO::NONE)
			{
				// 공격 충돌체 추가
				this->AddSquareCollider((UINT)COLLIDER_TYPE::PLAYERATTACK);

				if (this->DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo1Right", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(250.f, 70.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(GetScale().x - 25.f, -25.f));
				}
				if (this->DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo1Left", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(-250.f, 70.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(-GetScale().x + 25.f, -25.f));
				}
				DeathAttackCombo = (UINT)ATTACK_COMBO::FIRST;
			}
			else if (DeathAttackCombo == (UINT)ATTACK_COMBO::FIRST)
			{
				if (this->DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo2Right", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(330.f, 280.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(50.f, -60.f));
				}
				if (this->DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo2Left", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(-330.f, 280.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(-50.f, -60.f));
				}
				DeathAttackCombo = (UINT)ATTACK_COMBO::SECOND;
			}
			else if (DeathAttackCombo == (UINT)ATTACK_COMBO::SECOND)
			{
				if (this->DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo3Right", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(580.f, 60.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(0.f, -35.f));
				}
				if (this->DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo3Left", false);
					this->GetColliderVector()[1]->SetColliderScale(Vec(-570.f, 60.f));
					this->GetColliderVector()[1]->SetColliderOffSetPos(Vec(0.f, -35.f));
				}
				DeathAttackCombo = (UINT)ATTACK_COMBO::THIRD;
			}
			else if (DeathAttackCombo == (UINT)ATTACK_COMBO::THIRD)
			{
				if (this->DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo4Right", false);
					// 애니 프레임이 1부터 시작할때 10부터 14까지 아래 크기이고 나머지 부분은 작아야 한다.
				}
				if (this->DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathAttackBasicCombo4Left", false);
					
				}
				DeathAttackCombo = (UINT)ATTACK_COMBO::FOURTH;
			}

			
		}
		// Falling
		if (false == this->GetRigidBody()->GetBoolOnGround() && this->GetRigidBody()->GetVelocity().y < 0)
		{
			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				this->GetAnimator()->Play(L"DeathFallingRight", true);
			}
			if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				this->GetAnimator()->Play(L"DeathFallingLeft", true);
			}
		}

		// ToIdle
		if (CurAnimName == L"DeathRunRightToIdle" && CurAnim->IsFinish())
		{
			if (IsNone(KEY::LEFT) && IsNone(KEY::RIGHT))
			{
				this->m_bToIdle = true;
			}
		}

		if (CurAnimName == L"DeathRunLeftToIdle" && CurAnim->IsFinish())
		{
			if (IsNone(KEY::LEFT) && IsNone(KEY::RIGHT))
			{
				this->m_bToIdle = true;
			}
		}

		// Death Idled
		if (this->GetRigidBody()->GetBoolOnGround())
		{
			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				if (CurAnimName == L"DeathFallingRight") // Landing
				{
					this->GetAnimator()->Play(L"DeathLandingRight", false);
				}
				if (CurAnimName == L"DeathLandingRight" && CurAnim->IsFinish())
				{
					this->m_bToIdle = true;
				}

				if (m_bToIdle)
				{
					this->GetAnimator()->Play(L"DeathIdleRight", true);
					this->m_bToIdle = false;
					this->m_bOnIdle = true;
				}
			}
			else if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				if (CurAnimName == L"DeathFallingLeft") // Landing
				{
					this->GetAnimator()->Play(L"DeathLandingLeft", false);
				}
				if (CurAnimName == L"DeathLandingLeft" && CurAnim->IsFinish())
				{
					this->m_bToIdle = true;
				}

				if (m_bToIdle)
				{
					this->GetAnimator()->Play(L"DeathIdleLeft", true);
					this->m_bToIdle = false;
					this->m_bOnIdle = true;
				}
			}
		}


		// Death Sight and MoveStart
		if (IsTap(KEY::RIGHT))
		{
			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				if (m_bOnIdle == true)
				{
					this->GetAnimator()->Play(L"DeathIdleToRunRight", false);
				}
				else if (CurAnimName == L"DeathRunRightToIdle")
				{
					this->GetAnimator()->Play(L"DeathIdleToRunRight", false);
				}
			}
			else if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				if (m_bOnIdle == true)
				{
					this->GetAnimator()->Play(L"DeathIdleLeftToRight", false);
				}
				else // run
				{
					this->GetAnimator()->Play(L"DeathRunLeftToRunRight", false);
				}
				DeathSight = (UINT)DEATH_SIGHT::RIGHT;
			}
		}

		if (IsTap(KEY::LEFT))
		{
			if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				if (m_bOnIdle == true)
				{
					this->GetAnimator()->Play(L"DeathIdleToRunLeft", false);
				}
				else if( CurAnim->GetCurAnimName() == L"DeathRunLeftToIdle")
				{
					this->GetAnimator()->Play(L"DeathIdleToRunLeft", false);
				}
			}
			else if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				if (m_bOnIdle == true)
				{
					this->GetAnimator()->Play(L"DeathIdleRightToLeft", false);
				}
				else // run
				{
					this->GetAnimator()->Play(L"DeathRunRightToRunLeft", false);
				}
				DeathSight = (UINT)DEATH_SIGHT::LEFT;
			}
		}


		if (DeathState == (UINT)DEATH_STATE::DASH)
		{
			if (CurAnim->IsFinish())
			{
				if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathRunRightToIdle", false);
					this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
				}
				else if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathRunLeftToIdle", false);
					this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
				}
				DeathState = (UINT)DEATH_STATE::NONE;
			}
		}

		// Death Run
		if (IsPressed(KEY::RIGHT))
		{
			if (DeathAttackCombo == (UINT)ATTACK_COMBO::NONE)
			{
				vPos.x += m_fSpeed * DT;
			}

			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				if (CurAnimName == L"DeathLandingRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnimName == L"DeathRunLeftToRunRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnimName == L"DeathIdleToRunRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnimName == L"DeathIdleLeftToRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathIdleToRunRight", true);
				}
				if (CurAnimName == L"DeathIdleRight")
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnimName == L"DeathDashRight" && CurAnim->IsFinish())
				{
					this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
					DeathState = (UINT)DEATH_STATE::NONE;
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				
			}
			this->m_bOnIdle = false;
			this->m_bToIdle = false;
		}

		
		// Dash
		if (IsTap(KEY::LSHIFT))
		{
			if (DeathState != (UINT)DEATH_STATE::DASH)
			{
				if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathDashRight", false);
					if (CurAnimName == L"DeathRunRight")
					{
						this->GetRigidBody()->SetVelocity(Vec(1200, 0.f));
					}
					else
					{
						this->GetRigidBody()->SetVelocity(Vec(1400.f, 0.f));
					}
					this->DeathState = (UINT)DEATH_STATE::DASH;
				}
				else if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathDashLeft", false);
					if (CurAnimName == L"DeathRunLeft")
					{
						this->GetRigidBody()->SetVelocity(Vec(-1200.f, 0.f));
					}
					else
					{
						this->GetRigidBody()->SetVelocity(Vec(-1400.f, 0.f));
					}
					this->DeathState = (UINT)DEATH_STATE::DASH;
				}
			}
		}

		if (IsPressed(KEY::LEFT))
		{
			if (DeathAttackCombo == (UINT)ATTACK_COMBO::NONE)
			{
				vPos.x -= m_fSpeed * DT;
			}

			if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				if (CurAnimName == L"DeathLandingLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnimName == L"DeathRunRightToRunLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnimName == L"DeathIdleToRunLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnimName == L"DeathIdleRightToLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathIdleToRunLeft", false);
				}
				if (CurAnimName == L"DeathDashLeft" && CurAnim->IsFinish())
				{
					this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
					DeathState = (UINT)DEATH_STATE::NONE;
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnimName == L"DeathIdleLeft")
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
			}
			this->m_bOnIdle = false;
			this->m_bToIdle = false;
		}




		if (CurAnimName == L"DeathIdleToRunRight" && CurAnim->IsFinish())
		{
			this->GetAnimator()->Play(L"DeathRunRight", true);
		}
		// Run to Idle
		if (IsRelease(KEY::RIGHT))
		{
			if (CurAnimName == L"DeathRunLeft" || CurAnimName == L"DeathRunRightToRunLeft")
			{

			}
			else
			{
				if (true == this->GetRigidBody()->GetBoolOnGround())
				{
					this->GetAnimator()->Play(L"DeathRunRightToIdle", false);
				}
			}		}

		if (IsRelease(KEY::LEFT))
		{
			if (CurAnimName == L"DeathRunRight" || CurAnimName == L"DeathRunLeftToRunRight")
			{

			}
			else
			{
				if (true == this->GetRigidBody()->GetBoolOnGround())
				{
					this->GetAnimator()->Play(L"DeathRunLeftToIdle", false);
				}
			}
		}

		if (this->GetRigidBody()->GetBoolOnGround())
		{
			this->m_iJumpCount = 0;
		}

		if (m_iJumpCount < 1)
		{
			if (IsTap(KEY::SPACE))
			{
				Vec V = GetRigidBody()->GetVelocity();
				if (0.f < V.y) // jump in falling
				{
					GetRigidBody()->AddVelocity(Vec(0.f, -(V.y + 1600.f)));

					CEffectObject* _Effect = new CEffectObject(L"LandingDust");
					Instantiate(_Effect, Vec(this->GetPos().x, (this->GetPos().y) - 30.f), LAYER::BACKGROUNDOBJECT);

				}
				else // jump on ground
				{
					GetRigidBody()->AddVelocity(Vec(0.f, -1600.f));
					CEffectObject* _Effect = new CEffectObject(L"LandingDust");
					Instantiate(_Effect, Vec(this->GetPos().x, (this->GetPos().y) - 30.f), LAYER::BACKGROUNDOBJECT);
				}
				if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
				{
					this->GetAnimator()->Play(L"DeathJumpRight", false);
				}
				if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
				{
					this->GetAnimator()->Play(L"DeathJumpLeft", false);
				}
				m_iJumpCount++;
			}
		}
	}
	SetPos(vPos);

	CObject::ObjectTick();
}

void CPlayer::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

	CObject::ObjectRender(_dc, _pstring);
}

void CPlayer::CollisionBegin(CCollider* _pOther)
{
}

void CPlayer::Colliding(CCollider* _pOther)
{
}

void CPlayer::CollisionEnd(CCollider* _pOther)
{
}

