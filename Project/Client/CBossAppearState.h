#pragma once
#include <Engine/CState.h>

class CBossAppearState :
    public CState
{
private:
    float m_fSpeed;
    int   m_iDir;

    float m_fAccTime;
    float m_fFirstTime;
    float m_fSecondTime;
    float m_fThirdTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBossAppearState();
    ~CBossAppearState();
};

