#include "pch.h"
#include "CBackground.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"

CBackground::CBackground()
	: m_pTexture(nullptr)
{
}

CBackground::CBackground(wstring _pstring)
	: m_pTexture(nullptr)
{
	SetName(_pstring);

	// 여기에서 _pstring 으로 LineCollider FILE 을 검색하여 로드해 CreateLineCollider 를 반복 재생한다.
	CreateLineCollider(Vec(0.f,800.f), Vec(100.f, 800.f), 0);
	CreateLineCollider(Vec(100.f, 800.f), Vec(250.f, 625.f), 1);
	CreateLineCollider(Vec(250.f, 625.f), Vec(1550.f, 625.f), 2);
	CreateLineCollider(Vec(1550.f, 625.f), Vec(1700.f, 800.f), 3);
	CreateLineCollider(Vec(1700.f, 800.f), Vec(2372.f, 800.f), 4);
}

CBackground::~CBackground()
{

}


void CBackground::ObjectTick()
{
	CObject::ObjectTick();
}

void CBackground::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

	//Vec vLeftTop = Vec(vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f);

	m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);

	BitBlt(_dc
		, (int)(vPos.x - m_pTexture->Width() / 2.f)
		, (int)(vPos.y - m_pTexture->Height() / 2.f)
		, m_pTexture->Width()
		, m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0
		, 0
		, SRCCOPY);



	CObject::ObjectRender(_dc, _pstring);
}

