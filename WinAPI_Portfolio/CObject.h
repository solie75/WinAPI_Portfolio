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

	CAnimator* m_pAnimator;
	map<int, CCollider*> m_mapCollider;
	vector<CCollider*> m_vecCollider;
	
	//CCollider* m_pCollider;
	CRigidBody* m_pRigidBody;

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
	void CreateLineCollider(Vec _pStart, Vec _pEnd); // for GroundCollider
	void CreateRigidBody();

	//wstring GetStrName() { return strName; }
	
	virtual void CollisionBegin(CCollider* _pOther){}
	virtual void Colliding(CCollider* _pOther){}
	virtual void CollisionEnd(CCollider* _pOther){}



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

