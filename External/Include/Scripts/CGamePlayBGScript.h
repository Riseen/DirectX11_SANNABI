#pragma once
#include <Engine/CScript.h>

enum class PLAYBG_TYPE
{
    NOT,
    BOSSROOM_SKY,
    BOSSROOMLOOP_SKY,
    C1_SKY,
    C1_FBG4,
    C1_FBG1,
};

class CGamePlayBGScript :
    public CScript
{
private:
    PLAYBG_TYPE m_CurPLAYBGType;

private:
    void SetTexture();

public:


public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CGamePlayBGScript);
public:
    CGamePlayBGScript();
    ~CGamePlayBGScript();
};

