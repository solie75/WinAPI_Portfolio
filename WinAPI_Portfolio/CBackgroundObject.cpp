#include "pch.h"
#include "CBackgroundObject.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"

CBackgroundObject::CBackgroundObject()
	: m_pTexture(nullptr)
	, m_pElevatorClose(nullptr)
	, m_pElevatorDigIn(nullptr)
	, m_bShow(false)
{
}

CBackgroundObject::CBackgroundObject(wstring _pstring)
	: m_pTexture(nullptr)
	, m_pElevatorClose(nullptr)
	, m_pElevatorDigIn(nullptr)
	,m_bShow(false)
{
	SetName(_pstring);
	CreateAnimator();

	m_pElevatorClose = CResourceMgr::GetInst()->LoadTexture(L"ElevatorClose", L"texture\\ElevatorClose.bmp");
	m_pElevatorDigIn = CResourceMgr::GetInst()->LoadTexture(L"ElevatorDigIn", L"texture\\ElevatorDigIn.bmp");
	GetAnimator()->CreateAnimation(L"ElevatorClose", m_pElevatorClose, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 13, 0.04f);
	GetAnimator()->CreateAnimation(L"ElevatorDigIn", m_pElevatorDigIn, Vec(0.f, 0.f), Vec(270.f, 360.f), Vec(0.f, 0.f), 23, 0.04f);
	
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

	Vec vLeftTop = Vec(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	if (m_bShow)
	{
		TransparentBlt(_dc
			, (int)vLeftTop.x
			, (int)vLeftTop.y
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

