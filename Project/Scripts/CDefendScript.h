#pragma once
#include "CEnemyScript.h"

class CDefendScript :
    public CEnemyScript
{
private:
    CGameObject* m_Shield;
    ENEMY_STATE m_CurState;
    ENEMY_STATE m_PrevState;

    float m_fAppearTime;
    float m_fDeadTime;
    float m_fDeadAccTime;

    bool m_bCurLp;
    bool m_bPrevLp;
    bool m_bDead;

private:
    void ChangeState();
    void ChangeShieldPos();

public:
    void SetLp(bool _bLp) { m_bCurLp = _bLp; }
    bool GetCurLp() { return m_bCurLp; }
    ENEMY_STATE GetCurState() { return m_CurState; }

public:
    virtual void Holding() override;
    virtual void Dead() override;
    virtual void Detected() override;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SetCurEnemyState(ENEMY_STATE _State) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CDefendScript);
public:
    CDefendScript();
    ~CDefendScript();
};

