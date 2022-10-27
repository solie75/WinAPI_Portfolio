#include "pch.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CResourceMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEventMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CEngine::CEngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hWnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// window size set up
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC init
	m_hDC = GetDC(m_hMainWnd);

	// create bitmap for back buffer
	m_pMemTex = CResourceMgr::GetInst()->CreateTexture(L"BeckBuffer", m_ptResolution.x, m_ptResolution.y);

	// create common Pen and brush
	CreatePenBrush();

	// Manager Init
	CPathMgr::GetInst()->PathMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
	CLevelMgr::GetInst()->LevelMgrInit();
}

void CEngine::EngineProgress()
{
	CEngineTick();
	CEngineRender();

	// apply event in next frame
	CEventMgr::GetInst()->EventMgrTick();
}

void CEngine::CEngineTick()
{
	// count of FPS, DeltaTime
	CTimeMgr::GetInst()->TimeMgrTick();

	// Check Key Event
	CKeyMgr::GetInst()->KeyMgrTick();

	// callback all Object in CurLevel
	CLevelMgr::GetInst()->LevelMgrTick();

	// Callback all Collision
	//CollisionMgr::GetInst()->CollisionMgrTick();
}

void CEngine::CEngineRender()
{
	// screen clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Level Rendering
	CLevelMgr::GetInst()->LevelMgrRender(m_pMemTex->GetDC());

	// Camera Effect?
	
	// MemBitmap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	// TimeMgr Rendering
	CTimeMgr::GetInst()->TimeMgrRender();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}