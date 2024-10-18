#pragma once
#include <Engine/CState.h>

class CBombMoveState :
    public CState
{
private:
    float m_fDist;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBombMoveState();
    ~CBombMoveState();
};

