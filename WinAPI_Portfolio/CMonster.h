#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
public:

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    CLONE(CMonster);

public:
    CMonster();
    CMonster(wstring _pstring);
    ~CMonster();
};

