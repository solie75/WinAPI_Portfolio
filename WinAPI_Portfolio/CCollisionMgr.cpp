#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CObject.h"
#include "CPlayer.h"

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
		if (0 == vecFirst[i]->GetColliderVector().size())
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
			/*if (nullptr == ColliderVector1[j].GetCollider() || ColliderVector2[i] == vecRight[j])
				continue;*/
			// combine for creating ID of Collision 
			CollisionID ID = {};
			ID.FirstID = ColliderVector1[i]->GetID();
			ID.SecondID = ColliderVector2[j]->GetID();
			ID.id = (ID.FirstID + ID.SecondID);

			// check Collision in previous Flame
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end()) // 조합한 충돌 아이디가 이전 충돌 map 에 존재 하지 않으면 충돌 상태 false로 map 에 저장
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id); // 저장한 뒤 해당 id 를 iter 에 대입하도록 다시 찾음
			}
			// -> 모든 충돌의 경우의 수는 다 저장이 된다.

			

			// case of during Colliding
			if (CollisionBtwCollider(ColliderVector1[i], ColliderVector2[j]))
			{
				// Case of Colliding in PrevFrame
				if (iter->second) // 현재 비교중인 두 충돌체가 실제 충돌했고 또한 이전 프레임에도 충돌중인 경우
				{
					if (bDead) // 두 충돌체 중 하나라도 죽은 상태라면
					{
						ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
						ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
						iter->second = false;
					}
					else // 두 충돌체 모두 살아있는 상태라면
					{
						ColliderVector1[i]->OnOverlap(ColliderVector2[j]);
						ColliderVector2[j]->OnOverlap(ColliderVector1[i]);
					}
				}
				else // 이전프레임에서 충돌이 없었고 현재 프레임에 충돌이 있는 경우
				{
					if (!bDead) // 두 충돌체가 모두 살아있다면
					{
						ColliderVector1[i]->BeginOverlap(ColliderVector2[j]);
						ColliderVector2[j]->BeginOverlap(ColliderVector1[i]);
						iter->second = true; // 충돌 상태를 true 로 바꾼다.
					}
				}
			}
			else
			{
				// case of Colliding in PrevFrame
				if (iter->second) // 현재 충돌상태가 아니지만 이전 프레임에서 충돌이 있었던 경우
				{
					ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
					ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
					iter->second = false; // 더 이상 충돌이 아니므로 충돌상태를 false 로 바꾼다.
				}
			}


		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _Collider1, CCollider* _Collider2)
{
	Vec vCollider1Pos = _Collider1->GetColliderFinalPos();
	Vec vCollider1Scale = _Collider1->GetColliderScale();

	Vec vCollider2Pos = _Collider2->GetColliderFinalPos();
	Vec vCollider2Scale = _Collider2->GetColliderScale();

	if ((UINT)COLLIDER_TYPE::LINE == _Collider1->GetColliderType())
	{
		if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
		{
			return false;
		}
		
		CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider1);

		if (vCollider2Pos.x < _pLineCollider->GetEndPoint().x && vCollider2Pos.x > _pLineCollider->GetStartPoint().x)
		{
			
			_pLineCollider->SetInclination((_pLineCollider->GetEndPoint().y - _pLineCollider->GetStartPoint().y) / (_pLineCollider->GetEndPoint().x - _pLineCollider->GetStartPoint().x));
			float inclination = _pLineCollider->GetInclination();
			float y_intercept = _pLineCollider->GetStartPoint().y - inclination * _pLineCollider->GetStartPoint().x;
			_pLineCollider->SetDistance(fabs((double)inclination * vCollider2Pos.x - (vCollider2Pos.y + vCollider2Scale.y/2.f) + y_intercept) / (sqrtf(inclination * inclination + 1)));

			if (_pLineCollider->GetDistance() <= 2.f) // distance == 0 이면 충돌이게 하고 싶지만 그렇게 하면 그냥 통과 해버린다.
			{
				return true;
				
			}

			float yOfLineCollider = (_pLineCollider->GetInclination() * vCollider2Pos.x) + y_intercept;
			
			if ((vCollider2Pos.y + (vCollider2Scale.y / 2.f)) > yOfLineCollider)
			{
				_Collider2->GetOwner()->SetPos(Vec(_Collider2->GetOwner()->GetPos().x, yOfLineCollider - 26.f)); // 왜 vCollider2Scale.y / 2.f 가 아니라 26.f 라는 값이 나오는가.
			}

		}
	}
	if ((UINT)COLLIDER_TYPE::LINE == _Collider2->GetColliderType()) // case of LineCollider
	{
		if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
		{
			return false;
		}
		
		CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider2);

		if (vCollider1Pos.x < _pLineCollider->GetEndPoint().x && vCollider1Pos.x > _pLineCollider->GetStartPoint().x)
		{
			
			_pLineCollider->SetInclination((_pLineCollider->GetEndPoint().y - _pLineCollider->GetStartPoint().y) / (_pLineCollider->GetEndPoint().x - _pLineCollider->GetStartPoint().x));
			float inclination = _pLineCollider->GetInclination();
			float y_intercept = _pLineCollider->GetStartPoint().y - inclination * _pLineCollider->GetStartPoint().x;
			_pLineCollider->SetDistance(fabs((double)inclination * vCollider1Pos.x - (vCollider1Pos.y + vCollider1Scale.y) + y_intercept) / (sqrtf(inclination * inclination + 1)));

			if (_pLineCollider->GetDistance() <= 2.f)
			{
				return true;
				
			}

			float yOfLineCollider = (_pLineCollider->GetInclination() * vCollider1Pos.x) + y_intercept;
			
			if ((vCollider1Pos.y + vCollider1Scale.y / 2.f) > yOfLineCollider)
			{
				_Collider1->GetOwner()->SetPos(Vec(_Collider1->GetOwner()->GetPos().x, yOfLineCollider));
			}
		}

	}



	if (fabsf(vCollider1Pos.x - vCollider2Pos.x) > (vCollider1Scale.x/2.f + vCollider2Scale.x/2.f))
	{
		return false;
	}
	if (fabsf(vCollider1Pos.y - vCollider2Pos.y) > (vCollider1Scale.y / 2.f + vCollider2Scale.y / 2.f))
	{
		return false;
	}

	return true;
}
