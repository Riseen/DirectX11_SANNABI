#pragma once
#include <Engine/CState.h>

class C2ndHookedState :
    public CState
{
private:
    float m_f2ndHookedTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C2ndHookedState();
    ~C2ndHookedState();
};

