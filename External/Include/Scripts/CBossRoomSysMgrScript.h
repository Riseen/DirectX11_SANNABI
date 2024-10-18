#pragma once
#include <Engine/CScript.h>

enum class SYSMGR_TYPE
{
    NOT,
    BOSSSPAWNCAMERAMOVE,
    BOSSSPAWN,
    LEFTCARGOSPAWN,
    RIGHTCARGOSPAWN,
    SPAWNDOUBLE,
    BOMBCARGOSPAWN,
    FINALCRANESPAWN
};

class CBossRoomSysMgrScript :
    public CScript
{
private:
    SYSMGR_TYPE m_CurType;
    SYSMGR_TYPE m_PrevType;

    float m_fBossSpawnTime;
    float m_fBossSpawnCameraMoveTime;
    float m_fAccTime;

    int m_iPrevBossHP;

    bool m_bBossSpawn;
    bool m_bBossCamera;
    bool m_bBGMCHANGE;

private:
    void SysMgr();

public:
    void SetSysType(SYSMGR_TYPE _type) { m_CurType = _type; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBossRoomSysMgrScript);
public:
    CBossRoomSysMgrScript();
    ~CBossRoomSysMgrScript();
};

