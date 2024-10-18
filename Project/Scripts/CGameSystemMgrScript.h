#pragma once
#include <Engine/CScript.h>
#include "CEventColScript.h"


class CLevel;

typedef CLevel* (*LEVEL_LOAD)(const wstring&);

class CGameSystemMgrScript :
    public CScript
{
private:
    CGameObject* m_pEventCol[5];

public:
    static LEVEL_LOAD levelLoad;

public:
    CLevel* LoadLevel(const wstring& _strFilePath);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CGameSystemMgrScript);
public:
    CGameSystemMgrScript();
    ~CGameSystemMgrScript();
};

