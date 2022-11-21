#include "pch.h"
#include "CWall.h"

#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CAnimator.h"
#include "CCollider.h"

CWall::CWall()
{
}

CWall::CWall(wstring _pstring)
{
	SetName(_pstring);
	CreateSquareCollider();// (UINT)COLLIDER_TYPE::WALL, Vec(40.f, 1000.f), Vec(0.f, 0.f)
	GetColliderVector()[0]->SetColliderType((UINT)COLLIDER_TYPE::WALL);
	
}

CWall::~CWall()
{
}


void CWall::ObjectTick()
{
	GetColliderVector()[0]->SetColliderScale(Vec(GetScale()));
	CObject::ObjectTick();
}

void CWall::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}

void CWall::BeginOverlap(CCollider* _pOther)
{
	//SetDead();
}

void CWall::OnOverlap(CCollider* _pOther)
{
}

void CWall::EndOverlap(CCollider* _pOther)
{

}
