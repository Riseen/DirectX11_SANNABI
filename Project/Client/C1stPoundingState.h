#pragma once
#include <Engine/CState.h>

class C1stPoundingState :
    public CState
{
private:
    CGameObject* m_QTEUI;

    float m_fPoundingTime;
    float m_fAccTime;

    int m_iQTECount;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C1stPoundingState();
    ~C1stPoundingState();
};

