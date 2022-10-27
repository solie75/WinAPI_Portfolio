#pragma once
#include "CEntity.h"

class CResource :
    public CEntity
{
private:
    wstring m_strKey;
    wstring m_strRelativePath;

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strRelativepath) { m_strRelativePath = _strRelativepath; }

protected:
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CLONE_DEACTIVATE(CResource);

public:
    CResource();
    virtual ~CResource();

    friend class CResourceMgr;
};
