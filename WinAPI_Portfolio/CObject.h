#pragma once
#include "CEntity.h"
class CObject :
    public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;
	bool m_bDead;
	wstring strName;

public:
	void SetPos(Vec _v) { m_vPos = _v; }
	Vec GetPos() { return m_vPos; }

	void SetScale(Vec _v) { m_vScale = _v; }
	Vec GetScale() { return m_vScale; }

	virtual void ObjectTick();
	virtual void Final_Tick() final;
	virtual void ObjectRender(HDC _hdc, wstring);

public:
	bool IsDead() { return m_bDead; }
	void SetDead();
	virtual CObject* Clone() = 0;

	public:
	CObject();
	CObject(const CObject& _other); 
	virtual ~CObject();

	friend class CEventMgr;
};

