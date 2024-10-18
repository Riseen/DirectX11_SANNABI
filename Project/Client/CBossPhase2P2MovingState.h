#pragma once
#include <Engine/CState.h>

class CBossPhase2P2MovingState :
    public CState
{
private:
    float m_fSpeed;


    float m_fMaxDist;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase2P2MovingState();
    ~CBossPhase2P2MovingState();
};

