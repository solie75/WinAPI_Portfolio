#pragma once
#include "CMonster.h"

class CTexture;

class CGhostBook :
    public CMonster
{
public:
    CTexture* m_pGhostBookIdleRight;
    CTexture* m_pGhostBookIdleLeft;
    CTexture* m_pGhostBookRightToLeft;
    CTexture* m_pGhostBookLeftToRight;
    CTexture* m_pGhostBookAttackRight;
    CTexture* m_pGhostBookAttackLeft;
    CTexture* m_pGhostBookHitRight;
    CTexture* m_pGhostBookHitLeft;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void CollisionBegin(CCollider* _pOther) override;
    virtual void Colliding(CCollider* _pOther) override;
    virtual void CollisionEnd(CCollider* _pOther) override;

public:
    /*CGhostBook();*/
    CGhostBook(wstring _pstring);
    ~CGhostBook();
};

