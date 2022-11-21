#include "pch.h"
#include "CGhostWoman.h"
#include "CResourceMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "CMonsterProjectile.h"
//#include <cmath>

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
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::GHOSTWOMAN);
	AddSquareCollider();
	GetColliderVector()[1]->SetColliderType((UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG);
	GetColliderVector()[1]->SetColliderScale(Vec(850.f, 850.f));
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

	//GetColliderVector()[0]->SetColliderOffSetPos(Vec(-5.f, 0.f));
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

	if (_CurAnimName == L"GhostWomanAttackRight" || _CurAnimName == L"GhostWomanAttackLeft")
	{
		if (_CurAnim->IsFinish())
		{
			m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
		}
	}

	// Projectile 발사
	if (_CurAnimName == L"GhostWomanAttackRight" || _CurAnimName == L"GhostWomanAttackLeft")
	{
		if (GetAnimator()->GetCurAnimation()->GetAnimCurFrame() == 7)
		{
			TargetDegree;
			if (-112 <= TargetDegree && TargetDegree < -67)
			{
				CMonsterProjectile* _MonsterProjectile1 = new CMonsterProjectile(L"Projectile1");
				Instantiate(_MonsterProjectile1, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile1->m_vTargetPos = m_vTarget;
			}
			else if (-67 <= TargetDegree && TargetDegree < -22)
			{
				CMonsterProjectile* _MonsterProjectile2 = new CMonsterProjectile(L"Projectile2");
				Instantiate(_MonsterProjectile2, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile2->m_vTargetPos = m_vTarget;
			}
			else if (-22 <= TargetDegree && TargetDegree < 22)
			{
				CMonsterProjectile* _MonsterProjectile3 = new CMonsterProjectile(L"Projectile3");
				Instantiate(_MonsterProjectile3, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile3->m_vTargetPos = m_vTarget;
			}
			else if (22 <= TargetDegree && TargetDegree < 67)
			{
				CMonsterProjectile* _MonsterProjectile4 = new CMonsterProjectile(L"Projectile4");
				Instantiate(_MonsterProjectile4, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile4->m_vTargetPos = m_vTarget;
			}
			else if (67 <= TargetDegree && TargetDegree < 112)
			{
				CMonsterProjectile* _MonsterProjectile5 = new CMonsterProjectile(L"Projectile5");
				Instantiate(_MonsterProjectile5, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile5->m_vTargetPos = m_vTarget;
			}
			else if (112 <= TargetDegree && TargetDegree < 157)
			{
				CMonsterProjectile* _MonsterProjectile6 = new CMonsterProjectile(L"Projectile6");
				Instantiate(_MonsterProjectile6, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile6->m_vTargetPos = m_vTarget;
			}
			else if (157 <= TargetDegree || TargetDegree < -157)
			{
				CMonsterProjectile* _MonsterProjectile7 = new CMonsterProjectile(L"Projectile7");
				Instantiate(_MonsterProjectile7, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile7->m_vTargetPos = m_vTarget;
			}
			else if (-157 <= TargetDegree && TargetDegree < -112)
			{
				CMonsterProjectile* _MonsterProjectile8 = new CMonsterProjectile(L"Projectile8");
				Instantiate(_MonsterProjectile8, this->GetPos(), LAYER::MONSTER_PROJECTILE);
				_MonsterProjectile8->m_vTargetPos = m_vTarget;
			}
		}
	}

	// Idle
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

	// Hit
	if (this->m_GhostWoman_State == (UINT)GhostWoman_State::HIT && this->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		this->m_GhostWoman_State = (UINT)GhostWoman_State::IDLE;
	}


	// Attack Animation Start
	if (this->m_GhostWoman_State == (UINT)GhostWoman_State::ATTACK_LONG)
	{
		
		if (GetObjectSight() == (UINT)SIGHT::RIGHT)
		{
			if (_CurAnimName != L"GhostWomanAttackRight")
			{
				GetAnimator()->Play(L"GhostWomanAttackRight", false);
			}
		}
		if (GetObjectSight() == (UINT)SIGHT::LEFT)
		{
			if (_CurAnimName != L"GhostWomanAttackLeft")
			{
				GetAnimator()->Play(L"GhostWomanAttackLeft", false);
			}
		}
	}







	//if()
	this->SetPos(_vThisPos);

	CMonster::ObjectTick();
}

void CGhostWoman::ObjectRender(HDC _dc, wstring _pstring)
{
	CMonster::ObjectRender(_dc, _pstring);
}

void CGhostWoman::BeginOverlap(CCollider* _pOther)
{

	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		//m_GhostWoman_State = (UINT)GhostWoman_State::NONE;
		//this->SetObjectSpeed(0.f);
		this->m_bCollidingWall = true;
		if (_pOther->GetOwner()->GetPos().x > this->GetPos().x)
		{
			SetPos(Vec(_pOther->GetColliderFinalPos().x - _pOther->GetColliderScale().x / 2.f - this->GetScale().x / 2.f + 2.f, GetPos().y));
			SetObjectSight((UINT)SIGHT::LEFT);
		}
		if (_pOther->GetOwner()->GetPos().x < this->GetPos().x)
		{
			SetPos(Vec(_pOther->GetColliderFinalPos().x + _pOther->GetColliderScale().x / 2.f + this->GetScale().x / 2.f , GetPos().y));
			//SetPos(Vec(65.f, 1041.f));
			SetObjectSight((UINT)SIGHT::RIGHT);
		}
	}

	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	{
		Vec _thisScale = this->GetColliderVector()[1]->GetColliderScale();
		Vec _otherScale = _pOther->GetColliderScale();
		Vec _thisPos = this->GetColliderVector()[1]->GetColliderFinalPos();
		Vec _otherPos = _pOther->GetColliderFinalPos();

		

		/*if (fabsf(_thisPos.x - _otherPos.x)/2.f <= (_thisScale.x / 2.f + _otherScale.x / 2.f) / 2.f && fabsf(_thisPos.y - _otherPos.y) / 2.f <= (_thisScale.y / 2.f + _otherScale.y / 2.f) / 2.f)
		{
			TargetDegree = atan2(_otherPos.y - _thisPos.y, _otherPos.x - _thisPos.x) * 180.f / PI;
			m_vTarget = Vec(_otherPos.x - _thisPos.x, _otherPos.y - _thisPos.y);
			this->m_GhostWoman_State = (UINT)GhostWoman_State::ATTACK_SHORT;
			if (_thisPos.x < _otherPos.x)
			{
				SetObjectSight((UINT)SIGHT::RIGHT);
			}
			if (_otherPos.x < _thisPos.x)
			{
				SetObjectSight((UINT)SIGHT::LEFT);
			}
		}*/
		/*if (fabsf(_thisPos.x - _otherPos.x) <= (_thisScale.x / 2.f + _otherScale.x / 2.f) && fabsf(_thisPos.y - _otherPos.y) <= (_thisScale.y / 2.f + _otherScale.y / 2.f))
		{*/
			TargetDegree = atan2(_otherPos.y - _thisPos.y, _otherPos.x - _thisPos.x) * 180.f / PI;
			m_vTarget = Vec(_otherPos.x - _thisPos.x, _otherPos.y - _thisPos.y);
			this->m_GhostWoman_State = (UINT)GhostWoman_State::ATTACK_LONG;
			if (_thisPos.x < _otherPos.x)
			{
				SetObjectSight((UINT)SIGHT::RIGHT);
			}
			if (_otherPos.x < _thisPos.x)
			{
				SetObjectSight((UINT)SIGHT::LEFT);
			}
		/*}*/
		m_vTarget.Normalize();

		




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

void CGhostWoman::OnOverlap(CCollider* _pOther)
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
}

void CGhostWoman::EndOverlap(CCollider* _pOther)
{
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		this->m_bCollidingWall = false;
	}
}

