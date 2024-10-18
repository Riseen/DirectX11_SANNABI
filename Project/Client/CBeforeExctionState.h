#pragma once
#include <Engine/CState.h>

class CBeforeExctionState :
    public CState
{
private:
    CGameObject* m_QTEUI;

    float m_fQTEValue;
    float m_fPoundingTime;
    float m_fAccTime;

    

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBeforeExctionState();
    ~CBeforeExctionState();
};

