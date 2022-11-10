#pragma once
#include "CObject.h"

enum class DEATH_SIGHT
{
    RIGHT,
    LEFT,
    END = 2
};

class CTexture;

class CPlayer :
    public CObject
{
private:
    bool m_bKeyWorking;


public:
    float m_fSpeed;
    CTexture* m_pTexture;
    CTexture* m_pDeathSpawn;

    CTexture* m_pDeathIdleRight;
    CTexture* m_pDeathIdleLeft;

    CTexture* m_pDeathIdleLeftToRight;
    CTexture* m_pDeathIdleRightToLeft;

    CTexture* m_pDeathIdleToRunRight;
    CTexture* m_pDeathIdleToRunLeft;

    CTexture* m_pDeathRunRightToIdle;
    CTexture* m_pDeathRunLeftToIdle;

    CTexture* m_pDeathRunRight;
    CTexture* m_pDeathRunLeft;

    CTexture* m_pDeath;

    UINT DeathSight;
    bool m_bToIdle;
    bool m_bOnIdle;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void CollisionBegin(CCollider* _pOther) override;
    virtual void Colliding(CCollider* _pOther) override;
    virtual void CollisionEnd(CCollider* _pOther) override;

public:
    void SetKeyWorking(bool _b) { m_bKeyWorking = _b; }
    bool GetKeyWorking() { return m_bKeyWorking; }

    //void SetBoolToIdle(bool _b) { m_bToIdle = _b; }
    //bool GetBoolToIdle() { return m_bIdle; }

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

