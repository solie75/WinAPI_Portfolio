#pragma once

class CObject;

bool IsValid(CObject*& _pTarget);

void Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer);

void Saturate(float& _float);

void ChangeLevel(LEVEL_TYPE _eNextLevel);

void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);
