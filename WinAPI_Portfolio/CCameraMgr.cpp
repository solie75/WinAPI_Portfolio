#include "pch.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResourceMgr.h"

#include "CEngine.h"

#include "CTexture.h"

CCameraMgr::CCameraMgr()
	: m_fRatio(0.f)
	, m_pBlindTex(nullptr)
	, m_bCameraWorkRow(true)
	, m_bCameraWorkCol(true)
{
	POINT ptResolution = CEngine::GetInst()->GetResolution();

	//m_pBlindTex = CResourceMgr::GetInst()->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);
}

CCameraMgr::~CCameraMgr()
{}

void CCameraMgr::CameraMgrTick()
{
	if (IsPressed(KEY::W))
		m_vLook.y -= 500.f * DT;
	if (IsPressed(KEY::S))
		m_vLook.y += 500.f * DT;
	if (IsPressed(KEY::A))
		m_vLook.x -= 500.f * DT;
	if (IsPressed(KEY::D))
		m_vLook.x += 500.f * DT;

	Vec vResolution = CEngine::GetInst()->GetResolution();

	m_vDiff = m_vLook - (vResolution/ 2.f);

	//if (m_CamEffectList.empty())
	//{
	//	return;
	//}


	////CameraEffect
	//tCamEffect& effect = m_CamEffectList.front();

	//effect.m_fAccTime += DT;

	//if (effect.m_fMaxTime <= effect.m_fAccTime)
	//{
	//	m_CamEffectList.pop_front();
	//	return;
	//} // 카메라 이펙트의 맨 앞 요소가 정해진 시간을 초과하면 삭제된다.

	//m_fRatio = (effect.m_fAccTime / effect.m_fMaxTime) / 2.5f; // m_fRatio는 점차 커진다(0에서 1에 가까워진다.)
	//if (CAMERA_EFFECT::FADE_IN == effect.m_eCurEffect)
	//{
	//	m_fRatio = 0.4f - m_fRatio; // m_fRatio 는 점차 작아진다.
	//}
}

void CCameraMgr::CameraMgrRender(HDC _dc)
{
	// Animation of switching the scene
	//BLENDFUNCTION tBlend = {};

	//tBlend.AlphaFormat = 0;
	//tBlend.BlendFlags = 0;
	//tBlend.BlendOp = AC_SRC_OVER;
	//tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	//if (m_fRatio < 0.001f)
	//	return;

	//AlphaBlend(_dc
	//	, 0, 0
	//	, m_pBlindTex->Width()
	//	, m_pBlindTex->Height()
	//	, m_pBlindTex->GetDC()
	//	, 0, 0
	//	, m_pBlindTex->Width()
	//	, m_pBlindTex->Height()
	//	, tBlend);
}

//void CCameraMgr::FadeOut(float _fTerm)
//{
//	tCamEffect effect = {};
//	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
//	effect.m_fAccTime = 0.f;
//	effect.m_fMaxTime = _fTerm;
//
//	m_CamEffectList.push_back(effect);
//}
//
//void CCameraMgr::FadeIn(float _fTerm)
//{
//	tCamEffect effect = {};
//	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
//	effect.m_fAccTime = 0.f;
//	effect.m_fMaxTime = _fTerm;
//
//	m_CamEffectList.push_back(effect);
//}
