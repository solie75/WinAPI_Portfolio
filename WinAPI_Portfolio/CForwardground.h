#pragma once
#include "CObject.h"

class CTexture;


class CForwardground :
    public CObject
{
public:
    CTexture* m_pGhostStageLayer4;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;



public:
    CLONE(CForwardground);

public:
    CForwardground();
    CForwardground(wstring _pstring);
    ~CForwardground();
};

