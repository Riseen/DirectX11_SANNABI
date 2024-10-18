#pragma once
#include <Engine/CState.h>

class CAfterExectionState :
    public CState
{
private:
    float m_fAccTime;
    float m_fFadeOutTime;

    bool  m_bFadeOut;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CAfterExectionState();
    ~CAfterExectionState();
};

