#include "pch.h"
#include "CTrigger.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"
#include "CCollider.h"

CTrigger::CTrigger()
	: m_pTexture(nullptr)
	, Trigger(false)
{
}

CTrigger::CTrigger(wstring _pstring)
	: m_pTexture(nullptr)
	, Trigger(false)
{
	SetName(_pstring);
	CreateSquareCollider();
	GetColliderVector()[0]->SetColliderScale(Vec(50.f, 1000.f));
}

CTrigger::~CTrigger()
{
}


void CTrigger::ObjectTick()
{
	CObject::ObjectTick();
}

void CTrigger::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}

void CTrigger::CollisionBegin(CCollider* _pOther)
{
	// 충돌할 경우 Elevator Appear 시작
	
	/*if (this->GetName() == L"ElevatorAppearTrigger")
	{
		
	}*/
	Trigger = true;
}

void CTrigger::Colliding(CCollider* _pOther)
{
}

void CTrigger::CollisionEnd(CCollider* _pOther)
{
	SetDead();
}
