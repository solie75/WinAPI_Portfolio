#pragma once
#include "CCollider.h"
class CLineCollider :
    public CCollider
{
private:
    Vec StartPoint;
    Vec EndPoint;

public:
    Vec GetStartPoint() { return StartPoint; }
    Vec GetEndPoint() { return EndPoint; }

public:
    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    virtual void BeginOverlap(CCollider* _other);
    virtual void EndOverlap(CCollider* _other);
    virtual void OnOverlap(CCollider* _other);

public:
    CLONE(CLineCollider);

public:
    CLineCollider(CObject* _pOwner, Vec _pStart, Vec _pEnd);
    ~CLineCollider();
};

