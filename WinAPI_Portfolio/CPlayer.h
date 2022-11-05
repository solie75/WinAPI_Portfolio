#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
public:
    float m_fSpeed;
    CTexture* m_pTexture;
    CTexture* m_pDeathSpawn;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void CollisionBegin(CCollider* _pOther) override;
    virtual void Colliding(CCollider* _pOther) override;
    virtual void CollisionEnd(CCollider* _pOther) override;

public:
    CLONE(CPlayer);

    void SetSpeed(float _f)
    {
        m_fSpeed = _f;
    }

public:
    CPlayer();
    CPlayer(wstring _pstring);
    ~CPlayer();
};

