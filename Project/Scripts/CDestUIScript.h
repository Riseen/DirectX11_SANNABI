#pragma once
#include <Engine/CScript.h>

class CDestUIScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CDestUIScript);
public:
    CDestUIScript();
    ~CDestUIScript();
};

