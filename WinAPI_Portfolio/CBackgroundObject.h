#pragma once
#include "CObject.h"

class CTexture;

class CBackgroundObject :
    public CObject
{
public:
    CTexture* m_pTexture;
    CTexture* m_pElevatorClose;
    CTexture* m_pElevatorDigIn;
    bool m_bShow;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    void SetBoolShow(bool _b) { m_bShow = _b; }

public:
    CLONE(CBackgroundObject);

public:
    CBackgroundObject();
    CBackgroundObject(wstring _pstring);
    ~CBackgroundObject();

};

