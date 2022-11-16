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
		for (size_t j = 0 ; j < ColliderVector2.size(); ++j) // Collier map �� Collder�� �ϳ��� �����ϴ� ��� Iter�� ù ��°�� ColliderMap�� End() �� �ȴ�.'
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
			if (iter == m_mapPrevInfo.end()) // ������ �浹 ���̵� ���� �浹 map �� ���� ���� ������ �浹 ���� false�� map �� ����
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id); // ������ �� �ش� id �� iter �� �����ϵ��� �ٽ� ã��
			}
			// -> ��� �浹�� ����� ���� �� ������ �ȴ�.

			

			// case of during Colliding
			if (CollisionBtwCollider(ColliderVector1[i], ColliderVector2[j]))
			{
				// Case of Colliding in PrevFrame
				if (iter->second) // ���� ������ �� �浹ü�� ���� �浹�߰� ���� ���� �����ӿ��� �浹���� ���
				{
					if (bDead) // �� �浹ü �� �ϳ��� ���� ���¶��
					{
						ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
						ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
						iter->second = false;
					}
					else // �� �浹ü ��� ����ִ� ���¶��
					{
						ColliderVector1[i]->OnOverlap(ColliderVector2[j]);
						ColliderVector2[j]->OnOverlap(ColliderVector1[i]);
					}
				}
				else // ���������ӿ��� �浹�� ������ ���� �����ӿ� �浹�� �ִ� ���
				{
					if (!bDead) // �� �浹ü�� ��� ����ִٸ�
					{
						ColliderVector1[i]->BeginOverlap(ColliderVector2[j]);
						ColliderVector2[j]->BeginOverlap(ColliderVector1[i]);
						iter->second = true; // �浹 ���¸� true �� �ٲ۴�.
					}
				}
			}
			else
			{
				// case of Colliding in PrevFrame
				if (iter->second) // ���� �浹���°� �ƴ����� ���� �����ӿ��� �浹�� �־��� ���
				{
					ColliderVector1[i]->EndOverlap(ColliderVector2[j]);
					ColliderVector2[j]->EndOverlap(ColliderVector1[i]);
					iter->second = false; // �� �̻� �浹�� �ƴϹǷ� �浹���¸� false �� �ٲ۴�.
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

			if (_pLineCollider->GetDistance() <= 2.f) // distance == 0 �̸� �浹�̰� �ϰ� ������ �׷��� �ϸ� �׳� ��� �ع�����.
			{
				return true;
				
			}

			float yOfLineCollider = (_pLineCollider->GetInclination() * vCollider2Pos.x) + y_intercept;
			
			if ((vCollider2Pos.y + (vCollider2Scale.y / 2.f)) > yOfLineCollider)
			{
				_Collider2->GetOwner()->SetPos(Vec(_Collider2->GetOwner()->GetPos().x, yOfLineCollider - 26.f)); // �� vCollider2Scale.y / 2.f �� �ƴ϶� 26.f ��� ���� �����°�.
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
