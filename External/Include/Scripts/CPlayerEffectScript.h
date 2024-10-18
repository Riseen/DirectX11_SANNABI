#pragma once
#include <Engine/CScript.h>

enum class PlayerEffect_TYPE
{
    NOT,
    JUMP,
    LANDING,
    WALLJUMP,
    WALLSLIDING,
    ATTACKDONUT,
    GRABSHOTGAS,
    GRABSHOTFIRE,
    DAMAGETILE,
    ENEMYATTACK,
};

class CPlayerEffectScript :
    public CScript
{
private:
    PlayerEffect_TYPE m_CurEffectType;
    PlayerEffect_TYPE m_PrevEffectType;

    float m_fAccTime;
    float m_fDeleteTime;

private:
    void PlayEffect();

public:
    void SetEffectType(PlayerEffect_TYPE _Type) { m_CurEffectType = _Type; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CPlayerEffectScript);
public:
    CPlayerEffectScript();
    ~CPlayerEffectScript();
};

