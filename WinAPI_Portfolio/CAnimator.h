#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_pCurAnim;
    bool                        m_bRepeat;

public:
    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void Play(const wstring& _strName, bool _bRepeat);

    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec _vLeftTop, Vec _vSize, Vec _vOffset, int _iMaxFrameCount, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);

    CAnimation* GetCurAnimation() { return m_pCurAnim; }

public:
    CLONE(CAnimator);

public:
    CAnimator(CObject* _pOwner);
    CAnimator(const CAnimator& _other);
    virtual ~CAnimator();
};

