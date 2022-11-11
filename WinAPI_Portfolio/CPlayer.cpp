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
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
	, m_bToIdle(false)
	, m_bOnIdle(false)
	, DeathSight((UINT)DEATH_SIGHT::RIGHT)
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
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
	, m_bToIdle(false)
	, m_bOnIdle(false)
	, DeathSight((UINT)DEATH_SIGHT::RIGHT)
{
	CreateAnimator();
	CreateSquareCollider();
	CreateRigidBody();

	//GetCollider()->SetColliderOffSetPos(Vec(-5.f, -25.f));
	//GetCollider()->SetColliderScale(Vec(80.f, 100.f));

	//GetColliderMap().begin()->second->SetColliderOffSetPos(Vec(-5.f, -25.f));
	//GetColliderMap().begin()->second->SetColliderScale(Vec(80.f, 100.f));

	GetColliderVector()[0]->SetColliderOffSetPos(Vec(-5.f, -25.f));
	GetColliderVector()[0]->SetColliderScale(Vec(80.f, 100.f));

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


	SetName(_pstring);
	GetAnimator()->CreateAnimation(L"DeathSpawn", m_pDeathSpawn, Vec(0.f, 0.f), Vec(130.f, 166.f), 99, 0.025f);
	GetAnimator()->CreateAnimation(L"DeathIdleRight", m_pDeathIdleRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeft", m_pDeathIdleLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeftToRight", m_pDeathIdleLeftToRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathIdleRightToLeft", m_pDeathIdleRightToLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunRight", m_pDeathIdleToRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 4, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunLeft", m_pDeathIdleToRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 4, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunRightToIdle", m_pDeathRunRightToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), 9, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunLeftToIdle", m_pDeathRunLeftToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), 9, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunRight", m_pDeathRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 5, 0.08f);
	GetAnimator()->CreateAnimation(L"DeathRunLeft", m_pDeathRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 5, 0.08f);
	GetAnimator()->CreateAnimation(L"DeathRunLeftToRunRight", m_pDeathRunLeftToRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathRunRightToRunLeft", m_pDeathRunRightToRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathJumpRight", m_pDeathJumpRight, Vec(0.f, 0.f), Vec(120.f, 170.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathJumpLeft", m_pDeathJumpLeft, Vec(0.f, 0.f), Vec(120.f, 170.f), 7, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathLandingRight", m_pDeathLandingRight, Vec(0.f, 0.f), Vec(116.f, 130.f), 4, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathLandingLeft", m_pDeathLandingLeft, Vec(0.f, 0.f), Vec(116.f, 130.f), 4, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathFallingRight", m_pDeathFallingRight, Vec(0.f, 0.f), Vec(114.f, 116.f), 6, 0.02f);
	GetAnimator()->CreateAnimation(L"DeathFallingLeft", m_pDeathFallingLeft, Vec(0.f, 0.f), Vec(114.f, 116.f), 6, 0.02f);
	
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

	// after animation
	if (true == GetKeyWorking())
	{
		CAnimation* CurAnim = this->GetAnimator()->GetCurAnimation();

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
		if (CurAnim->GetCurAnimName() == L"DeathRunRightToIdle" && CurAnim->IsFinish())
		{
			if (IsNone(KEY::LEFT) && IsNone(KEY::RIGHT))
			{
				this->m_bToIdle = true;
			}
		}

		if (CurAnim->GetCurAnimName() == L"DeathRunLeftToIdle" && CurAnim->IsFinish())
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
				if (CurAnim->GetCurAnimName() == L"DeathFallingRight") // Landing
				{
					this->GetAnimator()->Play(L"DeathLandingRight", false);
				}
				if (CurAnim->GetCurAnimName() == L"DeathLandingRight" && CurAnim->IsFinish())
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
				if (CurAnim->GetCurAnimName() == L"DeathFallingLeft") // Landing
				{
					this->GetAnimator()->Play(L"DeathLandingLeft", false);
				}
				if (CurAnim->GetCurAnimName() == L"DeathLandingLeft" && CurAnim->IsFinish())
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
				else if (CurAnim->GetCurAnimName() == L"DeathRunRightToIdle")
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









		// Death Run
		if (IsPressed(KEY::RIGHT))
		{
			vPos.x += m_fSpeed * DT;
			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				if (CurAnim->GetCurAnimName() == L"DeathLandingRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathRunLeftToRunRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathIdleToRunRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunRight", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathIdleLeftToRight" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathIdleToRunRight", true);
				}
			}
			this->m_bOnIdle = false;
			this->m_bToIdle = false;
		}

		if (IsPressed(KEY::LEFT))
		{
			vPos.x -= m_fSpeed * DT;
			if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				if (CurAnim->GetCurAnimName() == L"DeathLandingLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathRunRightToRunLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathIdleToRunLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathRunLeft", true);
				}
				if (CurAnim->GetCurAnimName() == L"DeathIdleRightToLeft" && CurAnim->IsFinish())
				{
					this->GetAnimator()->Play(L"DeathIdleToRunLeft", false);
				}
			}
			this->m_bOnIdle = false;
			this->m_bToIdle = false;
		}




		if (CurAnim->GetCurAnimName() == L"DeathIdleToRunRight" && CurAnim->IsFinish())
		{
			this->GetAnimator()->Play(L"DeathRunRight", true);
		}
		// Run to Idle
		if (IsRelease(KEY::RIGHT))
		{
			if (CurAnim->GetCurAnimName() == L"DeathRunLeft" || CurAnim->GetCurAnimName() == L"DeathRunRightToRunLeft")
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
			if (CurAnim->GetCurAnimName() == L"DeathRunRight" || CurAnim->GetCurAnimName() == L"DeathRunLeftToRunRight")
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























		if (IsTap(KEY::K))
		{
			vPos.x -= 100.f * DT;
		}
		if (IsTap(KEY::L))
		{
			vPos.x += 100.f * DT;
		}


		if (IsTap(KEY::SPACE))
		{
			Vec V = GetRigidBody()->GetVelocity();
			if (0.f < V.y)
			{
				GetRigidBody()->AddVelocity(Vec(0.f, -(V.y + 1600.f)));
			}
			else
			{
				GetRigidBody()->AddVelocity(Vec(0.f, -1600.f));
			}
			if (DeathSight == (UINT)DEATH_SIGHT::RIGHT)
			{
				this->GetAnimator()->Play(L"DeathJumpRight", false);
			}
			if (DeathSight == (UINT)DEATH_SIGHT::LEFT)
			{
				this->GetAnimator()->Play(L"DeathJumpLeft", false);
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

