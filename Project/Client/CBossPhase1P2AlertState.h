#pragma once
#include <Engine/CState.h>

class CBossPhase1P2AlertState :
    public CState
{
private:
    int m_iCol;
    int m_iAlertCount;
    float m_fTerm;
    float m_fAccTime;

private:

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossPhase1P2AlertState();
    ~CBossPhase1P2AlertState();
};

