#include "pch.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(10000.f)
	, m_fGravityVLimit(10000.f)
	, m_bOnGround(false)
	, m_bGravityUse(false)
{
}

CRigidBody::CRigidBody(const CRigidBody& _other)
	: CComponent(_other)
	, m_vForce(_other.m_vForce)
	, m_vVelocity(_other.m_vVelocity)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_fGravityVLimit(_other.m_fGravityVLimit)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_bGravityUse(_other.m_bGravityUse)
	, m_bOnGround(false)
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::ComponentTick()
{
}

void CRigidBody::Final_Tick()
{
	Vec cAccel = m_vForce / m_fMass;

	m_vVelocity += cAccel * DT;

	if (m_bGravityUse && m_bOnGround || !m_bGravityUse)
	{
		Vec vFriction = -m_vVelocity;
		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}
		
		if (m_vVelocity.CountVectorScale() <= vFriction.CountVectorScale())
		{
			m_vVelocity = Vec(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	if (m_bGravityUse && !m_bOnGround)
	{
		Vec vGravityAccel = Vec(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT *3;
	}

	// Velocity Limit option
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
		}
		if (m_fGravityVLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
		}
	}

	else
	{
		if (m_fVelocityLimit < m_vVelocity.CountVectorScale())
		{
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}

	// Object position
	Vec vPos = GetOwner()->GetPos();

	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	// reset the Force at last moment in one frame
	m_vForce = Vec(0.f, 0.f);
}

void CRigidBody::ComponentRender(HDC _dc)
{
}

void CRigidBody::SetBoolOnGround(bool _bGround)
{
	m_bOnGround = _bGround;

	if (m_bOnGround)
	{
		m_vVelocity.y = 0.f;
	}
}