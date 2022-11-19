#include "pch.h"
#include "CForwardground.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CLevelMgr.h"

CForwardground::CForwardground()
	: m_pGhostStageLayer4(nullptr)
{
}

CForwardground::CForwardground(wstring _pstring)
	: m_pGhostStageLayer4(nullptr)
{
	SetName(_pstring);

	m_pGhostStageLayer4 = CResourceMgr::GetInst()->FindTexture(_pstring);
}

CForwardground::~CForwardground()
{

}


void CForwardground::ObjectTick()
{
	CObject::ObjectTick();
}

void CForwardground::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vScale = GetScale();

		TransparentBlt
		(
			_dc,
			(int)(vPos.x - m_pGhostStageLayer4->Width() / 2.f),
			(int)(vPos.y - m_pGhostStageLayer4->Height() / 2.f),
			m_pGhostStageLayer4->Width(),
			m_pGhostStageLayer4->Height(),
			m_pGhostStageLayer4->GetDC(),
			0,
			0,
			m_pGhostStageLayer4->Width(),
			m_pGhostStageLayer4->Height(),
			RGB(253, 253, 254)
		);

	CObject::ObjectRender(_dc, _pstring);
}