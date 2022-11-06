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

	//map<int, CCollider*> ColliderMap1 = _Object1->GetColliderMap();
	//map<int, CCollider*> ColliderMap2 = _Object2->GetColliderMap();

	vector<CCollider*> ColliderVector1 = _Object1->GetColliderVector();
	vector<CCollider*> ColliderVector2 = _Object2->GetColliderVector();

	//map<int, CCollider*>::iterator Iter1 = ColliderMap1.begin();
	//map<int, CCollider*>::iterator Iter2 = ColliderMap2.begin();

	for (size_t i = 0 ; i < ColliderVector1.size(); ++i)
	{
		for (size_t j = 0 ; j < ColliderVector2.size(); ++j) // Collier map 에 Collder가 하나만 존재하는 경우 Iter는 첫 번째에 ColliderMap의 End() 가 된다.'
		{
			// combine for creating ID of Collision 
			CollisionID ID = {};
			ID.FirstID = ColliderVector1[i]->GetID();
			ID.SecondID = ColliderVector2[j]->GetID();

			// check Collision in previous Flame
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			// case of during Colliding
			if (CollisionBtwCollider(ColliderVector1[i], ColliderVector2[j]))
			{
				// Case of Colliding in PrevFrame
				if (iter->second)
				{
					if (bDead)
					{
						ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
						ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
					}
					else
					{
						ColliderVector1[i]->OnOverlap(ColliderVector2[j]);
						ColliderVector2[j]->OnOverlap(ColliderVector1[i]);
					}
				}
				else
				{
					if (!bDead)
					{
						ColliderVector1[i]->BeginOverlap(ColliderVector2[j]);
						ColliderVector2[j]->BeginOverlap(ColliderVector1[i]);
						iter->second = true;
					}
				}
			}
			else
			{
				// case of Colliding in PrevFrame
				if (iter->second)
				{
					ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
					ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
					iter->second = false;
				}
			}


		}
	}

	//for (; Iter1 != ColliderMap1.end(); ++Iter1)
	//{ 
	//	for (; Iter2 != ColliderMap2.end(); ++Iter2) // Collier map 에 Collder가 하나만 존재하는 경우 Iter는 첫 번째에 ColliderMap의 End() 가 된다.'
	//	{
	//		// combine for creating ID of Collision 
	//		CollisionID ID = {};
	//		ID.FirstID = Iter1->second->GetID();
	//		ID.SecondID = Iter2->second->GetID();

	//		// check Collision in previous Flame
	//		map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
	//		if(iter == m_mapPrevInfo.end())
	//		{
	//			m_mapPrevInfo.insert(make_pair(ID.id, false));
	//			iter = m_mapPrevInfo.find(ID.id);
	//		}

	//		// case of during Colliding
	//		if (CollisionBtwCollider(Iter1->second, Iter2->second)) // 여기에서 계속해서 첫번째 LineCollider 가 들어간다.
	//		{
	//			// Case of Colliding in PrevFrame
	//			if (iter->second)
	//			{
	//				if (bDead)
	//				{
	//					Iter1->second->EndOverlap(Iter2->second);
	//					Iter2->second->EndOverlap(Iter1->second);
	//				}
	//				else
	//				{
	//					Iter1->second->OnOverlap(Iter2->second);
	//					Iter2->second->OnOverlap(Iter1->second);
	//				}
	//			}
	//			else
	//			{
	//				if (!bDead)
	//				{
 //						Iter1->second->BeginOverlap(Iter2->second);
	//					Iter2->second->BeginOverlap(Iter1->second);
	//					iter->second = true;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			// case of Colliding in PrevFrame
	//			if (iter->second)
	//			{
	//				Iter1->second->EndOverlap(Iter2->second);
	//				Iter2->second->EndOverlap(Iter1->second);
	//				iter->second = false;
	//			}
	//		}


	//	}
	//}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _Collider1, CCollider* _Collider2)
{
	if ((UINT)COLLIDER_TYPE::LINE == _Collider1->GetColliderType())
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
	if ((UINT)COLLIDER_TYPE::LINE == _Collider2->GetColliderType()) // case of LineCollider
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
