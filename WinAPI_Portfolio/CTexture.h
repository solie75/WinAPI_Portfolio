#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HBITMAP m_hBit;
    HDC m_hDC;

    BITMAP m_tBitmapInfo;

public:
    UINT Width() { return m_tBitmapInfo.bmWidth; }
    UINT Height() { return m_tBitmapInfo.bmHeight; }
    HDC GetDC() { return m_hDC; }

    void ReSize(UINT _iWidth, UINT _iHeight);

private:
    virtual int Load(const wstring& _strFilePath) override;
    void Create(UINT _iWidth, UINT _iHeight);


public:
    CTexture();
    ~CTexture();

    friend class CResourceMgr;
};

