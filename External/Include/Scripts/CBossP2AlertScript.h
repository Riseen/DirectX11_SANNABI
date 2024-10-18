#pragma once
#include <Engine/CScript.h>

class CBossP2AlertScript :
    public CScript
{
private:
    float m_fAccTime;
    float m_fAliveTime;

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBossP2AlertScript);
public:
    CBossP2AlertScript();
    ~CBossP2AlertScript();
};

