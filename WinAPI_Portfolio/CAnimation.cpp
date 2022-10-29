#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CPathMgr.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	, m_vecFrame{}
	, m_pAtlas(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::AnimationInit(const wstring& _strName, CTexture* _pAtlas, Vec _vLeftTop, Vec _vSize, int _iMaxFrameCount, float _fDuration)
{
	SetName(_strName); // Animation's name
	m_pAtlas = _pAtlas; // Animation's Atlas Image

	for (int i = 0; i < _iMaxFrameCount; ++i)
	{

		tAnimFrame frm = {};

		frm.vLeftTop = Vec(_vLeftTop.x + (float)(i%10) * _vSize.x, _vLeftTop.y + (float)(i/10) * _vSize.y);
		frm.vSize = _vSize;
		frm.fDuration = _fDuration;

		m_vecFrame.push_back(frm);
	}
}

void CAnimation::AnimationTick()
{
	if (m_bFinish)
	{
		return;
	}

	m_fAccTime += DT;

	if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime)
	{
		++m_iCurFrame;
		m_fAccTime = 0.f;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = (int)m_vecFrame.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::AnimationRender(HDC _dc)
{
	CObject* pOwnerObject = m_pAnimator->GetOwner();
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(pOwnerObject->GetPos());

	tAnimFrame frm = m_vecFrame[m_iCurFrame];

	TransparentBlt(
		_dc,
		int(vPos.x - frm.vSize.x / 2.f),
		int(vPos.y - frm.vSize.y / 2.f),
		int(frm.vSize.x),
		int(frm.vSize.y),
		m_pAtlas->GetDC(),
		int(frm.vLeftTop.x),
		int(frm.vLeftTop.y),
		int(frm.vSize.x),
		int(frm.vSize.y),
		RGB(255, 255, 255)
	);
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save Fail, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	// Save Animation Name
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// Save Atlas Texture keyValue
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	// Save Frame Info
	wchar_t szNum[200] = {};

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iFrameCount = m_vecFrame.size();
	_itow_s((int)iFrameCount, szNum, 200, 10);

	fwprintf(pFile, szNum);
	fwprintf(pFile, L"\n\n");

	for (size_t i = 0; i < iFrameCount; ++i)
	{
		fwprintf(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vLeftTop.x, m_vecFrame[i].vLeftTop.y);

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vSize.x, m_vecFrame[i].vSize.y);

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vOffset.x, m_vecFrame[i].vOffset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrame[i].fDuration);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Load 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 불러오기 실패", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	wstring strAtlasKey;
	wstring strAtlasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasRelativePath = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount);

			for (size_t i = 0; i < iFrameCount; ++i)
			{
				tAnimFrame frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
					}

					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						break;
					}
				}

				m_vecFrame.push_back(frm);
			}

			break;
		}
	}

	m_pAtlas = CResourceMgr::GetInst()->LoadTexture(strAtlasKey, strAtlasRelativePath);

	fclose(pFile);

}



