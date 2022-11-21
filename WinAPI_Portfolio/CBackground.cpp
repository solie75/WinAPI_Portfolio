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
		// GroundCollider
		CreateLineCollider(Vec(-516.f, 862.f), Vec(324.f, 862.f));
		CreateLineCollider(Vec(324.f, 862.f), Vec(474.f, 686.f));
		CreateLineCollider(Vec(474.f, 686.f), Vec(1774.f, 686.f));
		CreateLineCollider(Vec(1774.f, 686.f), Vec(1924.f, 862.f));
		CreateLineCollider(Vec(1924.f, 862.f), Vec(2559.f, 862.f));

		// WallCollider //여기에서 VPos 까지 입력하면 그게 곧 finalpos 가 된다.
		/*AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 1000.f), Vec(-(1480.f), 0.f));
		AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(60.f, 1000.f), Vec(+(1524.f), 0.f));*/
	}

	if (_pstring == L"Ghost_Stage_Layer3")
	{
		CreateLineCollider(Vec(0.f, 1150.f), Vec(3500.f, 1150.f));
		CreateLineCollider(Vec(3500.f, 1150.f), Vec(4200.f, 1720.f));
		CreateLineCollider(Vec(4200.f, 1720.f), Vec(5380.f, 1720.f));
		//CreateLineCollider(Vec(5380.f, 1720.f), Vec(5380.f, 2530.f));
		CreateLineCollider(Vec(5380.f, 2530.f), Vec(10040.f, 2530.f));
		CreateLineCollider(Vec(10040.f, 2100.f), Vec(10760.f, 2100.f));
		CreateLineCollider(Vec(10760.f, 1910.f), Vec(11860.f, 1910.f));

		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 2000.f), Vec(-6000.f, -500.f));
		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 2000.f), Vec(-4600.f, -500.f)); // GhostWoman Test Wall
		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 810.f), Vec(-1340.f, 2125.f));
		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 430.f), Vec(10060.f, 2315.f));
		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 190.f), Vec(10780.f, 2005.f));
		//AddSquareCollider((UINT)COLLIDER_TYPE::WALL, Vec(40.f, 1000.f), Vec(11860.f, 1910.f));
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

