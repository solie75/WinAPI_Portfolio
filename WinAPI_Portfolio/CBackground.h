#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
public:
    CTexture* m_pTexture;
    bool StageON;

    // background Layer
    //CTexture* m_pGhostStageLayer1;
    //CTexture* m_pGhostStageLayer2;
    //CTexture* m_pGhostStageLayer3;
    //CTexture* m_pGhostStageLayer4;

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

