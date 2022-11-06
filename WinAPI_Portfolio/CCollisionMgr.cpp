#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CObject.h"

#include "CLevelMgr.h"
#include "CCollider.h"
#include "CLineCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::LayerCheck(LAYER _layer1, LAYER _layer2)
{
	UINT iRow = (UINT)_layer1;
	UINT iCol = (UINT)_layer2;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionMgrTick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; ++iRow)
	{
		for (UINT iCol = 0; iCol < (UINT)LAYER::END; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
			{
				continue; // case of not Collision
			}
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(LAYER _layer1, LAYER _layer2)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObject*>& vecFirst = pCurLevel->GetLayer(_layer1);
	const vector<CObject*>& vecSecond = pCurLevel->GetLayer(_layer2);

	

	if (vecFirst.empty() || vecSecond.empty())
	{
		return;
	}

	for (size_t i = 0; i < vecFirst.size(); ++i)
	{
		if (true == vecFirst[i]->GetColliderMap().empty())
		{
			continue;
		}

		size_t j = 0;
		if (_layer1 == _layer2)
		{
			j = i;
		}

		for (; j < vecSecond.size(); ++j)
		{
			if (nullptr == vecSecond[j] || vecFirst[i] == vecSecond[j])
			{
				continue;
			}

			CollisionBtwObject(vecFirst[i], vecSecond[j]);
		}
	}
}

void CCollisionMgr::CollisionBtwObject(CObject* _Object1, CObject* _Object2)
{
	// check the state of Object's dead
	bool bDead = _Object1->IsDead() || _Object2->IsDead();

	//map<int, CCollider*>::iterator Iter1 = _Object1->GetColliderMap().begin();
	//map<int, CCollider*>::iterator Iter2 = _Object2->GetColliderMap().begin();

	map<int, CCollider*> ColliderMap1 = _Object1->GetColliderMap();
	map<int, CCollider*> ColliderMap2 = _Object2->GetColliderMap();

	map<int, CCollider*>::iterator Iter1 = ColliderMap1.begin();
	map<int, CCollider*>::iterator Iter2 = ColliderMap2.begin();

	for (; Iter1 != ColliderMap1.end(); ++Iter1)
	{ 
		for (; Iter2 != ColliderMap2.end(); ++Iter2)
		{
			// combine for creating ID of Collision 
			CollisionID ID = {};
			ID.FirstID = Iter1->second->GetID();
			ID.SecondID = Iter2->second->GetID();

			// check Collision in previous Flame
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if(iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			// case of during Colliding
			if (CollisionBtwCollider(Iter1->second, Iter2->second))
			{
				// Case of Colliding in PrevFrame
				if (iter->second)
				{
					if (bDead)
					{
						Iter1->second->EndOverlap(Iter2->second);
						Iter2->second->EndOverlap(Iter1->second);
					}
					else
					{
						Iter1->second->OnOverlap(Iter2->second);
						Iter2->second->OnOverlap(Iter1->second);
					}
				}
				else
				{
					if (!bDead)
					{
 						Iter1->second->BeginOverlap(Iter2->second);
						Iter2->second->BeginOverlap(Iter1->second);
						iter->second = true;
					}
				}
			}
			else
			{
				// case of Colliding in PrevFrame
				if (iter->second)
				{
					Iter1->second->EndOverlap(Iter2->second);
					Iter2->second->EndOverlap(Iter1->second);
					iter->second = false;
				}
			}


		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _Collider1, CCollider* _Collider2)
{
	if (Vec(0.f, 0.f) == _Collider1->GetColliderScale())
	{
		Vec vCollider2Pos = _Collider2->GetColliderFinalPos();
		Vec vCollider2Scale = _Collider2->GetColliderScale();

		CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider1);

		if (vCollider2Pos.x < _pLineCollider->GetEndPoint().x && vCollider2Pos.x > _pLineCollider->GetStartPoint().x)
		{
			// Vec(vCollider2Pos.x, vCollider2Pos + vCollider2Scale);
			float inclination = (_pLineCollider->GetEndPoint().y - _pLineCollider->GetStartPoint().y) / (_pLineCollider->GetEndPoint().x - _pLineCollider->GetStartPoint().x);
			double distance = fabs((double)inclination * vCollider2Pos.x - (vCollider2Pos.y + vCollider2Scale.y / 2.f) + (_pLineCollider->GetStartPoint().y - inclination * _pLineCollider->GetStartPoint().x)) / (sqrtf(inclination * inclination + 1));

			if (distance < 1.f)
			{
				return true;
			}
		}
	}
	if (Vec(0.f, 0.f) == _Collider2->GetColliderScale()) // case of LineCollider
	{
		Vec vCollider1Pos = _Collider1->GetColliderFinalPos();
		Vec vCollider1Scale = _Collider1->GetColliderScale();

		CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider2);

		if (vCollider1Pos.x < _pLineCollider->GetEndPoint().x && vCollider1Pos.x > _pLineCollider->GetStartPoint().x)
		{
			// Vec(vCollider2Pos.x, vCollider2Pos + vCollider2Scale);
			float inclination = (_pLineCollider->GetEndPoint().y - _pLineCollider->GetStartPoint().y) / (_pLineCollider->GetEndPoint().x - _pLineCollider->GetStartPoint().x);
			double distance = fabs((double)inclination * vCollider1Pos.x - (vCollider1Pos.y + vCollider1Scale.y) + (_pLineCollider->GetStartPoint().y - inclination * _pLineCollider->GetStartPoint().x)) / (sqrtf(inclination * inclination + 1));

			if (distance == 0.f)
			{
				return true;
			}
		}

	}

	Vec vCollider1Pos = _Collider1->GetColliderFinalPos();
	Vec vCollider1Scale = _Collider1->GetColliderScale();

	Vec vCollider2Pos = _Collider2->GetColliderFinalPos();
	Vec vCollider2Scale = _Collider2->GetColliderScale();

	if (fabsf(vCollider1Pos.x - vCollider2Pos.x) > (vCollider1Scale.x + vCollider2Scale.x))
	{
		return false;
	}
	if (fabsf(vCollider1Pos.y - vCollider2Pos.y) > (vCollider1Scale.y + vCollider2Scale.y))
	{
		return false;
	}

	return true;
}
