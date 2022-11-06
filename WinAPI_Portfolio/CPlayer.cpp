#include "pch.h"
#include "CPlayer.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CAnimation.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"


CPlayer::CPlayer()
	: m_pTexture(nullptr)
	, m_pDeathSpawn(nullptr)
	, m_fSpeed(300.f)
{
}

CPlayer::CPlayer(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pDeathSpawn(nullptr)
	, m_fSpeed(300.f)
{
	CreateAnimator();
	CreateSquareCollider(0);
	CreateRigidBody();

	//GetCollider()->SetColliderOffSetPos(Vec(-5.f, -25.f));
	//GetCollider()->SetColliderScale(Vec(80.f, 100.f));

	GetColliderMap().begin()->second->SetColliderOffSetPos(Vec(-5.f, -25.f));
	GetColliderMap().begin()->second->SetColliderScale(Vec(80.f, 100.f));

	m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);
	m_pDeathSpawn = CResourceMgr::GetInst()->FindTexture(L"DeathSpawn");
	//CTexture* m_pSpawn = CResourceMgr::GetInst()->LoadTexture(L"DeathSpawn", L"texture\\DeathSpawn.bmp");
	SetName(_pstring);
	GetAnimator()->CreateAnimation(L"DeathSpawn", m_pDeathSpawn, Vec(0.f, 0.f), Vec(150.f, 190.f), 100, 0.025f);
	/*GetAnimator()->FindAnimation(L"DeathSpawn")->Save(L"animation\\DeathSpawn.anim");*/
	
	// Gravity Setting
	//GetRigidBody()->SetGravity(true);
	//GetRigidBody()->SetGravityAccel(800.f);
	//GetRigidBody()->SetGravityVelocityLimit(700.f);
}

CPlayer::~CPlayer()
{
}


void CPlayer::ObjectTick()
{
	Vec vPos = GetPos();

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
		, (int)m_pTexture->Height()
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

