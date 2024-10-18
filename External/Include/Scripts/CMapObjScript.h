#pragma once
#include <Engine/CScript.h>

enum class MAPOBJ_TYPE
{
    BACKBUILDING1,
    BACKBUILDING2,
    BACKBUILDING3,
    BACKBUILDING4,
    BACKBUILDING6,
    BARICATE1,
    BARICATE2,
    BASKET,
    CYCLE,
    BOARD,
    BUSSTATION1,
    BUSSTATION2,
    CAR1,
    CAR2,
    DONOTENTER,
    STUFF,
    TRUCK,
    POLE,
    FRONT1,
    FRONT2,
    FRONT3,
    FRONT4,
    FRONT5,
    FRONT6,
    FRONT7,
    FRONT8,
    FRONT9,
    FRONT10,
    BOSSROOM_FRONT,
    BOSSROOM_MID1,
    BOSSROOM_MID2,
    BOSSROOM_MID3,
    BOSSROOM_MID4,
    BOSSROOM_MID5,
    BOSSROOM_MID6,
    BOSSROOM_MID7,
    BOSSROOM_MID8,
    BOSSROOM_MID9,
    BOSSROOM_WALL,
    BOSSROOM_WALL_LEFT,
    BOSSROOM_WALL_RIGHT,
    BOSSROOM_WALL_WIDE,
    BOSSROOM_WALL_WIDE_LEFT,
    BOSSROOM_WALL_WIDE_RIGHT,
    BOSSROOM_LOOP_MID1,
    BOSSROOM_LOOP_MID2,
    BOSSROOM_LOOP_MID3,
    BOSSROOM_LOOP_MID4,
};

class CMapObjScript :
    public CScript
{
private:
    MAPOBJ_TYPE m_CurMapObjType;

private:
    void SetTexture();

public:
    void SetMapObjType(MAPOBJ_TYPE _type) { m_CurMapObjType = _type; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMapObjScript);
public:
    CMapObjScript();
    ~CMapObjScript();
};

