#pragma once
#include "CObject.h"

class CTexture;

class CTrigger :
    public CObject
{
public:
    CTexture* m_pTexture;
    bool Trigger;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void CollisionBegin(CCollider* _pOther) override;
    virtual void Colliding(CCollider* _pOther) override;
    virtual void CollisionEnd(CCollider* _pOther) override;

    bool IsTriggerOn() {
        return Trigger;
    }

public:
    CLONE(CTrigger);

public:
    CTrigger();
    CTrigger(wstring _pstring);
    ~CTrigger();
};

