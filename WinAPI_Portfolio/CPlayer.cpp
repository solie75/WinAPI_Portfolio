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
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
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
	, m_fSpeed(500.f)
	, m_bKeyWorking(false)
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


	SetName(_pstring);
	GetAnimator()->CreateAnimation(L"DeathSpawn", m_pDeathSpawn, Vec(0.f, 0.f), Vec(150.f, 190.f), 100, 0.025f);
	GetAnimator()->CreateAnimation(L"DeathIdleRight", m_pDeathIdleRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeft", m_pDeathIdleLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleLeftToRight", m_pDeathIdleLeftToRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleRightToLeft", m_pDeathIdleRightToLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunRight", m_pDeathIdleToRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathIdleToRunLeft", m_pDeathIdleToRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunRightToIdle", m_pDeathRunRightToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunLeftToIdle", m_pDeathRunLeftToIdle, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunRight", m_pDeathRunRight, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	GetAnimator()->CreateAnimation(L"DeathRunLeft", m_pDeathRunLeft, Vec(0.f, 0.f), Vec(98.f, 128.f), 60, 0.04f);
	
	//GetAnimator()->FindAnimation(L"DeathIdleRight")->Save(L"animation\\DeathIdleRight.anim");
	//GetAnimator()->FindAnimation(L"DeathIdleLeft")->Save(L"animation\\DeathIdleLeft.anim");
	//GetAnimator()->FindAnimation(L"DeathSpawn")->Save(L"animation\\DeathSpawn.anim");
	//GetAnimator()->FindAnimation(L"DeathIdleRight")->Save(L"animation\\DeathIdleRight.anim");

	/*GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");*/


	// Gravity Setting
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(500.f);
	GetRigidBody()->SetGravityVelocityLimit(700.f);
}

CPlayer::~CPlayer()
{
}


void CPlayer::ObjectTick()
{
	Vec vPos = GetPos();

	if (GetKeyWorking() == true)
	{
		if (IsPressed(KEY::RIGHT))
		{

			vPos.x += m_fSpeed * DT;
		}
		if (IsPressed(KEY::LEFT))
		{

			vPos.x -= m_fSpeed * DT;
		}
		if (IsPressed(KEY::UP))
		{
			vPos.y -= m_fSpeed * DT;
		}
		if (IsPressed(KEY::DOWN))
		{
			vPos.y += m_fSpeed * DT;
		}

		if (IsTap(KEY::RIGHT))
		{
			this->GetAnimator()->Play(L"DeathIdleRight", true);
		}
		if (IsTap(KEY::LEFT))
		{
			this->GetAnimator()->Play(L"DeathIdleLeft", true);
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
				GetRigidBody()->AddVelocity(Vec(0.f, -(V.y + 400.f)));
			}
			else
			{
				GetRigidBody()->AddVelocity(Vec(0.f, -400.f));
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

	/*Vec vLeftTop = Vec(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	TransparentBlt(_dc
		, (int)vLeftTop.x
		, (int)vLeftTop.y
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()www
		, RGB(255, 255, 255)
	);*/

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

