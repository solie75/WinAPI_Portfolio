#include "pch.h"
#include "CBackgroundObject.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"

CBackgroundObject::CBackgroundObject()
	: m_pTexture(nullptr)
	, m_pElevatorClose(nullptr)
	, m_pElevatorOpen(nullptr)
	, m_pElevatorDigIn(nullptr)
	, m_pElevatorDigOut(nullptr)
	, m_bShow(false)
{
}

CBackgroundObject::CBackgroundObject(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pElevatorClose(nullptr)
	, m_pElevatorDigIn(nullptr)
	, m_pElevatorDigOut(nullptr)
	, m_bShow(false)
{
	SetName(_pstring);
	CreateAnimator();

	CResourceMgr::GetInst()->LoadTexture(L"Elevator", L"texture\\OfficeElevator.bmp");

	m_pElevatorClose = CResourceMgr::GetInst()->LoadTexture(L"ElevatorClose", L"texture\\ElevatorClose.bmp");
	m_pElevatorOpen = CResourceMgr::GetInst()->LoadTexture(L"ElevatorOpen", L"texture\\ElevatorOpen.bmp");
	m_pElevatorDigIn = CResourceMgr::GetInst()->LoadTexture(L"ElevatorDigIn", L"texture\\ElevatorDigIn.bmp");
	m_pElevatorDigOut = CResourceMgr::GetInst()->LoadTexture(L"ElevatorDigOut", L"texture\\ElevatorDigOut.bmp");
	GetAnimator()->CreateAnimation(L"ElevatorClose", m_pElevatorClose, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 13, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorOpen", m_pElevatorOpen, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 14, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorDigIn", m_pElevatorDigIn, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 23, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorDigOut", m_pElevatorDigOut, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 23, 0.04f);
	
}

CBackgroundObject::~CBackgroundObject()
{
}


void CBackgroundObject::ObjectTick()
{
	CObject::ObjectTick();
}

void CBackgroundObject::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

	m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);

	if (m_bShow)
	{
		TransparentBlt(_dc
			, (int)(vPos.x - m_pTexture->Width() / 2.f)
			, (int)(vPos.y - m_pTexture->Height() / 2.f)
			, (int)m_pTexture->Width()
			, (int)m_pTexture->Height()
			, m_pTexture->GetDC()
			, 0, 0
			, (int)m_pTexture->Width()
			, (int)m_pTexture->Height()
			, RGB(253, 253, 254)
		);
	}
	
	CObject::ObjectRender(_dc, _pstring);
}

