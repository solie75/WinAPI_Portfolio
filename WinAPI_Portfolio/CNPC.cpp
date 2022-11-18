#include "pch.h"
#include "CNPC.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CBackgroundObject.h"

CNPC::CNPC()
	: m_pTexture(nullptr)
	, m_pElevatorAppear(nullptr)
	, m_pElevatorIdle(nullptr)
	, m_pElevatorDisappear(nullptr)
	, m_bInteraction(false)
	, m_pInteractionTexture(nullptr)
	, m_pInteract(nullptr)
	, vDiffWithPlayer(Vec(0.f, 0.f))
{
}

CNPC::CNPC(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pElevatorAppear(nullptr)
	, m_pElevatorIdle(nullptr)
	, m_pElevatorDisappear(nullptr)
	, m_bInteraction(false)
	, m_pInteractionTexture(nullptr)
	, m_pInteract(nullptr)
	, vDiffWithPlayer(Vec(0.f, 0.f))
{
	SetName(_pstring);
	CreateSquareCollider();
	CreateAnimator();

	GetColliderVector()[0]->SetColliderScale(Vec(260.f, 370.f));
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::OBJECT);


	m_pElevatorAppear = CResourceMgr::GetInst()->LoadTexture(L"ElevatorAppear", L"texture\\ElevatorAppear.bmp");
	m_pElevatorIdle = CResourceMgr::GetInst()->LoadTexture(L"ElevatorIdle", L"texture\\ElevatorIdle.bmp");
	m_pInteractionTexture = CResourceMgr::GetInst()->LoadTexture(L"InteractionKey", L"texture\\Key_F.bmp");
	m_pElevatorDisappear = CResourceMgr::GetInst()->LoadTexture(L"ElevatorDisappear", L"texture\\ElevatorDisappear.bmp");
	GetAnimator()->CreateAnimation(L"ElevatorAppear", m_pElevatorAppear, Vec(0.f, 0.f), Vec(520.f, 370.f), Vec(20.f, 20.f), 87, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorIdle", m_pElevatorIdle, Vec(0.f, 0.f), Vec(520.f, 370.f), Vec(0.f, 50.f), 94, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorDisappear", m_pElevatorDisappear, Vec(0.f, 0.f), Vec(520.f, 370.f), Vec(0.f, 50.f), 22, 0.04f);

	m_pInteract = new CBackgroundObject(L"InteractionKey");
	Instantiate(m_pInteract, Vec(2010.f, 400.f), LAYER::BACKGROUNDOBJECT);
}

CNPC::~CNPC()
{
}


void CNPC::ObjectTick()
{
	if (m_bInteraction)
	{
		m_pInteract->SetBoolShow(true);
	}
	else
	{
		m_pInteract->SetBoolShow(false);
	}
	CObject::ObjectTick();
}

void CNPC::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}

void CNPC::CollisionBegin(CCollider* _pOther)
{
	m_bInteraction = true;
}

void CNPC::Colliding(CCollider* _pOther)
{
}

void CNPC::CollisionEnd(CCollider* _pOther)
{
	m_bInteraction = false;
}
