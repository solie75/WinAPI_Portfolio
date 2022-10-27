#include "pch.h"

#include "CResourceMgr.h"
#include "CPathMgr.h"

#include "CTexture.h"
#include "CResource.h"

CResourceMgr::CResourceMgr()
{

}

CResourceMgr::~CResourceMgr()
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }
}

CTexture* CResourceMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return iter->second;
}

CTexture* CResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CResource* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
    {
        return (CTexture*)pTexture;
    }

    // make the Texture's path using PathMgr
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // create Texture and Loading
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    // save in map
    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));

    return (CTexture*)pTexture;
}
