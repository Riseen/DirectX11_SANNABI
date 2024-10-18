#pragma once
#include <Engine/CScript.h>
#include "CSearchBarScript.h"

class CEnemyScript :
    public CScript
{
private:

public:
    virtual void SetCurEnemyState(ENEMY_STATE _State);
    virtual void Holding();
    virtual void Dead();
    virtual void Detected();

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CEnemyScript);
public:
    CEnemyScript();
    CEnemyScript(UINT _ScriptType);
    ~CEnemyScript();
};

