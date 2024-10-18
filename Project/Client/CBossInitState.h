#pragma once
#include <Engine/CState.h>

class CBossInitState :
    public CState
{
private:
    float m_InitTime;
    float m_fAccTime;
    float m_fRunTime;

    bool  m_bInit;
    bool  m_bRun;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossInitState();
    ~CBossInitState();
};

