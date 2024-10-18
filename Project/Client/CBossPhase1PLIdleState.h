#pragma once
#include <Engine/CState.h>

class CBossPhase1PLIdleState :
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
    CBossPhase1PLIdleState();
    ~CBossPhase1PLIdleState();
};

