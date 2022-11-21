#include "pch.h"
#include "CLineCollider.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CEngine.h"
#include "CPlayer.h"

#include "CCameraMgr.h"

CLineCollider::CLineCollider(CObject* _pOwner, Vec _pStart, Vec _End)
	: CCollider(_pOwner)
	, StartPoint(_pStart)
	, EndPoint(_End)
{
	SetOverlapCount(0);
	SetColliderType((UINT)COLLIDER_TYPE::LINE);
}

CLineCollider::~CLineCollider()
{
}


void CLineCollider::ComponentTick()
{
	//CCollider::ComponentTick();
}

void CLineCollider::ComponentRender(HDC _dc)
{
	HPEN hPen = nullptr;

	if (0 < GetOverlapCount())
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	}
	else
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	}

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	//Vec vRenderPos = CCameraMgr::GetInst()->GetRenderPos(GetColliderFinalPos());
	
	// drawing the Line
	Vec vStartPoint = CCameraMgr::GetInst()->GetRenderPos(StartPoint);
	Vec vEndPoint = CCameraMgr::GetInst()->GetRenderPos(EndPoint);

	MoveToEx(_dc, (int)(vStartPoint.x), (int)(vStartPoint.y), NULL);
	LineTo(_dc, (int)(vEndPoint.x), (int)(vEndPoint.y));

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CLineCollider::BeginOverlap(CCollider* _other)
{
	GetOwner()->BeginOverlap(_other);
	if (_other->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER || _other->GetColliderType() == (UINT)COLLIDER_TYPE::GHOSTWOMAN)
	{
		if (nullptr == _other->GetOwner())
		{
			return;
		}
		_other->GetOwner()->GetRigidBody()->SetBoolOnGround(true);
	}

	CCollider::BeginOverlap(_other);
}

void CLineCollider::EndOverlap(CCollider* _other)
{
	GetOwner()->EndOverlap(_other);
	if (_other->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER || _other->GetColliderType() == (UINT)COLLIDER_TYPE::GHOSTWOMAN)
	{
		if (nullptr == _other->GetOwner())
		{
			return;
		}
		_other->GetOwner()->GetRigidBody()->SetBoolOnGround(false);
	}

	CCollider::EndOverlap(_other);
}

void CLineCollider::OnOverlap(CCollider* _other)
{
	GetOwner()->OnOverlap(_other);

	CCollider::OnOverlap(_other);
}


