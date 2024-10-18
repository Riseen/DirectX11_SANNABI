#pragma once
#include <Engine/CScript.h>

class CMenuUIScript :
    public CScript
{
private:
    float m_fAlpha;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMenuUIScript);
public:
    CMenuUIScript();
    ~CMenuUIScript();
};

