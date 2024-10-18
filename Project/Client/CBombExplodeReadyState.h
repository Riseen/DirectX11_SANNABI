#pragma once
#include <Engine/CState.h>

class CBombExplodeReadyState :
    public CState
{
private:
    CGameObject* m_Col;

    float m_fExplodeTime;
    float m_fAccTime;
    float m_fSoundTime;
    float m_fSoundAccTime;


public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CBombExplodeReadyState();
    ~CBombExplodeReadyState();
};

