#include "pch.h"
#include "CObject.h"
#include "CEventMgr.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
{ 
}

CObject::CObject(const CObject& _other)
	: CEntity(_other)
	, m_vPos()
	, m_vScale{}
	, m_bDead(false)
{
}

CObject::~CObject()
{
}

void CObject::ObjectTick()
{
}

void CObject::Final_Tick()
{
}

void CObject::ObjectRender(HDC _hdc)
{
}

void CObject::SetDead()
{
	tEvent event = {};
	event.eType = EVENT_TYPE::DELETE_OBJECT;
	event.wPARAM = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(event);
}


