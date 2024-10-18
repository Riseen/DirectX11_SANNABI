#pragma once
#include "CEnemyScript.h"

class CTurretGunScript :
    public CEnemyScript
{
private:
    float m_fDegree;
    float m_fDist;

    Vec3  m_vShotPos;
    Vec3  m_vCurPlayerDir;

    bool  m_bOutLineOn;
public:
    void ChangeState(ENEMY_STATE _CurState, ENEMY_STATE _PrevState);
    void ChangeFSM(ENEMY_STATE _CurState);
    Vec3 GetShotPos() { return m_vShotPos; }
    Vec3 GetPlayerDir() { return m_vCurPlayerDir; }
    float GetDegree() { return m_fDegree; }

    void SetOutLine(bool _bOutLineOnOff) { m_bOutLineOn = _bOutLineOnOff;  }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Detected() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTurretGunScript);
public:
    CTurretGunScript();
    ~CTurretGunScript();
};

