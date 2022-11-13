#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_mapAnim{}
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _other)
	: CComponent(_other)
	, m_mapAnim{}
	, m_pCurAnim(_other.m_pCurAnim)
	, m_bRepeat(_other.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _other.m_mapAnim.begin();
	for (; iter != _other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->Reset();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	if (nullptr != m_pCurAnim)
	{
		Play(_other.m_pCurAnim->GetName(), m_bRepeat);
	}
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		delete iter->second;
	}
}


void CAnimator::ComponentTick()
{
	if (nullptr == m_pCurAnim)
	{
		return;
	}

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}

	m_pCurAnim->AnimationTick();
}

void CAnimator::ComponentRender(HDC _dc)
{
	if (nullptr == m_pCurAnim)
	{
		return;
	}

	m_pCurAnim->AnimationRender(_dc);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset(); // pur animation init
	m_bRepeat = _bRepeat;
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec _vLeftTop, Vec _vSize, Vec _vOffset, int _iMaxFrameCount, float _fDuration)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	pAnim = new CAnimation(this);
	pAnim->AnimationInit(_strName, _pAtlas, _vLeftTop, _vSize, _vOffset,_iMaxFrameCount, _fDuration);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	this;
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

CAnimation* CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation(this);

	pAnim->Load(_strRelativePath);

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));

	return nullptr;
}

