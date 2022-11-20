#include "pch.h"
#include "CGhostWoman.h"
#include "CResourceMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"

CGhostWoman::CGhostWoman(wstring _pstring)
	: m_pGhostWomanIdleRight(nullptr)
	, m_pGhostWomanIdleLeft(nullptr)
	, m_pGhostWomanLeftToRight(nullptr)
	, m_pGhostWomanRightToLeft(nullptr)
	, m_pGhostWomanAttackRight(nullptr)
	, m_pGhostWomanAttackLeft(nullptr)
	, m_pGhostWomanHitRight(nullptr)
	, m_pGhostWomanHitLeft(nullptr)
	, m_GhostWoman_State((UINT)GhostWoman_State::NONE)
	, m_bCollidingWall(false)
{
	SetName(_pstring);
	CreateAnimator();
	CreateSquareCollider();
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::OBJECT);
	CreateRigidBody();

	// Gravity Setting
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(1200.f);
	GetRigidBody()->SetGravityVelocityLimit(1400.f);

	m_pGhostWomanIdleRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanIdleRight", L"texture\\Ghost_Woman_Idle_Right.bmp");
	m_pGhostWomanIdleLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanIdleLeft", L"texture\\Ghost_Woman_Idle_Left.bmp");
	m_pGhostWomanLeftToRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanLeftToRight", L"texture\\Ghost_Woman_RightToLeft.bmp");
	m_pGhostWomanRightToLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanRightToLeft", L"texture\\Ghost_Woman_LeftToRight.bmp");
	m_pGhostWomanAttackRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanAttackRight", L"texture\\Ghost_Woman_Attack_Right.bmp");
	m_pGhostWomanAttackLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanAttackLeft", L"texture\\Ghost_Woman_Attack_Left.bmp");
	m_pGhostWomanHitRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanHitRight", L"texture\\Ghost_Woman_Hit_Right.bmp");
	m_pGhostWomanHitLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanHitLeft", L"texture\\Ghost_Woman_Hit_Left.bmp");

	GetAnimator()->CreateAnimation(L"GhostWomanIdleRight", m_pGhostWomanIdleRight, Vec(0.f, 0.f), Vec(80.f, 220.f), Vec(0.f, 0.f), 12, 0.08f);
	GetAnimator()->CreateAnimation(L"GhostWomanIdleLeft", m_pGhostWomanIdleLeft, Vec(0.f, 0.f), Vec(80.f, 220.f), Vec(0.f, 0.f), 12, 0.08f);
	GetAnimator()->CreateAnimation(L"GhostWomanLeftToRight", m_pGhostWomanLeftToRight, Vec(0.f, 0.f), Vec(70.f, 210.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostWomanRightToLeft", m_pGhostWomanRightToLeft, Vec(0.f, 0.f), Vec(70.f, 210.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostWomanAttackRight", m_pGhostWomanAttackRight, Vec(0.f, 0.f), Vec(90.f, 210.f), Vec(0.f, 0.f), 21, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostWomanAttackLeft", m_pGhostWomanAttackLeft, Vec(0.f, 0.f), Vec(90.f, 210.f), Vec(0.f, 0.f), 21, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostWomanHitRight", m_pGhostWomanHitRight, Vec(0.f, 0.f), Vec(90.f, 230.f), Vec(0.f, 0.f), 41, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostWomanHitLeft", m_pGhostWomanHitLeft, Vec(0.f, 0.f), Vec(90.f, 230.f), Vec(0.f, 0.f), 41, 0.04f);

	GetAnimator()->Play(L"GhostWomanIdleRight", true);
	SetObjectSight((UINT)SIGHT::RIGHT);

	GetColliderVector()[0]->SetColliderOffSetPos(Vec(-5.f, 0.f));
	Vec _CurAnimSize = GetAnimator()->GetCurAnimation()->GetAnimCurSize();
	GetColliderVector()[0]->SetColliderScale(_CurAnimSize); // 사실 여기에서는 Idle 의 사이즈를 하드코딩해도 된다.
	m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
	this->SetObjectSpeed(250.f);


}

CGhostWoman::~CGhostWoman()
{
}


void CGhostWoman::ObjectTick()
{
	Vec _vThisPos = this->GetPos();
	CAnimation* _CurAnim = this->GetAnimator()->GetCurAnimation();
	wstring _CurAnimName = this->GetAnimator()->GetCurAnimation()->GetCurAnimName();
	
	if (m_GhostWoman_State == (UINT)GhostWoman_State::IDLE)
	{
		if (GetObjectSight() == (UINT)SIGHT::RIGHT)
		{
			if (_CurAnimName != L"GhostWomanIdleRight")
			{
				this->GetAnimator()->Play(L"GhostWomanIdleRight", true);
			}
			_vThisPos.x += this->GetObjectSpeed() * DT;
		}
		else if (GetObjectSight() == (UINT)SIGHT::LEFT)
		{
			if (_CurAnimName != L"GhostWomanIdleLeft")
			{
				this->GetAnimator()->Play(L"GhostWomanIdleLeft", true);
			}
			_vThisPos.x -= this->GetObjectSpeed() * DT;
		}
	}
	if (this->m_GhostWoman_State == (UINT)GhostWoman_State::HIT && this->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		this->m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
	}

	//if()
	this->SetPos(_vThisPos);

	CMonster::ObjectTick();
}

void CGhostWoman::ObjectRender(HDC _dc, wstring _pstring)
{
	CMonster::ObjectRender(_dc, _pstring);
}

void CGhostWoman::CollisionBegin(CCollider* _pOther)
{
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		m_GhostWoman_State = (UINT)GhostWoman_State::NONE;
		this->SetObjectSpeed(0.f);
		this->GetRigidBody()->SetVelocity(Vec(0.f, 0.f));
		this->m_bCollidingWall = true;
	}
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
	{
		if (_pOther-> GetOwner()->GetPos().x > this->GetPos().x)
		{
			this->GetAnimator()->Play(L"GhostWomanHitRight", false);
			if (this->m_bCollidingWall == true)
			{
				this->GetRigidBody()->AddVelocity(Vec(0.f, -300.f));
			}
			else
			{
				this->GetRigidBody()->AddVelocity(Vec(-100.f, -300.f));
			}
			this->SetObjectSight((UINT)SIGHT::RIGHT);
			this->m_GhostWoman_State = (UINT)GhostWoman_State::HIT;
		}
		if (_pOther->GetOwner()->GetPos().x < this->GetPos().x)
		{
			this->GetAnimator()->Play(L"GhostWomanHitLeft", false);
			if (this->m_bCollidingWall == true)
			{
				this->GetRigidBody()->AddVelocity(Vec(0.f, -300.f));
			}
			else
			{
				this->GetRigidBody()->AddVelocity(Vec(100.f, -300.f));
			}
			
			this->SetObjectSight((UINT)SIGHT::LEFT);
			this->m_GhostWoman_State = (UINT)GhostWoman_State::HIT;
		}
	}
}

void CGhostWoman::Colliding(CCollider* _pOther)
{
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		if (_pOther->GetColliderFinalPos().x > this->GetPos().x)
		{
			this->SetObjectSight((UINT)SIGHT::LEFT);
			m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
			this->SetObjectSpeed(250.f);
		}
		else if (_pOther->GetColliderScale().x < this->GetPos().x)
		{
			this->SetObjectSight((UINT)SIGHT::RIGHT);
			m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
			this->SetObjectSpeed(250.f);
		}
	}
	
	//if()
}

void CGhostWoman::CollisionEnd(CCollider* _pOther)
{
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		this->m_bCollidingWall = false;
	}
}

