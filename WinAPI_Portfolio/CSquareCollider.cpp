#include "pch.h"
#include "CSquareCollider.h"
#include "CObject.h"
#include "CEngine.h"
#include "CCameraMgr.h"

CSquareCollider::CSquareCollider(CObject* _pOwner)
	:	CCollider(_pOwner)
{
	SetOverlapCount(0);
	SetColliderType((UINT)COLLIDER_TYPE::UNKNOWN);
}

CSquareCollider::~CSquareCollider()
{
}

void CSquareCollider::ComponentTick()
{


	CCollider::ComponentTick();
}

void CSquareCollider::ComponentRender(HDC _dc)
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

	HBRUSH hNULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNULLBrush);

	Vec vRenderPos = CCameraMgr::GetInst()->GetRenderPos(GetColliderFinalPos());

	Rectangle(_dc
		, (int)(vRenderPos.x - GetColliderScale().x / 2.f)
		, (int)(vRenderPos.y - GetColliderScale().y / 2.f)
		, (int)(vRenderPos.x + GetColliderScale().x / 2.f)
		, (int)(vRenderPos.y + GetColliderScale().y / 2.f));

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CSquareCollider::BeginOverlap(CCollider* _other)
{
	GetOwner()->BeginOverlap(_other);

	CCollider::BeginOverlap(_other);
}

void CSquareCollider::EndOverlap(CCollider* _other)
{
	GetOwner()->EndOverlap(_other);

	CCollider::EndOverlap(_other);
}

void CSquareCollider::OnOverlap(CCollider* _other)
{
	GetOwner()->OnOverlap(_other);

	CCollider::OnOverlap(_other);
}

