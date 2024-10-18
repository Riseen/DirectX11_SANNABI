#pragma once
#include <Engine/CScript.h>



class CHPUIScript :
    public CScript
{
private:
    int m_iCurHp;
    int m_iPrevHp;

    float m_fRecoveryTime;
    float m_fAccTime;

    float m_fIdleTime;
    float m_fidleAccTime;


    bool m_bIdleTurn;
    bool m_bDamage;

private:
    void ChangeHPState();
    void RotateReset();
    void Recovery();
    void TurnIdleMini();

public:
    void SetCurHP(int _iHP) { m_iCurHp = _iHP; }

    int GetCurHP() { return m_iCurHp; }
    int GetPrevHP() { return m_iPrevHp; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CHPUIScript);
public:
    CHPUIScript();
    ~CHPUIScript();

};

