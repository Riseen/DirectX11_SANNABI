#pragma once
#include <Engine/CState.h>

class C1stHookedState :
    public CState
{
private:
    float m_f1stHookedTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C1stHookedState();
    ~C1stHookedState();
};

