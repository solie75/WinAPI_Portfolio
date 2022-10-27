#include "pch.h"
#include "CBackgroundTexture.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"

CBackgroundTexture::CBackgroundTexture()
	: m_pTexture(nullptr)
{
}

CBackgroundTexture::CBackgroundTexture(wstring _pstring)
	: m_pTexture(nullptr)
{
	SetName(_pstring);
}

CBackgroundTexture::~CBackgroundTexture()
{

}


void CBackgroundTexture::ObjectTick()
{
	CObject::ObjectTick();
}

void CBackgroundTexture::ObjectRender(HDC _dc, wstring _pstring)
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

