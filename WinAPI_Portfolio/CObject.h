#pragma once
#include "CEntity.h"

class CAnimator;
class CRigidBody;
class CCollider;

class CObject :
    public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;
	bool m_bDead;
	wstring strName;
	UINT m_iObjectType;

	CAnimator* m_pAnimator;
	map<int, CCollider*> m_mapCollider;
	vector<CCollider*> m_vecCollider;
	
	//CCollider* m_pCollider;
	CRigidBody* m_pRigidBody;

	UINT m_iObjectSight;
	float m_fObjectSpeed;

public:

	void SetPos(Vec _v) { m_vPos = _v; }
	Vec GetPos() { return m_vPos; }

	void SetScale(Vec _v) { m_vScale = _v; }
	Vec GetScale() { return m_vScale; }

	virtual void ObjectTick();
	virtual void Final_Tick() final;
	virtual void ObjectRender(HDC _dc, wstring _pstring);

	void CreateAnimator();
	void CreateSquareCollider();
	void AddSquareCollider();
	void AddSquareCollider(UINT _Collider_Type);
	void AddSquareCollider(UINT _Collider_Type, Vec _vSize, Vec _vPos);
	void CreateLineCollider(Vec _pStart, Vec _pEnd); // for GroundCollider
	void CreateRigidBody();
	UINT GetObjectType() { return m_iObjectType; }
	void SetObjectType(UINT _i) { m_iObjectType = _i; }
	UINT GetObjectSight() { return m_iObjectSight; }
	void SetObjectSight(UINT _i) { m_iObjectSight = _i; }
	float GetObjectSpeed() { return m_fObjectSpeed; }
	void SetObjectSpeed(float _f) { m_fObjectSpeed = _f;}

	//wstring GetStrName() { return strName; }
	
	virtual void BeginOverlap(CCollider* _pOther){}
	virtual void OnOverlap(CCollider* _pOther){}
	virtual void EndOverlap(CCollider* _pOther){}



	CAnimator* GetAnimator() {
		return m_pAnimator;
	}

	CCollider* GetCollider(int _ColliderIdx) {
		//map<int, CCollider*>::iterator iter = m_mapCollider.find(_ColliderIdx);
		//return iter->second;
		return m_vecCollider[_ColliderIdx];
	}

	//map<int, CCollider*> GetColliderMap() {
	//	return m_mapCollider;
	//}

	vector<CCollider*> GetColliderVector() {
		return m_vecCollider;
	}

	CRigidBody* GetRigidBody() {
		return m_pRigidBody;
	}

	void DeleteLastCollider() { m_vecCollider.erase(m_vecCollider.end() - 1); }



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

