#pragma once
#include <Engine/CState.h>

class CBossPhase2P6DownState :
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
    CBossPhase2P6DownState();
    ~CBossPhase2P6DownState();
};

