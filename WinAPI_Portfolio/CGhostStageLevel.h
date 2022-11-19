#pragma once
#include "CLevel.h"

class CTexture;

class CGhostStageLevel :
    public CLevel
{
public:
    bool OnStage;
public:
    virtual void LevelInit() override;
    virtual void LevelTick() override;

    virtual void LevelEnter() override;
    virtual void LevelExit() override;

public:
    CGhostStageLevel();
    ~CGhostStageLevel();
};

