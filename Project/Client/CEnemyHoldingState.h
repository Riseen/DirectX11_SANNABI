#pragma once
#include <Engine/CState.h>

class CEnemyHoldingState :
    public CState
{
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CEnemyHoldingState();
    ~CEnemyHoldingState();
};

