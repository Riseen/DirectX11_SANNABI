#pragma once
#include <Engine/CState.h>

class CBossPhase2P1DamageState :
    public CState
{
private:
    float m_fDownTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase2P1DamageState();
    ~CBossPhase2P1DamageState();
};

