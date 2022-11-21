#pragma once
#include "CMonster.h"

class CTexture;

enum class GhostWoman_State
{
    IDLE,
    UTURN,
    ATTACK_LONG,
    ATTACK_SHORT,
    HIT,
    NONE
};

class CGhostWoman :
    public CMonster
{
public:
    CTexture* m_pGhostWomanIdleRight;
    CTexture* m_pGhostWomanIdleLeft;
    CTexture* m_pGhostWomanRightToLeft;
    CTexture* m_pGhostWomanLeftToRight;
    CTexture* m_pGhostWomanAttackRight;
    CTexture* m_pGhostWomanAttackLeft;
    CTexture* m_pGhostWomanHitRight;
    CTexture* m_pGhostWomanHitLeft;

    UINT m_GhostWoman_State;
    bool m_bCollidingWall;
    float TargetDegree;
    Vec m_vTarget;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    CGhostWoman(wstring _pstring);
    ~CGhostWoman();
};

