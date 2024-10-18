#pragma once
#include <Engine/CState.h>

class CBossPhase2P6DamageState :
    public CState
{
private:
    float m_fDamageTime;
    float m_fAccTime;


public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase2P6DamageState();
    ~CBossPhase2P6DamageState();
};

