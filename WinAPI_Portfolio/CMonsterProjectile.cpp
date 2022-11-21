#include "pch.h"
#include "CMonsterProjectile.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMonsterProjectile::CMonsterProjectile(wstring _pstring)
	: m_pProjectile1(nullptr)
	, m_pProjectile2(nullptr)
	, m_pProjectile3(nullptr)
	, m_pProjectile4(nullptr)
	, m_pProjectile5(nullptr)
	, m_pProjectile6(nullptr)
	, m_pProjectile7(nullptr)
	, m_pProjectile8(nullptr)
	, OnCrush(false)
	, m_fSpeed(450.f)
{
	
	SetName(_pstring);
	CreateAnimator();
	CreateSquareCollider();
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::MONSTER_PROJECTILE);

	m_pProjectile1 = CResourceMgr::GetInst()->LoadTexture(L"Projectile1", L"texture\\Ghost_Projectile1.bmp");
	m_pProjectile2 = CResourceMgr::GetInst()->LoadTexture(L"Projectile2", L"texture\\Ghost_Projectile2.bmp");
	m_pProjectile3 = CResourceMgr::GetInst()->LoadTexture(L"Projectile3", L"texture\\Ghost_Projectile3.bmp");
	m_pProjectile4 = CResourceMgr::GetInst()->LoadTexture(L"Projectile4", L"texture\\Ghost_Projectile4.bmp");
	m_pProjectile5 = CResourceMgr::GetInst()->LoadTexture(L"Projectile5", L"texture\\Ghost_Projectile5.bmp");
	m_pProjectile6 = CResourceMgr::GetInst()->LoadTexture(L"Projectile6", L"texture\\Ghost_Projectile6.bmp");
	m_pProjectile7 = CResourceMgr::GetInst()->LoadTexture(L"Projectile7", L"texture\\Ghost_Projectile7.bmp");
	m_pProjectile8 = CResourceMgr::GetInst()->LoadTexture(L"Projectile8", L"texture\\Ghost_Projectile8.bmp");

	GetAnimator()->CreateAnimation(L"Projectile1", m_pProjectile1, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile2", m_pProjectile2, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile3", m_pProjectile3, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile4", m_pProjectile4, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile5", m_pProjectile5, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile6", m_pProjectile6, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile7", m_pProjectile7, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);
	GetAnimator()->CreateAnimation(L"Projectile8", m_pProjectile8, Vec(0.f, 0.f), Vec(270.f, 270.f), Vec(0.f, 0.f), 10, 0.04f);

	GetAnimator()->Play(_pstring, true);
}

CMonsterProjectile::~CMonsterProjectile()
{
}


void CMonsterProjectile::ObjectTick()
{
	Vec _v = GetPos();
	_v.x += m_vTargetPos.x * m_fSpeed * DT;
	_v.y += m_vTargetPos.y * m_fSpeed * DT;

	SetPos(_v);

	if (OnCrush)
	{
		SetDead();
	}
	CObject::ObjectTick();
}

void CMonsterProjectile::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}

void CMonsterProjectile::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	{
		OnCrush = true;
	}
}

void CMonsterProjectile::OnOverlap(CCollider* _pOther)
{
}

void CMonsterProjectile::EndOverlap(CCollider* _pOther)
{
}

