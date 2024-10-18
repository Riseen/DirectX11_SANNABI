#pragma once
#include <Engine/CState.h>

class CBossPhase1P6GroggyState :
    public CState
{
private:
    float m_fGroggyTime;
    float m_fAccTime;


public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P6GroggyState();
    ~CBossPhase1P6GroggyState();
};

