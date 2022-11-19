#include "pch.h"
#include "CGhostBook.h"
#include "CAnimator.h"
#include "CResourceMgr.h"
#include "CAnimation.h"

CGhostBook::CGhostBook(wstring _pstring)
	: m_pGhostBookIdleRight(nullptr)
	, m_pGhostBookIdleLeft(nullptr)
	, m_pGhostBookLeftToRight(nullptr)
	, m_pGhostBookRightToLeft(nullptr)
	, m_pGhostBookAttackRight(nullptr)
	, m_pGhostBookAttackLeft(nullptr)
	, m_pGhostBookHitRight(nullptr)
	, m_pGhostBookHitLeft(nullptr)
{
	m_pGhostBookIdleRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookIdleRight", L"Texture\\");
	m_pGhostBookIdleLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookIdleLeft", L"Texture\\");
	m_pGhostBookLeftToRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookLeftToRight", L"Texture\\");
	m_pGhostBookRightToLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookRightToLeft", L"Texture\\");
	m_pGhostBookAttackRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookAttackRight", L"Texture\\");
	m_pGhostBookAttackLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookAttackLeft", L"Texture\\");
	m_pGhostBookHitRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookHitRight", L"Texture\\");
	m_pGhostBookHitLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookHitLeft", L"Texture\\");
}

CGhostBook::~CGhostBook()
{
}

void CGhostBook::ObjectTick()
{
	CMonster::ObjectTick();
}

void CGhostBook::ObjectRender(HDC _dc, wstring _pstring)
{
	CMonster::ObjectRender(_dc, _pstring);
}

