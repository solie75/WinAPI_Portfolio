#include "pch.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
//#include "CResourceMgr.h"

#include "CEngine.h"

//#include "CTexture.h"

CCameraMgr::CCameraMgr()
	: m_fRatio(0.f)
	, m_pBlindTex(nullptr)
{
	POINT ptResolution = CEngine::GetInst()->GetResolution();

	/*m_pBlindTex = CResourceMgr::GetInst()->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);*/ // trans scene animation
}

CCameraMgr::~CCameraMgr()
{}

void CCameraMgr::CameraMgrTick()
{
	// CameraMove
	//if (IsPressed(KEY::W))
	//	m_vLook.y -= 10.f * DT;
	//if (IsPressed(KEY::S))
	//	m_vLook.y += 10.f * DT;
	//if (IsPressed(KEY::A))
	//	m_vLook.x -= 10.f * DT;
	//if (IsPressed(KEY::D))
	//	m_vLook.x += 10.f * DT;

	Vec vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	m_vDiff = m_vLook - vResolution;

	if (m_CamEffectList.empty())
	{
		return;
	}

	tCamEffect& effect = m_CamEffectList.front();

	effect.m_fAccTime += DT;

	if (effect.m_fMaxTime <= effect.m_fAccTime)
	{
		m_CamEffectList.pop_front();
		return;
	} // ī�޶� ����Ʈ�� �� �� ��Ұ� ������ �ð��� �ʰ��ϸ� �����ȴ�.

	m_fRatio = effect.m_fAccTime / effect.m_fMaxTime; // m_fRatio�� ���� Ŀ����(0���� 1�� ���������.)
	if (CAMERA_EFFECT::FADE_IN == effect.m_eCurEffect)
	{
		m_fRatio = 1.f - m_fRatio; // m_fRatio �� ���� �۾�����.
	}
}

void CCameraMgr::CameraMgrRender(HDC _dc)
{
	// Animation of switching the scene
}

void CCameraMgr::FadeOut(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}

void CCameraMgr::FadeIn(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}
