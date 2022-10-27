#pragma once

class CTexture;

class CResourceMgr
{
	SINGLE(CResourceMgr)

private:
	map<wstring, CTexture*>m_mapTex;

public:
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
};
