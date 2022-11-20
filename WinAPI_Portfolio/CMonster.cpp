#include "pch.h"
#include "CMonster.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"

CMonster::CMonster()
{
}

CMonster::CMonster(wstring _pstring)
{
}

CMonster::~CMonster()
{
}


void CMonster::ObjectTick()
{
	CObject::ObjectTick();
}

void CMonster::ObjectRender(HDC _dc, wstring _pstring)
{
	CObject::ObjectRender(_dc, _pstring);
}

void CMonster::CollisionBegin(CCollider* _pOther)
{
}

void CMonster::Colliding(CCollider* _pOther)
{
}

void CMonster::CollisionEnd(CCollider* _pOther)
{
}

