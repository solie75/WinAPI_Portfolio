#include "pch.h"
#include "func.h"

#include "CObject.h"
#include "CEventMgr.h"

bool IsValid(CObject*& _pTarget)
{
	if (nullptr == _pTarget || _pTarget->IsDead())
	{
		_pTarget = nullptr;
		return false;
	}

	return true;
}


void Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer)
{
	_pNewObj->SetPos(_vPos);
	_pNewObj->SetObjectType((UINT)_eLayer);

	tEvent event = {};
	event.eType = EVENT_TYPE::CREATE_OBJECT;
	event.wPARAM = (DWORD_PTR)_pNewObj;
	event.lPARAM = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(event);
}

void Saturate(float& _float)
{
	if (1.f < _float)
	{
		_float = 1.f;
	}
	if (_float < 0.f)
	{
		_float = 0.f;
	}
}

void ChangeLevel(LEVEL_TYPE _eNextLevel)
{
	tEvent _event = {};
	_event.eType = EVENT_TYPE::LEVEL_CHANGE;
	_event.wPARAM = (DWORD_PTR)_eNextLevel;
	CEventMgr::GetInst()->AddEvent(_event);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);
	_str = szBuff;
}
