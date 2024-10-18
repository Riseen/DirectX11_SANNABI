#pragma once
#include <Engine/CState.h>

class CBossPhase2P6ExcHoldedState :
    public CState
{
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase2P6ExcHoldedState();
    ~CBossPhase2P6ExcHoldedState();
};

