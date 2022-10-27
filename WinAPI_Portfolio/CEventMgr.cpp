#include "pch.h"
#include "CEventMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CObject.h"

CEventMgr::CEventMgr()
{}

CEventMgr::~CEventMgr()
{}

void CEventMgr::EventMgrTick()
{
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EVENT_TYPE::CREATE_OBJECT: // wParam : Object Adress, lParam : Layer
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CObject* pNewObject = (CObject*)m_vecEvent[i].wPARAM;
			LAYER eLayer = (LAYER)m_vecEvent[i].lPARAM;

			pCurLevel->AddObject(pNewObject, eLayer);
			
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CObject* pObject = (CObject*)m_vecEvent[i].wPARAM;

			// defense the case of deleted same object in one tick
			if (false == pObject->m_bDead)
			{
				m_vecGarbage.push_back(pObject);
				pObject->m_bDead = true;
			}
		}
		break;
		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Next Level Type
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_vecEvent[i].wPARAM;
			CLevelMgr::GetInst()->ChangeLevel(eNextLevel);
		}
		break;
		default:
			break;
		}
	}

	m_vecEvent.clear();
}
