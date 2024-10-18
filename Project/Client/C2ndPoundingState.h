#pragma once
#include <Engine/CState.h>

class C2ndPoundingState :
    public CState
{
private:
    CGameObject* m_QTEUI;

    float m_fPoundingTime;
    float m_fAccTime;

    int m_iQTECount;
    int m_iPrevQTECount;
public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C2ndPoundingState();
    ~C2ndPoundingState();
};

