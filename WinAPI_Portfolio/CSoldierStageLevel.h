#pragma once
#include "CLevel.h"
class CSoldierStageLevel :
    public CLevel
{
public:
    virtual void LevelInit() override;
    virtual void LevelTick() override;

    virtual void LevelEnter() override;
    virtual void LevelExit() override;
};

