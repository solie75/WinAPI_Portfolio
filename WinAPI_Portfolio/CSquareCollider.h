#pragma once
#include "CCollider.h"
class CSquareCollider :
    public CCollider
{
public:
    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

    bool IsSquareCollider() { return true; }

public:
    virtual void BeginOverlap(CCollider* _other) override;
    virtual void EndOverlap(CCollider* _other) override;
    virtual void OnOverlap(CCollider* _other) override;

public:
    CLONE(CSquareCollider);

public:
    CSquareCollider(CObject* _pOwner);
    ~CSquareCollider();
};

