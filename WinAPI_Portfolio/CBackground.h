#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
public:
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CBackground);

public:
    CBackground();
    CBackground(wstring _pstring);
    ~CBackground();
};

