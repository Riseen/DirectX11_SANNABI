#pragma once
#include "CEnemyScript.h"




class CBossScript :
    public CEnemyScript
{
private:
    CGameObject* m_BossAttackPoint;
    CGameObject* m_BossCollsion;

    BOSS_STATE m_CurState;
    BOSS_STATE m_PrevState;

    int m_iBossHP;
    int m_iPatternCount;

    float m_fAccTime;
    float m_fChangeTime;

private:
    void CreateAttackCollsion();
    void DeleteAttackCollsion();
    void DeleteBossCollsion();
   

public:
    void CreateBossCollsion();
    void Holding();
    void Damage();
    void SetScaleForState(BOSS_STATE _State);

public:
    BOSS_STATE GetCurBossState() { return m_CurState; }
    void SetBossState(BOSS_STATE _CurState) { m_CurState = _CurState; }
    void ChangeState();
    void SetPatternCount(int _iCount) { m_iPatternCount = _iCount; }

    void SetHP(int _iHp) { m_iBossHP = _iHp; }
    int GetHP() { return m_iBossHP; }
    int GetCurPatternCount() { return m_iPatternCount; }
 
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Detected() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBossScript);
public:
    CBossScript();
    ~CBossScript();
};

