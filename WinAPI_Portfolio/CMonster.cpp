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

void CMonster::BeginOverlap(CCollider* _pOther)
{
}

void CMonster::OnOverlap(CCollider* _pOther)
{
}

void CMonster::EndOverlap(CCollider* _pOther)
{
}

