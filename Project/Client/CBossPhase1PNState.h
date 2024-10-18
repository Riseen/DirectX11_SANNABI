#pragma once
#include <Engine/CState.h>

class CBossPhase1PNState :
    public CState
{
private:
    float m_fNextPhaseTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1PNState();
    ~CBossPhase1PNState();
};

