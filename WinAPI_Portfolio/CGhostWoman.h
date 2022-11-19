#pragma once
#include "CMonster.h"

class CTexture;

class CGhostWoman :
    public CMonster
{
public:
    CTexture* m_pGhostWomanIdleRight;
    CTexture* m_pGhostWomanIdleLeft;
    CTexture* m_pGhostWomanRightToLeft;
    CTexture* m_pGhostWomanLeftToRight;
    CTexture* m_PGhostWomanAttackRight;
    CTexture* m_PGhostWomanAttackLeft;
    CTexture* m_PGhostWomanHitRight;
    CTexture* m_PGhostWomanHitLeft;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CGhostWoman(wstring _pstring);
    ~CGhostWoman();
};

