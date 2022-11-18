#pragma once
#include "CObject.h"

class CTexture;
class CBackgroundObject;

class CNPC :
    public CObject
{
public:
    CTexture* m_pTexture;
    CTexture* m_pElevatorAppear;
    CTexture* m_pElevatorIdle;
    CTexture* m_pElevatorDisappear;
    CTexture* m_pInteractionTexture;
    CBackgroundObject* m_pInteract;

    Vec vDiffWithPlayer;

    bool m_bInteraction;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void CollisionBegin(CCollider* _pOther) override;
    virtual void Colliding(CCollider* _pOther) override;
    virtual void CollisionEnd(CCollider* _pOther) override;

public:
    CLONE(CNPC);

public:
    CNPC();
    CNPC(wstring _pstring);
    ~CNPC();
};

