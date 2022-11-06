#include "pch.h"
#include "CEngine.h"
#include "CCollider.h"

#include "CObject.h"

#include "CCameraMgr.h"

CCollider::CCollider(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_iOverlapCount(0)
	, m_vColliderScale(Vec(0.f,0.f))
	, m_ColliderType(0)
{
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vColliderOffsetPos(_other.m_vColliderOffsetPos)
	, m_vColliderFinalPos(_other.m_vColliderFinalPos)
	, m_vColliderScale(_other.m_vColliderScale)
	, m_iOverlapCount(0)
	, m_ColliderType(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::ComponentTick()
{
	// decide finalPosition of Collider
	m_vColliderFinalPos = GetOwner()->GetPos() + m_vColliderOffsetPos;

	// if overlapcount
	assert(!(m_iOverlapCount < 0));
}

void CCollider::ComponentRender(HDC _dc)
{
}