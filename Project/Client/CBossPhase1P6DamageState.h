#pragma once
#include <Engine/CState.h>

class CBossPhase1P6DamageState :
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
    CBossPhase1P6DamageState();
    ~CBossPhase1P6DamageState();
};

