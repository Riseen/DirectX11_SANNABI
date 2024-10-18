#pragma once
#include <Engine/CState.h>

class CBossPhase1P6MovingState :
    public CState
{
private:
    float m_fMovingTime;
    float m_fAccTime;

    float m_fSpeed;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P6MovingState();
    ~CBossPhase1P6MovingState();
};

