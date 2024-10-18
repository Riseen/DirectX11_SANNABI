#pragma once
#include <Engine/CState.h>

class CBeforePoundingState :
    public CState
{
private:
    float m_fBeforeTime;
    float m_fAccTime;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBeforePoundingState();
    ~CBeforePoundingState();
};

