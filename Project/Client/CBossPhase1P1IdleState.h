#pragma once
#include <Engine/CState.h>

class CBossPhase1P1IdleState :
    public CState
{
private:
    float m_fAttackTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P1IdleState();
    ~CBossPhase1P1IdleState();
};

