#include "pch.h"
#include "CObject.h"
#include "CEventMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CLineCollider.h"
#include "CSquareCollider.h"
#include "CRigidBody.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
	, m_pAnimator(nullptr)
	, m_vecCollider{}
	, m_pRigidBody(nullptr)
{ 
}

CObject::CObject(const CObject& _other)
	: CEntity(_other)
	, m_vPos()
	, m_vScale{}
	, m_bDead(false)
	, m_pAnimator(nullptr)
	, m_vecCollider{}
	, m_pRigidBody(nullptr)
{
	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = _other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}

	if (0 != _other.m_vecCollider.size())
	{
		for (size_t i = 0; i < m_vecCollider.size(); ++i)
		{
			m_vecCollider[i] = _other.m_vecCollider[i]->Clone();
			m_vecCollider[i]->SetOwner(this);
		}
	}
}

CObject::~CObject()
{
	DEL(m_pAnimator);
	DEL(m_pRigidBody);
	
	for (size_t i = 0; i < m_vecCollider.size(); ++i)
	{
		DEL(m_vecCollider[i]);
	}
}

void CObject::ObjectTick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentTick();
	}
	if (0 != m_vecCollider.size())
	{
		for (size_t i = 0; i < m_vecCollider.size(); ++i)
		{
			m_vecCollider[i]->ComponentTick();
		}
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentTick();
	}
}

void CObject::Final_Tick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Final_Tick();
	}
	if (0 != m_vecCollider.size())
	{
		for (size_t i = 0; i < m_vecCollider.size(); ++i)
		{
			m_vecCollider[i]->Final_Tick();
		}
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->Final_Tick();
	}
}

void CObject::ObjectRender(HDC _dc, wstring _pstring)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentRender(_dc);
	}
	if (0 != m_vecCollider.size())
	{
		for (size_t i = 0; i < m_vecCollider.size(); ++i)
		{
			m_vecCollider[i]->ComponentRender(_dc);
		}
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentRender(_dc);
	}
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObject::CreateSquareCollider()
{
	//m_pCollider = new CSquareCollider(this);

	//m_mapCollider.insert(make_pair( (_colliderIdx), (CCollider*)(new CSquareCollider(this))));
	m_vecCollider.push_back((CCollider*)(new CSquareCollider(this)));
}

void CObject::CreateLineCollider(Vec _pStart, Vec _pEnd)
{
	//m_pCollider = new CLineCollider(this, _pStart, _pEnd);
	//m_mapCollider.insert(make_pair(_colliderIdx, (CCollider*)(new CLineCollider(this, _pStart, _pEnd))));
	m_vecCollider.push_back((CCollider*)(new CLineCollider(this, _pStart, _pEnd)));
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody(this);
}

void CObject::SetDead()
{
	tEvent event = {};
	event.eType = EVENT_TYPE::DELETE_OBJECT;
	event.wPARAM = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(event);
}


