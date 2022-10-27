#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_iCallCount(0)
	, m_fDeltaTime(0.f) // time during one tick
	, m_fTime(0.f) // Accumulated real time
{}

CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::TimeMgrInit()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::TimeMgrTick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)(m_llFrequency.QuadPart);

	m_fTime += m_fDeltaTime;

	++m_iCallCount;

	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::TimeMgrRender()
{
	// once per second
	if (1.f <= m_fTime)
	{
		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS: %d, DT : %f", m_iCallCount, m_fDeltaTime);
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);

		m_fTime = 0;
		m_iCallCount = 0;
	}
}
