#pragma once
#include <Engine/CState.h>

class C3rdPoundingState :
    public CState
{
private:
    CGameObject* m_QTEUI;

    int m_iQTECount;
    int m_iPrevQTECount;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    C3rdPoundingState();
    ~C3rdPoundingState();
};

