#pragma once
#include <Engine/CState.h>

class CBossPhase1PLEndState :
    public CState
{
private:
    float m_fEndTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1PLEndState();
    ~CBossPhase1PLEndState();
};

