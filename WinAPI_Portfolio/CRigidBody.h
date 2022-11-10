#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec m_vForce;
    Vec m_vVelocity;
    float m_fMass;

    float m_fFriction;
    float m_fFrictionScale;

    float m_fVelocityLimit;
    float m_fGravityVLimit;

    float m_fGravityAccel;
    bool m_bGravityUse;
    bool m_bOnGround;


public:
    virtual void ComponentTick() override;
    virtual void Final_Tick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void AddForce(Vec _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }
    void SetVelocity(Vec _vVelocity) { m_vVelocity = _vVelocity; }
    Vec GetVelocity() { return m_vVelocity; }

    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }

    void AddVelocity(Vec _vAddV) { m_vVelocity += _vAddV; }

    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetBoolOnGround(bool _bGround);
    bool GetBoolOnGround() { return m_bOnGround; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }

public:
    CLONE(CRigidBody);

public:
    CRigidBody(CObject* _pOwner);
    CRigidBody(const CRigidBody& _other);
    virtual ~CRigidBody();
};

