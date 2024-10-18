#pragma once
#include <Engine/CScript.h>

enum class AFTERIMAGE_TYPE
{
    NOT,
    SWING_DASH,
    SHOT_DOWN,
    SHOT_FRONT,
    SHOT_UP,
    SHOT_AIR_DOWN,
    SHOT_AIR_FRONT,
    SHOT_AIR_UP,
};


class CAfterImageManagerScript :
    public CScript
{
private:
    AFTERIMAGE_TYPE m_CurType;
    AFTERIMAGE_TYPE m_PrevType;

    float m_fAccTime;
    float m_fTerm;

    int   m_iMaxSwingDashCount;

private:
    void CreateAfterImage();
    void CreateSwingDashImage();

public:
    void SetAfterImage(AFTERIMAGE_TYPE _type) { m_CurType = _type; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CAfterImageManagerScript);
public:
    CAfterImageManagerScript();
    ~CAfterImageManagerScript();
};

