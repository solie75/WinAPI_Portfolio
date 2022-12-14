#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec m_vColliderOffsetPos;
    Vec m_vColliderFinalPos;
    Vec m_vColliderScale;

    UINT m_ColliderType;

    int m_iOverlapCount;

public:
    void SetColliderOffSetPos(Vec _vOffsetPos) { m_vColliderOffsetPos = _vOffsetPos;}
    void SetColliderScale(Vec _vScale) { m_vColliderScale = _vScale;}
    void SetOverlapCount(int _i) { m_iOverlapCount = _i; }
    void AddOverlapCount() { ++m_iOverlapCount; }
    void SubtractOvelapCount() { --m_iOverlapCount; }
    int GetOverlapCount() { return m_iOverlapCount; }
    void SetColliderType(UINT _ColliderType) { m_ColliderType = _ColliderType; }
    UINT GetColliderType() { return m_ColliderType; }


    Vec GetColliderOffSetPos() { return m_vColliderOffsetPos; }
    Vec GetColliderFinalPos() { return m_vColliderFinalPos; }
    Vec GetColliderScale() { return m_vColliderScale; }

public:
    virtual void ComponentTick() override;
    virtual void Final_Tick() override;
    virtual void ComponentRender(HDC _dc);

public:
    virtual void BeginOverlap(CCollider* _other);
    virtual void EndOverlap(CCollider* _other);
    virtual void OnOverlap(CCollider* _other);

public:
    CLONE(CCollider);

public:
    CCollider(CObject* _pOwner);
    CCollider(const CCollider& _other);
    ~CCollider();
};

