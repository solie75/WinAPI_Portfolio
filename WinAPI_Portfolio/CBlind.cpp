#include "pch.h"
#include "CBlind.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CResourceMgr.h"
#include "CTexture.h"

CBlind::CBlind()
	: m_pBlindTexture(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_bAccOn(false)
	, CurEffect((UINT)Blind_Effect::NONE)
{
}

CBlind::CBlind(wstring _pstring)
	: m_pBlindTexture(nullptr)
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_bAccOn(false)
	, CurEffect((UINT)Blind_Effect::NONE)
{
	SetName(_pstring);
	Vec _Resolution = CEngine::GetInst()->GetResolution();
	m_pBlindTexture = CResourceMgr::GetInst()->CreateTexture(L"BlindTexture", _Resolution.x, _Resolution.y);
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


