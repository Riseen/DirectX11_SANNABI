#pragma once
#include <Engine/CScript.h>

class CGrabTailScript :
    public CScript
{
private:
    float m_fAccTime;
    float m_fPlayTime;


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CGrabTailScript);
public:
    CGrabTailScript();
    ~CGrabTailScript();
};

