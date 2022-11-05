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
	//, m_pCollider(nullptr)
	, m_mapCollider{}
	, m_pRigidBody(nullptr)
{ 
}

CObject::CObject(const CObject& _other)
	: CEntity(_other)
	, m_vPos()
	, m_vScale{}
	, m_bDead(false)
	, m_pAnimator(nullptr)
	//, m_pCollider(nullptr)
	, m_mapCollider{}
	, m_pRigidBody(nullptr)
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
	//DEL(m_pCollider);
	DEL(m_pRigidBody);
	
	map<int, CCollider*>::iterator iter = m_mapCollider.begin();
	for (; iter != m_mapCollider.end(); ++iter)
	{
		delete iter->second;
	}
}

void CObject::ObjectTick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentTick();
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentTick();
	}
	//if (nullptr != m_pCollider)
	//{
	//	m_pCollider->ComponentTick();
	//}
	if (true != m_mapCollider.empty())
	{
		map<int, CCollider*>::iterator iter = m_mapCollider.begin();
		for (; iter != m_mapCollider.end(); ++iter)
		{
			iter->second->ComponentTick();
		}
	}
}

void CObject::Final_Tick()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Final_Tick();
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->Final_Tick();
	}
	//if (nullptr != m_pCollider)
	//{
	//	m_pCollider->Final_Tick();
	//}
	if (true != m_mapCollider.empty())
	{
		map<int, CCollider*>::iterator iter = m_mapCollider.begin();
		for (; iter != m_mapCollider.end(); ++iter)
		{
			iter->second->Final_Tick();
		}
	}
}

void CObject::ObjectRender(HDC _dc, wstring _pstring)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentRender(_dc);
	}
	//if (nullptr != m_pCollider)
	//{
	//	m_pCollider->ComponentRender(_dc);
	//}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentRender(_dc);
	}
	if (true != m_mapCollider.empty())
	{
		map<int, CCollider*>::iterator iter = m_mapCollider.begin();
		for (; iter != m_mapCollider.end(); ++iter)
		{
			iter->second->ComponentRender(_dc);
		}
	}
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObject::CreateSquareCollider(int _colliderIdx)
{
	//m_pCollider = new CSquareCollider(this);

	m_mapCollider.insert(make_pair( (_colliderIdx), (CCollider*)(new CSquareCollider(this))));
}

void CObject::CreateLineCollider(Vec _pStart, Vec _pEnd, int _colliderIdx)
{
	//m_pCollider = new CLineCollider(this, _pStart, _pEnd);
	m_mapCollider.insert(make_pair(_colliderIdx, (CCollider*)(new CLineCollider(this, _pStart, _pEnd))));
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


