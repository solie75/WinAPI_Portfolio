#include "pch.h"
#include "CLevelMgr.h"

#include "CStartLevel.h"
#include "CDeathOfficeLevel.h"
#include "CGhostStageLevel.h"
#include "CBoss1Level.h"
#include "CSoldierStageLevel.h"
#include "CBoss2Level.h"
#include "CEndLevel.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	for (size_t i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::LevelMgrInit()
{
	// Create Level
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::DEATHOFFICE] = new CDeathOfficeLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::GHOSTSTAGE] = new CGhostStageLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_MRGORDONGRIMES] = new CBoss1Level;
	m_arrLevel[(UINT)LEVEL_TYPE::SOLDIERSTAGE] = new CSoldierStageLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_MRGORDONGRIMES] = new CBoss2Level;
	//m_arrLevel[(UINT)LEVEL_TYPE::END] = new CEndLevel;

	m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::GHOSTSTAGE];
	CurLevelType = (UINT)LEVEL_TYPE::GHOSTSTAGE;
	m_pCurLevel->LevelInit();
}

void CLevelMgr::LevelMgrTick()
{
	m_pCurLevel->LevelTick();
	m_pCurLevel->Final_Tick();
}

void CLevelMgr::LevelMgrRender(HDC _dc)
{
	m_pCurLevel->LevelRender(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// 현재 레벨과 변경하려는 레벨이 동일한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	m_pCurLevel->LevelExit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];
	CurLevelType = (UINT)_eNext;

	m_pCurLevel->LevelEnter();

}
