#include "pch.h"
#include "CEngine.h"
#include "CCollider.h"

#include "CObject.h"

#include "CCameraMgr.h"

CCollider::CCollider(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_iOverlapCount(0)
	//, m_vColliderScale(Vec(0.f,0.f))
	, m_ColliderType(0)
	//, m_vColliderOffsetPos(Vec(0.f, 0.f))
{
	//m_vColliderFinalPos = GetOwner()->GetPos() + m_vColliderOffsetPos;
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vColliderOffsetPos(_other.m_vColliderOffsetPos)
	, m_vColliderFinalPos(_other.m_vColliderFinalPos)
	, m_vColliderScale(_other.m_vColliderScale)
	, m_iOverlapCount(0)
	, m_ColliderType(0)
{
	//m_vColliderFinalPos = GetOwner()->GetPos() + m_vColliderOffsetPos;
}

CCollider::~CCollider()
{
}

void CCollider::ComponentTick()
{
	//assert(!(m_iOverlapCount < 0));
}

void CCollider::Final_Tick()
{
	m_vColliderFinalPos = GetOwner()->GetPos() + m_vColliderOffsetPos;
}

void CCollider::ComponentRender(HDC _dc)
{
}

void CCollider::BeginOverlap(CCollider* _other)
{
 	AddOverlapCount();
}

void CCollider::EndOverlap(CCollider* _other)
{
	SubtractOvelapCount();
}

void CCollider::OnOverlap(CCollider* _other)
{
}
