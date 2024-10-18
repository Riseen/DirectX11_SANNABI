#pragma once
#include <Engine/CState.h>

class C3rdBeforePoundingState :
    public CState
{
private:
    float m_fPoundingTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C3rdBeforePoundingState();
    ~C3rdBeforePoundingState();
};

