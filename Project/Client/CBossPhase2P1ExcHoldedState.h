#pragma once
#include <Engine/CState.h>

class CBossPhase2P1ExcHoldedState :
    public CState
{
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase2P1ExcHoldedState();
    ~CBossPhase2P1ExcHoldedState();
};

