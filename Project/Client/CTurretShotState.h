#pragma once
#include <Engine/CState.h>

class CTurretShotState :
    public CState
{
private:
    float m_fTerm;
    float m_fCurAccTime;

    int   m_iBulletCount;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTurretShotState();
    ~CTurretShotState();
};

