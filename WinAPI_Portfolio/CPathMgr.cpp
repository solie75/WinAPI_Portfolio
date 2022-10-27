#include "pch.h"
#include "CPathMgr.h"
#include "CEngine.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{}

void CPathMgr::PathMgrInit()
{
	GetCurrentDirectory(256, m_szContentPath);

	// to Parent Folder
	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; --i)
	{
		if (L'\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = 0;
			break;
		}
	}

	// + bin\\content
	wcscat_s(m_szContentPath, L"\\bin\\content\\");

	PathMgrRender();
}

void CPathMgr::PathMgrRender()
{
	SetWindowText(CEngine::GetInst()->GetMainWnd(), m_szContentPath);
}
