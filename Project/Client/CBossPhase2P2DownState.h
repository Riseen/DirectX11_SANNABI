#pragma once
#include <Engine/CState.h>

class CBossPhase2P2DownState :
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
    CBossPhase2P2DownState();
    ~CBossPhase2P2DownState();
};

