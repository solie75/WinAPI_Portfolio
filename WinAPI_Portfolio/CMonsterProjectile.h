#pragma once
#include "CObject.h"

class CTexture;
class CMonsterProjectile :
    public CObject
{
public:
    bool OnCrush;
    float m_fSpeed;
    Vec m_vTargetPos;

    CTexture* m_pProjectile1;
    CTexture* m_pProjectile2;
    CTexture* m_pProjectile3;
    CTexture* m_pProjectile4;
    CTexture* m_pProjectile5;
    CTexture* m_pProjectile6;
    CTexture* m_pProjectile7;
    CTexture* m_pProjectile8;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    /*bool IsTriggerOn() {
        return Trigger;
    }*/

public:
    CLONE(CMonsterProjectile);

public:
    CMonsterProjectile();
    CMonsterProjectile(wstring _pstring);
    ~CMonsterProjectile();
};

