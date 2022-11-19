#include "pch.h"
#include "CGhostWoman.h"
#include "CResourceMgr.h"
#include "CAnimator.h"
#include "CAnimator.h"

CGhostWoman::CGhostWoman(wstring _pstring)
: m_pGhostWomanIdleRight(nullptr)
, m_pGhostWomanIdleLeft(nullptr)
, m_pGhostWomanLeftToRight(nullptr)
, m_pGhostWomanRightToLeft(nullptr)
, m_PGhostWomanAttackRight(nullptr)
, m_PGhostWomanAttackLeft(nullptr)
, m_PGhostWomanHitRight(nullptr)
, m_PGhostWomanHitLeft(nullptr)
{
	m_pGhostWomanIdleRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanIdleRight", L"texture\\Ghost_Woman_Idle_Right.bmp");
	m_pGhostWomanIdleLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanIdleLeft", L"texture\\Ghost_Woman_Idle_Left.bmp");
	m_pGhostWomanLeftToRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanLeftToRight", L"texture\\Ghost_Woman_RightToLeft.bmp");
	m_pGhostWomanRightToLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanRightToLeft", L"texture\\Ghost_Woman_LeftToRight.bmp");
	m_PGhostWomanAttackRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanAttackRight", L"texture\\Ghost_Woman_Attack_Right.bmp");
	m_PGhostWomanAttackLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanAttackLeft", L"texture\\Ghost_Woman_Attack_Left.bmp");
	m_PGhostWomanHitRight = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanHitRight", L"texture\\Ghost_Woman_Hit_Right.bmp");
	m_PGhostWomanHitLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostWomanHitLeft", L"texture\\Ghost_Woman_Hit_Left.bmp");
}

CGhostWoman::~CGhostWoman()
{
}


void CGhostWoman::ObjectTick()
{
	CMonster::ObjectTick();
}

void CGhostWoman::ObjectRender(HDC _dc, wstring _pstring)
{
	CMonster::ObjectRender(_dc, _pstring);
}

