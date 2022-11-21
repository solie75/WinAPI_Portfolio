
#include "CObject.h"
class CWall :
    public CObject
{
public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc, wstring _pstring) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    CLONE(CWall);

public:
    CWall();
    CWall(wstring _pstring);
    ~CWall();
};
