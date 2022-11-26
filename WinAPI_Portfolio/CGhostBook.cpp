#include "pch.h"
#include "CGhostBook.h"
#include "CAnimator.h"
#include "CResourceMgr.h"
#include "CAnimation.h"
#include "CCollider.h"

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
	SetName(_pstring);
	CreateAnimator();
	CreateSquareCollider();

	m_pGhostBookIdleRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookIdleRight", L"Texture\\Ghost_Book_Idle_Right.bmp");
	m_pGhostBookIdleLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookIdleLeft", L"Texture\\GhostBookIdleLeft");
	m_pGhostBookLeftToRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookLeftToRight", L"Texture\\GhostBookLeftToRight");
	m_pGhostBookRightToLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookRightToLeft", L"Texture\\GhostBookRightToLeft");
	m_pGhostBookAttackRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookAttackRight", L"Texture\\GhostBookAttackRight");
	m_pGhostBookAttackLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookAttackLeft", L"Texture\\GhostBookAttackLeft");
	m_pGhostBookHitRight = CResourceMgr::GetInst()->LoadTexture(L"GhostBookHitRight", L"Texture\\GhostBookHitRight");
	m_pGhostBookHitLeft = CResourceMgr::GetInst()->LoadTexture(L"GhostBookHitLeft", L"Texture\\GhostBookHitLeft");

	GetAnimator()->CreateAnimation(L"GhostBookIdleRight", m_pGhostBookIdleRight, Vec(0.f, 0.f), Vec(100.f, 80.f), Vec(0.f, 0.f), 24, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookIdleLeft", m_pGhostBookIdleLeft, Vec(0.f, 0.f), Vec(100.f, 80.f), Vec(0.f, 0.f), 24, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookLeftToRight", m_pGhostBookLeftToRight, Vec(0.f, 0.f), Vec(100.f, 70.f), Vec(0.f, 0.f), 9, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookRightToLeft", m_pGhostBookRightToLeft, Vec(0.f, 0.f), Vec(100.f, 70.f), Vec(0.f, 0.f), 9, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookAttackRight", m_pGhostBookAttackRight, Vec(0.f, 0.f), Vec(230.f, 370.f), Vec(0.f, 0.f), 54, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookAttackLeft", m_pGhostBookAttackLeft, Vec(0.f, 0.f), Vec(230.f, 370.f), Vec(0.f, 0.f), 54, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookHitRight", m_pGhostBookHitRight, Vec(0.f, 0.f), Vec(100.f, 90.f), Vec(0.f, 0.f), 18, 0.04f);
	GetAnimator()->CreateAnimation(L"GhostBookHitLeft", m_pGhostBookHitLeft, Vec(0.f, 0.f), Vec(100.f, 90.f), Vec(0.f, 0.f), 18, 0.04f);

	GetAnimator()->Play(L"GhostBookIdleRight", true);
	Vec _CurAnimSize = GetAnimator()->GetCurAnimation()->GetAnimCurSize();
	GetColliderVector()[0]->SetColliderScale(_CurAnimSize);
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

void CGhostBook::BeginOverlap(CCollider* _pOther)
{
}

void CGhostBook::OnOverlap(CCollider* _pOther)
{
}

void CGhostBook::EndOverlap(CCollider* _pOther)
{
}

