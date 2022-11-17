#pragma once
#include "CObject.h"

class CTexture;

class CDialog :
    public CObject
{
public:
    CTexture* m_pTexture;
    int CurAnim;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    //virtual void CollisionBegin(CCollider* _pOther) override;
    //virtual void Colliding(CCollider* _pOther) override;
    //virtual void CollisionEnd(CCollider* _pOther) override;

    void SetCurDialAnim(int _i)
    {
        CurAnim = _i;
    }

    int GetCurDialAnim() { return CurAnim; }

public:
    CLONE(CDialog);

public:
    CDialog();
    CDialog(wstring _pstring);
    ~CDialog();
};

