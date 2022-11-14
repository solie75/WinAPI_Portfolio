#include "pch.h"
#include "CNPC.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"

CNPC::CNPC()
	: m_pTexture(nullptr)
	, m_pElevatorAppear(nullptr)
{
}

CNPC::CNPC(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pElevatorAppear(nullptr)
{
	SetName(_pstring);
	CreateSquareCollider();
	CreateAnimator();

	m_pElevatorAppear = CResourceMgr::GetInst()->LoadTexture(L"OfficeElevatorAppear", L"texture\\ElevatorAppear.bmp");
	GetAnimator()->CreateAnimation(L"OfficeElevatorAppear", m_pElevatorAppear, Vec(0.f, 0.f), Vec(520.f, 370.f), Vec(0.f, 0.f), 87, 0.025f);
}

CNPC::~CNPC()
{
}


void CNPC::ObjectTick()
{
	CObject::ObjectTick();
}

void CNPC::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}
