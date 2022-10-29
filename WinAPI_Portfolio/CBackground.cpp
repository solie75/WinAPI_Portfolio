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

