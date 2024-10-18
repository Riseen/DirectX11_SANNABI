#pragma once
#include <Engine/CScript.h>

class CMainSmokeScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainSmokeScript);
public:
    CMainSmokeScript();
    ~CMainSmokeScript();
};

