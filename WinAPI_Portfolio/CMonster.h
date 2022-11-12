#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
public:
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CMonster);

public:
    CMonster();
    CMonster(wstring _pstring);
    ~CMonster();
};

