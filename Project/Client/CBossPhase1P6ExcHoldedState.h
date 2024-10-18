#pragma once
#include <Engine/CState.h>

class CBossPhase1P6ExcHoldedState :
    public CState
{
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P6ExcHoldedState();
    ~CBossPhase1P6ExcHoldedState();
};

