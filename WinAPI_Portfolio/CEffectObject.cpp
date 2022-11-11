#include "pch.h"
#include "CEffectObject.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffectObject::CEffectObject()
	: m_pTexture(nullptr)
{
}

CEffectObject::CEffectObject(wstring _pstring)
	: m_pTexture(nullptr)
{
	SetName(_pstring);
	CreateAnimator();

	CTexture* _textrue = CResourceMgr::GetInst()->LoadTexture(L"DeathLandingDust", L"texture\\DeathLandingDust.bmp");
	GetAnimator()->CreateAnimation(L"DeathLandingDust", _textrue, Vec(0.f, 0.f), Vec(280.f, 110.f), 12, 0.025f);
	this->GetAnimator()->Play(L"DeathLandingDust", false);
}

CEffectObject::~CEffectObject()
{
}


void CEffectObject::ObjectTick()
{
	CObject::ObjectTick();
}

void CEffectObject::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

	/*m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);

	Vec vLeftTop = Vec(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	TransparentBlt(_dc
		, (int)vLeftTop.x
		, (int)vLeftTop.y
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()
		, RGB(255, 0, 255)
	);*/

	if (this->GetAnimator()->GetCurAnimation()->GetCurAnimName() == L"DeathLandingDust" && this->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		SetDead();
	}

	CObject::ObjectRender(_dc, _pstring);
}

