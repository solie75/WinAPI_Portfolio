#include "pch.h"
#include "CDialog.h"
#include "CEngine.h"
#include "CResourceMgr.h"
#include "CTexture.h"
#include "CCameraMgr.h"

CDialog::CDialog()
	: m_pTexture(nullptr)
	, CurAnim(0)
{
}

CDialog::CDialog(wstring _pstring)
	: m_pTexture(nullptr)
	, CurAnim(0)
{
	SetName(_pstring);
	
}

CDialog::~CDialog()
{
}


void CDialog::ObjectTick()
{
	CObject::ObjectTick();
}

void CDialog::ObjectRender(HDC _dc, wstring _pstring)
{
	Vec vResolution = CEngine::GetInst()->GetResolution();
	m_pTexture = CResourceMgr::GetInst()->FindTexture(_pstring);

	if (CurAnim > 0)
	{
		TransparentBlt(
			_dc,
			int(vResolution.x/2 - 1080/2),
			int(vResolution.y/2 - 55),
			(int)1080, // 출력 너비
			(int)450, // 출력 높이
			m_pTexture->GetDC(),
			int((CurAnim-1) * 1080), // 원본의 시작 지점 좌표
			int(0),
			(int)1080, // 원본 너비
			(int)450, // 원본 높이
			RGB(253, 253, 254)
		);
	}
	CObject::ObjectRender(_dc, _pstring);
}
