#pragma once
#include <Engine/CScript.h>

enum class BackGroundSTATE
{
    START,
    LIGHTON,
    LIGHTOFF
};

class CBackgroundScript :
    public CScript
{
private:
    Ptr<CTexture> m_BlueLEDTex;
    Ptr<CTexture> m_LightOffTex;
    Ptr<CTexture> m_LightOnTex;

    float m_fAccTime;

    BackGroundSTATE m_State;
    BackGroundSTATE m_prevState;

public:
    bool IsMainReady();

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBackgroundScript);
public:
    CBackgroundScript();
    ~CBackgroundScript();
};

