#pragma once
#include "CEntity.h"

class CObject;

class CLevel :
    public CEntity
{
private:
    vector<CObject*> m_arrLayer[(UINT)LAYER::END];

public:
    virtual void LevelInit() = 0;
    virtual void LevelTick();
    virtual void Final_Tick();
    virtual void LevelRender(HDC _dc);

    virtual void LevelEnter() = 0; // ������ ������ �� ȣ�� ��
    virtual void LevelExit() = 0; // ������ ��� �� ȣ�� ��



public:
    void AddObject(CObject* _pObj, LAYER _layer) 
    { 
        m_arrLayer[(UINT)_layer].push_back(_pObj);
    }

    const vector<CObject*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer];}

    void DeleteAllObject();

    void DeleteObject(LAYER _eLayer); // ������ �귯�� ���� ������Ʈ ����� ������ �Լ��ϰ� �̸��� ��ģ��. �������� �̸��� �ٲ���

public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    virtual ~CLevel();
};