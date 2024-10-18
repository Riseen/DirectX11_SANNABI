#pragma once
#include <Engine/CState.h>

class CTurretAimingState :
    public CState
{
private:
    float m_fAimmingTime;
    float m_fCurAccTime;

    CGameObject* m_pRay;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTurretAimingState();
    ~CTurretAimingState();
};

