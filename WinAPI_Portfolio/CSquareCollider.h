#pragma once
#include "CCollider.h"
class CSquareCollider :
    public CCollider
{
public:
    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    virtual void BeginOverlap(CCollider* _other);
    virtual void EndOverlap(CCollider* _other);
    virtual void OnOverlap(CCollider* _other);

public:
    CLONE(CSquareCollider);

public:
    CSquareCollider(CObject* _pOwner);
    ~CSquareCollider();
};
