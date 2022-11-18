#pragma once
#include "CObject.h"

class CTexture;

enum class Blind_Effect
{
    FADE_IN,
    FADE_OUT,
    DONE,
    TRANSITION_IN,
    //TRANSITION,
    TRANSITION_OUT,
    NONE,
};

class CBlind :
    public CObject
{
public:
    CTexture* m_pBlindTexture;
    CTexture* m_pTransitionIn_Part1;
    CTexture* m_pTransitionIn_Part2;
    CTexture* m_pTransitionIn_Part3;
    CTexture* m_pTransitionIn_Part4;
    CTexture* m_pTransitionIn_Part5;
    CTexture* m_pTransitionOut_Part1;
    CTexture* m_pTransitionOut_Part2;
    CTexture* m_pTransitionOut_Part3;
    CTexture* m_pTransitionOut_Part4;
    CTexture* m_pTransitionOut_Part5;

    float           m_fRatio;
    float			m_fAccTime;
    float			m_fMaxTime;
    bool            m_bAccOn;
    UINT            CurEffect;
    //vector<CTexture*> m_vecTransition;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    //virtual void CollisionBegin(CCollider* _pOther) override;
    //virtual void Colliding(CCollider* _pOther) override;
    //virtual void CollisionEnd(CCollider* _pOther) override;

    void FadeOut(float _fTerm);
    void FadeIn(float _fTerm);


public:
    CLONE(CBlind);

public:
    CBlind();
    CBlind(wstring _pstring);
    ~CBlind();
};

