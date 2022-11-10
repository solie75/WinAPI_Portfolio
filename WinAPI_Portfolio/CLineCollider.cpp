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
	AddOverlapCount();
	GetOwner()->CollisionBegin(_other);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_other->GetOwner());
	if(nullptr == pPlayer)
	{
		return;
	}
	// 바닥 충돌체와 맞닿은 플레이어의 추락 정지
	pPlayer->GetRigidBody()->SetBoolOnGround(true);
}

void CLineCollider::EndOverlap(CCollider* _other)
{
	SubtractOvelapCount();
	GetOwner()->CollisionEnd(_other);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_other->GetOwner());
	if (nullptr == pPlayer)
	{
		return;
	}
	pPlayer->GetRigidBody()->SetBoolOnGround(false);
}

void CLineCollider::OnOverlap(CCollider* _other)
{
	GetOwner()->Colliding(_other);
}


