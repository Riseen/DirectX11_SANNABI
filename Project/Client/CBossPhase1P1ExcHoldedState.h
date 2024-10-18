#pragma once
#include <Engine/CState.h>

class CBossPhase1P1ExcHoldedState :
    public CState
{
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P1ExcHoldedState();
    ~CBossPhase1P1ExcHoldedState();
};

