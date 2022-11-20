#pragma once
#include "CObject.h"
#include "CEffectObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    bool m_bKeyWorking;

public:
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

    CTexture* m_pDeathRunRightToRunLeft;
    CTexture* m_pDeathRunLeftToRunRight;

    CTexture* m_pDeathDashRight;
    CTexture* m_pDeathDashLeft;

    CTexture* m_pDeathJumpRight;
    CTexture* m_pDeathJumpLeft;
    CTexture* m_pDeathLandingRight;
    CTexture* m_pDeathLandingLeft;
    CTexture* m_pDeathFallingRight;
    CTexture* m_pDeathFallingLeft;

    CTexture* m_pDeathElevatorInRight;
    CTexture* m_pDeathElevatorInLeft;

    CTexture* m_pDeathElevatorIdleRight;
    CTexture* m_pDeathElevatorIdleLeft;

    CTexture* m_pDeathElevatorOut;

    // attack
    CTexture* m_pDeathAttackBasicCombo1Right;
    CTexture* m_pDeathAttackBasicCombo1Left;
    CTexture* m_pDeathAttackBasicCombo2Right;
    CTexture* m_pDeathAttackBasicCombo2Left;
    CTexture* m_pDeathAttackBasicCombo3Right;
    CTexture* m_pDeathAttackBasicCombo3Left;
    CTexture* m_pDeathAttackBasicCombo4Right;
    CTexture* m_pDeathAttackBasicCombo4Left;

    CTexture* m_pDeath;

    //vector<CEffectObject*> m_vecPlayerEffect;

    //UINT m_iObjectSight;
    UINT DeathState;
    //UINT DeathAttactState; // Death Attack 이 None 이면 State 도 None 아닌가.
    UINT DeathAttackCombo;
    bool m_bToIdle;
    bool m_bOnIdle;
    bool OnElevator;
    //bool OnRender;
    int m_iJumpCount;

    CTexture* m_pRemove;

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

public:
    //CPlayer();
    CPlayer(wstring _pstring);
    ~CPlayer();
};

