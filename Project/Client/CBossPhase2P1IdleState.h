#pragma once
#include <Engine/CState.h>

class CBossPhase2P1IdleState :
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
    CBossPhase2P1IdleState();
    ~CBossPhase2P1IdleState();
};

