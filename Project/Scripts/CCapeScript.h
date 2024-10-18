#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"

class CCapeScript :
    public CScript
{
public:
    void ChangeState(PLAYER_STATE _curPlayerState, PLAYER_STATE _prevPlayerState, bool _bLp, bool _bPrevLp);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CCapeScript);
public:
    CCapeScript();
    ~CCapeScript();
};

