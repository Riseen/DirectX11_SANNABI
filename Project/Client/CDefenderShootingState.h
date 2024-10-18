#pragma once
#include <Engine/CState.h>

class CDefenderShootingState :
    public CState
{
private:
    CGameObject* m_Bomb;

    float m_fAttackTime;
    float m_fAccTime;


public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CDefenderShootingState();
    ~CDefenderShootingState();
};

