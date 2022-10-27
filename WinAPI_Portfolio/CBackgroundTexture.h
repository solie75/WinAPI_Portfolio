#pragma once
#include "CObject.h"

class CTexture;

class CBackgroundTexture :
    public CObject
{
public:
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CBackgroundTexture);

public:
    CBackgroundTexture();
    CBackgroundTexture(wstring _pstring);
    ~CBackgroundTexture();
};

