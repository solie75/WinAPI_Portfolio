#pragma once
#include "CObject.h"

class CTexture;

class CEffectObject :
    public CObject
{
public:
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CEffectObject);

public:
    CEffectObject();
    CEffectObject(wstring _pstring);
    ~CEffectObject();
};

