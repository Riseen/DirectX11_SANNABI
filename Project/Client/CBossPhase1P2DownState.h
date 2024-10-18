#pragma once
#include <Engine/CState.h>

class CBossPhase1P2DownState :
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
    CBossPhase1P2DownState();
    ~CBossPhase1P2DownState();
};

