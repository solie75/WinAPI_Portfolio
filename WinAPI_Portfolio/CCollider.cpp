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
	// decide finalPosition of Collider
	m_vColliderFinalPos = GetOwner()->GetPos() + m_vColliderOffsetPos;

	if (this->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		m_vColliderFinalPos = m_vColliderOffsetPos;
	}

	// if overlapcount
	assert(!(m_iOverlapCount < 0));
}

void CCollider::ComponentRender(HDC _dc)
{
}

void CCollider::BeginOverlap(CCollider* _other)
{
	_other->GetOwner()->CollisionBegin(this);
	this->GetOwner()->CollisionBegin(_other);
}

void CCollider::EndOverlap(CCollider* _other)
{
	_other->GetOwner()->Colliding(this);
	this->GetOwner()->Colliding(_other);
}

void CCollider::OnOverlap(CCollider* _other)
{
	_other->GetOwner()->CollisionEnd(this);
	this->GetOwner()->CollisionEnd(_other);
}
