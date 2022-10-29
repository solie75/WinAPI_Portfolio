#pragma once
#include "CObject.h"

class CTexture;

class CBackgroundObject :
    public CObject
{
public:
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CBackgroundObject);

public:
    CBackgroundObject();
    CBackgroundObject(wstring _pstring);
    ~CBackgroundObject();

};

