#pragma once
#include <Engine/CState.h>

class CTurretAlertState :
    public CState
{
private:
    float m_fAlertTime;
    float m_fCooldownTime;
    float m_fAccTime;

    ENEMY_STATE m_prevState;

public:
    void SetPrevState(ENEMY_STATE _state) { m_prevState = _state; }

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CTurretAlertState();
    ~CTurretAlertState();
};

