#include "pch.h"
#include "CBlind.h"
#include "CEngine.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"
#include "CTexture.h"
#include "Clevel.h"

CBlind::CBlind()
	: m_pBlindTexture(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_bAccOn(false)
	, m_pTransitionIn_Part1(nullptr)
	, m_pTransitionIn_Part2(nullptr)
	, m_pTransitionIn_Part3(nullptr)
	, m_pTransitionIn_Part4(nullptr)
	, m_pTransitionIn_Part5(nullptr)
	, m_pTransitionOut_Part1(nullptr)
	, m_pTransitionOut_Part2(nullptr)
	, m_pTransitionOut_Part3(nullptr)
	, m_pTransitionOut_Part4(nullptr)
	, m_pTransitionOut_Part5(nullptr)
	//, m_vecTransition{}
	, CurEffect((UINT)Blind_Effect::NONE)
{
}

CBlind::CBlind(wstring _pstring)
	: m_pBlindTexture(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_bAccOn(false)
	, m_pTransitionIn_Part1(nullptr)
	, m_pTransitionIn_Part2(nullptr)
	, m_pTransitionIn_Part3(nullptr)
	, m_pTransitionIn_Part4(nullptr)
	, m_pTransitionIn_Part5(nullptr)
	, m_pTransitionOut_Part1(nullptr)
	, m_pTransitionOut_Part2(nullptr)
	, m_pTransitionOut_Part3(nullptr)
	, m_pTransitionOut_Part4(nullptr)
	, m_pTransitionOut_Part5(nullptr)
	//, m_vecTransition{}
	, CurEffect((UINT)Blind_Effect::NONE)
{
	SetName(_pstring);
	CreateAnimator();
	Vec _Resolution = CEngine::GetInst()->GetResolution();
	m_pBlindTexture = CResourceMgr::GetInst()->CreateTexture(L"BlindTexture", _Resolution.x, _Resolution.y);

	m_pTransitionIn_Part1 = CResourceMgr::GetInst()->LoadTexture(L"TransitionIn_Part1", L"texture\\Transition_Part1.bmp");
	m_pTransitionIn_Part2 = CResourceMgr::GetInst()->LoadTexture(L"TransitionIn_Part2", L"texture\\Transition_Part2.bmp");
	m_pTransitionIn_Part3 = CResourceMgr::GetInst()->LoadTexture(L"TransitionIn_Part3", L"texture\\Transition_Part3.bmp");
	m_pTransitionIn_Part4 = CResourceMgr::GetInst()->LoadTexture(L"TransitionIn_Part4", L"texture\\Transition_Part4.bmp");
	m_pTransitionIn_Part5 = CResourceMgr::GetInst()->LoadTexture(L"TransitionIn_Part5", L"texture\\Transition_Part5.bmp");

	m_pTransitionOut_Part1 = CResourceMgr::GetInst()->LoadTexture(L"TransitionOut_Part1", L"texture\\TransitionOut_Part1.bmp");
	m_pTransitionOut_Part2 = CResourceMgr::GetInst()->LoadTexture(L"TransitionOut_Part2", L"texture\\TransitionOut_Part2.bmp");
	m_pTransitionOut_Part3 = CResourceMgr::GetInst()->LoadTexture(L"TransitionOut_Part3", L"texture\\TransitionOut_Part3.bmp");
	m_pTransitionOut_Part4 = CResourceMgr::GetInst()->LoadTexture(L"TransitionOut_Part4", L"texture\\TransitionOut_Part4.bmp");
	m_pTransitionOut_Part5 = CResourceMgr::GetInst()->LoadTexture(L"TransitionOut_Part5", L"texture\\TransitionOut_Part5.bmp");

	GetAnimator()->CreateAnimation(L"TransitionIn_Part1", m_pTransitionIn_Part1, Vec(0.f, 0.f), Vec(1600.f , 900.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"TransitionIn_Part2", m_pTransitionIn_Part2, Vec(0.f, 0.f), Vec(1600.f , 900.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"TransitionIn_Part3", m_pTransitionIn_Part3, Vec(0.f, 0.f), Vec(1600.f , 900.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"TransitionIn_Part4", m_pTransitionIn_Part4, Vec(0.f, 0.f), Vec(1600.f , 900.f), Vec(0.f, 0.f), 5, 0.04f);
	GetAnimator()->CreateAnimation(L"TransitionIn_Part5", m_pTransitionIn_Part5, Vec(0.f, 0.f), Vec(1600.f , 900.f), Vec(0.f, 0.f), 5, 0.04f);

	GetAnimator()->CreateAnimation(L"TransitionOut_Part1", m_pTransitionOut_Part1, Vec(0.f, 0.f), Vec(1600.f, 900.f), Vec(0.f, 0.f), 5, 0.02f);
	GetAnimator()->CreateAnimation(L"TransitionOut_Part2", m_pTransitionOut_Part2, Vec(0.f, 0.f), Vec(1600.f, 900.f), Vec(0.f, 0.f), 5, 0.02f);
	GetAnimator()->CreateAnimation(L"TransitionOut_Part3", m_pTransitionOut_Part3, Vec(0.f, 0.f), Vec(1600.f, 900.f), Vec(0.f, 0.f), 5, 0.02f);
	GetAnimator()->CreateAnimation(L"TransitionOut_Part4", m_pTransitionOut_Part4, Vec(0.f, 0.f), Vec(1600.f, 900.f), Vec(0.f, 0.f), 5, 0.02f);
	GetAnimator()->CreateAnimation(L"TransitionOut_Part5", m_pTransitionOut_Part5, Vec(0.f, 0.f), Vec(1600.f, 900.f), Vec(0.f, 0.f), 5, 0.02f);
}

CBlind::~CBlind()
{
}


void CBlind::ObjectTick()
{
	if (m_bAccOn == true)
	{
		m_fAccTime += DT;
	}

	if (m_fAccTime > 0.001f && CurEffect != (UINT)Blind_Effect::DONE)
	{
		m_fRatio = (m_fAccTime / m_fMaxTime) / 2.f;
		if (CurEffect == (UINT)Blind_Effect::FADE_IN)
		{
			m_fRatio = 0.4f - m_fRatio;
		}
	}

	if (m_fMaxTime <= m_fAccTime)
	{
		m_bAccOn = false;
		m_fAccTime = 0.f;
		
		if (CurEffect == (UINT)Blind_Effect::FADE_IN)
		{
			CurEffect = (UINT)Blind_Effect::DONE;
			m_bAccOn = true;
		}
	}

	Vec _v = CCameraMgr::GetInst()->GetCameraLook();

	SetPos(_v);

	CObject::ObjectTick();
}

void CBlind::ObjectRender(HDC _dc, wstring _pstring)
{
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	if (m_fRatio < 0.001f)
		return;

	AlphaBlend(_dc
		, 0, 0
		, m_pBlindTexture->Width()
		, m_pBlindTexture->Height()
		, m_pBlindTexture->GetDC()
		, 0, 0
		, m_pBlindTexture->Width()
		, m_pBlindTexture->Height()
		, tBlend);

	CObject::ObjectRender(_dc, _pstring);
}

void CBlind::FadeOut(float _fTerm)
{
	m_bAccOn = true;
	m_fMaxTime = _fTerm;
	CurEffect = (UINT)Blind_Effect::FADE_OUT;
}

void CBlind::FadeIn(float _fTerm)
{
	m_bAccOn = true;
	m_fMaxTime = _fTerm;
	CurEffect = (UINT)Blind_Effect::FADE_IN;
}


