#pragma once
#include <Engine/CScript.h>

class CMainFlashScript :
    public CScript
{
public:
    bool IsFinish();

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainFlashScript);
public:
    CMainFlashScript();
    ~CMainFlashScript();
};

