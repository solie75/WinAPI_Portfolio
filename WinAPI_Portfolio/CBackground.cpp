#include "pch.h"
#include "CBackground.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CLevelMgr.h"

CBackground::CBackground()
	: m_pTexture(nullptr)
{
}

CBackground::CBackground(wstring _pstring)
	: m_pTexture(nullptr)
	//, m_pGhostStageLayer1(nullptr)
	//, m_pGhostStageLayer2(nullptr)
	//, m_pGhostStageLayer3(nullptr)
	//, m_pGhostStageLayer4(nullptr)
{
	SetName(_pstring);

	//m_pGhostStageLayer1 = CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer1", L"texture\\Ghost_Stage_Layer1");
	//m_pGhostStageLayer2 = CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer2", L"texture\\Ghost_Stage_Layer2");
	//m_pGhostStageLayer3 = CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer3", L"texture\\Ghost_Stage_Layer3");
	//m_pGhostStageLayer4 = CResourceMgr::GetInst()->LoadTexture(L"Ghost_Stage_Layer4", L"texture\\Ghost_Stage_Layer4");

	if (_pstring == L"DeathOffice")
	{
		CreateLineCollider(Vec(-740.f, 800.f), Vec(100.f, 800.f));
		CreateLineCollider(Vec(100.f, 800.f), Vec(250.f, 625.f));
		CreateLineCollider(Vec(250.f, 625.f), Vec(1550.f, 625.f));
		CreateLineCollider(Vec(1550.f, 625.f), Vec(1700.f, 800.f));
		CreateLineCollider(Vec(1700.f, 800.f), Vec(2335.f, 800.f));
	}

	if (_pstring == L"Ghost_Stage_Layer3")
	{
		CreateLineCollider(Vec(0.f, 1150.f), Vec(3500.f, 1150.f));
		CreateLineCollider(Vec(3500.f, 1150.f), Vec(4200.f, 1720.f));
		CreateLineCollider(Vec(4200.f, 1720.f), Vec(5380.f, 1720.f));
		CreateLineCollider(Vec(5380.f, 1720.f), Vec(5380.f, 2530.f));
		CreateLineCollider(Vec(5380.f, 2530.f), Vec(10040.f, 2530.f));
		CreateLineCollider(Vec(9820.f, 2100.f), Vec(10660.f, 2100.f));
		CreateLineCollider(Vec(10660.f, 2100.f), Vec(10660.f, 1910.f));
		CreateLineCollider(Vec(10660.f, 1910.f), Vec(11860.f, 1910.f));
	}
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

	if(CLevelMgr::GetInst()->GetCurLevelType() == (UINT)LEVEL_TYPE::DEATHOFFICE)
	{
		BitBlt(_dc
			, (int)(vPos.x - m_pTexture->Width() / 2.f)
			, (int)(vPos.y - m_pTexture->Height() / 2.f)
			, m_pTexture->Width()
			, m_pTexture->Height()
			, m_pTexture->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}

	if (CLevelMgr::GetInst()->GetCurLevelType() == (UINT)LEVEL_TYPE::GHOSTSTAGE)
	{
		TransparentBlt
		(
			_dc,
			(int)(vPos.x - m_pTexture->Width() / 2.f),
			(int)(vPos.y - m_pTexture->Height() / 2.f),
			m_pTexture->Width(),
			m_pTexture->Height(),
			m_pTexture->GetDC(),
			0,
			0,
			m_pTexture->Width(),
			m_pTexture->Height(),
			RGB(253, 253, 254)
		);
	}
	
	CObject::ObjectRender(_dc, _pstring);
}

