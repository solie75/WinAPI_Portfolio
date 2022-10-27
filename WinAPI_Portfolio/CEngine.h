#pragma once

class CEngine
{
	SINGLE(CEngine)

private:
	HWND m_hMainWnd;
	HDC m_hDC;
	POINT m_ptResolution;
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

private:
	void CreatePenBrush();

public:
	HWND GetMainWnd() { return m_hMainWnd; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }

public:
	void CEngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	
	void progress();
};

