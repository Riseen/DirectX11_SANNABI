#pragma once
#include <Engine/CState.h>

class CBossPhase1PLDownState :
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
    CBossPhase1PLDownState();
    ~CBossPhase1PLDownState();
};

