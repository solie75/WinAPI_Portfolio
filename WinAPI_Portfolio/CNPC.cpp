#include "pch.h"
#include "CNPC.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCameraMgr.h"

CNPC::CNPC()
	: m_pTexture(nullptr)
{
}

CNPC::CNPC(wstring _pstring)
	: m_pTexture(nullptr)
{
	SetName(_pstring);
	CreateSquareCollider();
}

CNPC::~CNPC()
{
}


void CNPC::ObjectTick()
{
}

void CNPC::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

	m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);

	Vec vLeftTop = Vec(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	TransparentBlt(_dc
		, (int)vLeftTop.x
		, (int)vLeftTop.y
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width()
		, (int)m_pTexture->Height()
		, RGB(253, 253, 254)
	);
}
