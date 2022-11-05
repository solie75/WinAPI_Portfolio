#pragma once
#include "CObject.h"
class CGround :
    public CObject
{
private:
    Vec StartPoint;
    Vec EndPoint;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _string) override;

    void GroundSave(FILE* _pFile);
    void GroundLoad(FILE* _pFile);

public:
    CLONE(CGround);

public:
    CGround(Vec _pStart, Vec _pEnd);
    ~CGround();
};


