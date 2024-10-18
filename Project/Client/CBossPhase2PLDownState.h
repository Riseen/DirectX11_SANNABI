#pragma once
#include <Engine/CState.h>

class CBossPhase2PLDownState :
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
    CBossPhase2PLDownState();
    ~CBossPhase2PLDownState();
};

