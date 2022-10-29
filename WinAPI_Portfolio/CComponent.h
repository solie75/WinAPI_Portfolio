#pragma once
#include "CEntity.h"

class CObject;

class CComponent :
    public CEntity
{
private:
    CObject* m_pOwner;

public:
    virtual void ComponentTick() = 0;
    virtual void Final_Tick() {};
    virtual void ComponentRender(HDC _dc) = 0;

public:
    CObject* GetOwner() { return m_pOwner; }

private:
    void SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }

public:
    CComponent(CObject* _pOwner);
    ~CComponent();

    friend class CObject;
};

