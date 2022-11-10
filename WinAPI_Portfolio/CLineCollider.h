#pragma once
#include "CCollider.h"
class CLineCollider :
    public CCollider
{
private:
    Vec StartPoint;
    Vec EndPoint;

    float Inclination;
    double Distance; //Distance bitween Player and Line

public:
    Vec GetStartPoint() { return StartPoint; }
    Vec GetEndPoint() { return EndPoint; }
    float GetInclination() { return Inclination; }
    double GetDistance() { return Distance; }

    void SetInclination(float _f) { Inclination = _f; }
    void SetDistance(double _d) { Distance = _d; }

    bool IsLineCollider() { return true; }

public:
    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    virtual void BeginOverlap(CCollider* _other) override;
    virtual void EndOverlap(CCollider* _other) override;
    virtual void OnOverlap(CCollider* _other) override;

public:
    CLONE(CLineCollider);

public:
    CLineCollider(CObject* _pOwner, Vec _pStart, Vec _pEnd);
    ~CLineCollider();
};

