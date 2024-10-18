#pragma once
#include <Engine/CState.h>

class C3rdHookedState :
    public CState
{
private:
    float m_f3rdHookedTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C3rdHookedState();
    ~C3rdHookedState();
};

