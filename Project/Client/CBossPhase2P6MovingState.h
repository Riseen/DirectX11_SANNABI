#pragma once
#include <Engine/CState.h>

class CBossPhase2P6MovingState :
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
    CBossPhase2P6MovingState();
    ~CBossPhase2P6MovingState();
};

