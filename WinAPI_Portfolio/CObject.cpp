#include "pch.h"
#include "CObject.h"
#include "CEventMgr.h"

#include "CAnimator.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
	, m_pAnimator(nullptr)
{ 
}

CObject::CObject(const CObject& _other)
	: CEntity(_other)
	, m_vPos()
	, m_vScale{}
	, m_bDead(false)
	, m_pAnimator(nullptr)
{
	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = _other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}
}

CObject::~CObject()
{
	DEL(m_pAnimator);
}

void CObject::ObjectTick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentTick();
	}
}

void CObject::Final_Tick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Final_Tick();
	}
}

void CObject::ObjectRender(HDC _dc, wstring _pstring)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentRender(_dc);
	}
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObject::SetDead()
{
	tEvent event = {};
	event.eType = EVENT_TYPE::DELETE_OBJECT;
	event.wPARAM = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(event);
}


