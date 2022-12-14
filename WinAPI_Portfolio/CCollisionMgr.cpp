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

	vector<CCollider*> ColliderVector1 = _Object1->GetColliderVector();
	vector<CCollider*> ColliderVector2 = _Object2->GetColliderVector();

	for (size_t i = 0 ; i < ColliderVector1.size(); ++i)
	{
		for (size_t j = 0 ; j < ColliderVector2.size(); ++j) // Collier map 에 Collder가 하나만 존재하는 경우 Iter는 첫 번째에 ColliderMap의 End() 가 된다.'
		{
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

			

			// case of during OnOverlap
			if (CollisionBtwCollider(ColliderVector1[i], ColliderVector2[j]))
			{
				// Case of OnOverlap in PrevFrame
				if (iter->second) // 현재 비교중인 두 충돌체가 실제 충돌했고 또한 이전 프레임에도 충돌중인 경우
				{
					if (bDead) // 두 충돌체 중 하나라도 죽은 상태라면
					{
						/*if (ColliderVector1[i]->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
						{
							int i = ColliderVector1[i]->GetOverlapCount();
						}
						if (ColliderVector2[j]->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
						{
							int i
						}*/
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
				// case of OnOverlap in PrevFrame
				if (iter->second) // 현재 충돌상태가 아니지만 이전 프레임에서 충돌이 있었던 경우
				{
					if (ColliderVector1[i]->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
					{
						ColliderVector1[i]->GetOverlapCount();
					}
					if (ColliderVector2[j]->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
					{
						ColliderVector2[j]->GetOverlapCount();
					}
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
		if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
		{
			return false;
		}
		if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
		{
			return false;
		}
		
		CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider1);

		if (vCollider2Pos.x < _pLineCollider->GetEndPoint().x && vCollider2Pos.x > _pLineCollider->GetStartPoint().x)
		{
			
			// line 충돌체의 기울기 구하기
			_pLineCollider->SetInclination((_pLineCollider->GetEndPoint().y - _pLineCollider->GetStartPoint().y) / (_pLineCollider->GetEndPoint().x - _pLineCollider->GetStartPoint().x));
			float inclination = _pLineCollider->GetInclination();
			
			// line 충돌체의 y 절편 구하기
			float y_intercept = _pLineCollider->GetStartPoint().y - inclination * _pLineCollider->GetStartPoint().x;

			// line 충돌체와 그외 사각 충돌체 및 점에 대한 거리
			_pLineCollider->SetDistance(fabs((double)inclination * vCollider2Pos.x - (vCollider2Pos.y + vCollider2Scale.y/2.f) + y_intercept) / (sqrtf(inclination * inclination + 1)));

			if (_pLineCollider->GetDistance() <= 2.f) // distance == 0 이면 충돌이게 하고 싶지만 그렇게 하면 그냥 통과 해버린다.
			{
				return true;
				
			}

			float yOfLineCollider = (_pLineCollider->GetInclination() * vCollider2Pos.x) + y_intercept;
			
			if ((vCollider2Pos.y + (vCollider2Scale.y / 2.f)) > yOfLineCollider)
			{
				if (_Collider2->GetOwner()->GetObjectType() == (UINT)LAYER::PLAYER)
				{
					_Collider2->GetOwner()->SetPos(Vec(_Collider2->GetOwner()->GetPos().x, yOfLineCollider - 26.f));
				}
				if (_Collider2->GetOwner()->GetObjectType() == (UINT)LAYER::MONSTER)
				{
					_Collider2->GetOwner()->SetPos(Vec(_Collider2->GetOwner()->GetPos().x, yOfLineCollider - _Collider2->GetOwner()->GetScale().y / 2.f));
				}
				
			}

		}
	}
	if ((UINT)COLLIDER_TYPE::LINE == _Collider2->GetColliderType()) // case of LineCollider
	{
		if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
		{
			return false;
		}
		if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG)
		{
			return false;
		}
		if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
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


	
	// 충돌체 종류에 따른 충돌 무시
	if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK && _Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		return false;
	}
	if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK && _Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		return false;
	}

	if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
	{
		return false;
	}
	if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYERATTACK)
	{
		return false;
	}

	if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		return false;
	}
	if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::WALL)
	{
		return false;
	}
	//CLineCollider* _pLineCollider = dynamic_cast<CLineCollider*>(_Collider2);
	if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::GHOSTWOMAN && _Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	{
		return false;
	}
	if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::GHOSTWOMAN && _Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	{
		return false;
	}

	//if (_Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	//{
	//	CGhostWoman_Collider1->GetOwner()
	//}
	//if (_Collider2->GetColliderType() == (UINT)COLLIDER_TYPE::MONSTER_DETECT_RANGE_LONG && _Collider1->GetColliderType() == (UINT)COLLIDER_TYPE::PLAYER)
	//{
	//	return false;
	//}

	// 사각 충돌

	if (fabsf(vCollider1Pos.x - vCollider2Pos.x) <= (vCollider1Scale.x/2.f + vCollider2Scale.x/2.f) && fabsf(vCollider1Pos.y - vCollider2Pos.y) <= (vCollider1Scale.y / 2.f + vCollider2Scale.y / 2.f))
	{
		return true;
	}

	return false;
}
