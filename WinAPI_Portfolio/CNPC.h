#pragma once
#include "CObject.h"

class CTexture;

class CNPC :
    public CObject
{
public:
    CTexture* m_pTexture;
    CTexture* m_pElevatorAppear;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

public:
    CLONE(CNPC);

public:
    CNPC();
    CNPC(wstring _pstring);
    ~CNPC();
};

