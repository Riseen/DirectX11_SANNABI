#pragma once
#include <Engine/CState.h>

class CExctionState :
    public CState
{
private:
    float m_fPoundingTime;
    float m_fStartTime;
    float m_fAccTime;

    bool m_bExction;
    bool m_bExctionStart;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CExctionState();
    ~CExctionState();
};

