#pragma once
#include <Engine/CScript.h>

enum class TURRETLASER_STATE
{
    NOT,
    AIMMING,
    SHOT
};


class CTurretLaserScript :
    public CScript
{
private:
    Vec3 m_vDestPos;
    Vec3 m_vStartPos;

    TURRETLASER_STATE m_CurState;


public:
    void SetDestPos(Vec3 _vDestPos) { m_vDestPos = _vDestPos; }
    void SetStartPos(Vec3 _vStartPos) { m_vStartPos = _vStartPos; }
    void SetLasetState(TURRETLASER_STATE _state) { m_CurState = _state; }
    TURRETLASER_STATE GetLaserState() { return m_CurState; }

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTurretLaserScript);
public:
    CTurretLaserScript();
    ~CTurretLaserScript();
};

