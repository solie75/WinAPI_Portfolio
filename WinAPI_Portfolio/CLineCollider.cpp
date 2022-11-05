#include "pch.h"
#include "CLineCollider.h"
#include "CObject.h"
#include "CEngine.h"

#include "CCameraMgr.h"

CLineCollider::CLineCollider(CObject* _pOwner, Vec _pStart, Vec _End)
	: CCollider(_pOwner)
	, StartPoint(_pStart)
	, EndPoint(_End)
{
	SetOverlapCount(0);
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
	
	// 그냥 정수로 Rectangle이나 선을 그리는 함수는 작동하는데 아래것만 작동 안함 시발
	// drawing the Line
	MoveToEx(_dc, (int)(StartPoint.x), (int)(StartPoint.y), NULL);
	LineTo(_dc, (int)(EndPoint.x), (int)(EndPoint.y));

	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CLineCollider::BeginOverlap(CCollider* _other)
{
	AddOverlapCount();
	GetOwner()->CollisionBegin(_other);
}

void CLineCollider::EndOverlap(CCollider* _other)
{
	SubtractOvelapCount();
	GetOwner()->CollisionBegin(_other);
}

void CLineCollider::OnOverlap(CCollider* _other)
{
	GetOwner()->Colliding(_other);
}


