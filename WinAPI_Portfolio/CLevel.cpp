#include "pch.h"
#include "CLevel.h"
#include "CObject.h"

CLevel::CLevel()
	: bgm1(nullptr)
{
}

CLevel::~CLevel()
{
	// 모든 오브젝트 삭제
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			DEL(m_arrLayer[i][ii]);
		}
	}
}

void CLevel::LevelTick()
{
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->ObjectTick();
		}
	}
}

void CLevel::Final_Tick()
{
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->Final_Tick();
		}
	}
}

void CLevel::LevelRender(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
				
			}
			else
			{
				(*iter)->ObjectRender(_dc, (*iter)->GetName());
				++iter;
			}
		}
	}
}

void CLevel::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
			{
				continue;
			}

			DEL(m_arrLayer[i][j]);
		}
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}