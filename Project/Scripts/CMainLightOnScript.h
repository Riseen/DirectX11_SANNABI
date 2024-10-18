#pragma once
#include <Engine/CScript.h>

class CMainLightOnScript :
    public CScript
{
private:
    float m_fLightSpeed;
    float m_fLight_B_Speed;
    Vec3  m_vStartColor;

public:
    bool IsFinish();

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainLightOnScript);
public:
    CMainLightOnScript();
    ~CMainLightOnScript();
};

