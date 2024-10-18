#pragma once
#include "CEnemyScript.h"

enum class SPAWN_DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class CTurretBodyScript:
    public CEnemyScript
{
private:
    CGameObject* m_pGun;
    CGameObject* m_pLaser;

    ENEMY_STATE m_CurState;
    ENEMY_STATE m_PrevState;
    SPAWN_DIR   m_CurSpawnDir;

    float m_fDeadTime;
    float m_fDeadAccTime;
    float m_fPopUpTime;
    float m_fAccTime;

private:
    void ChangeState();
    bool IsSpecialState();

public:
    void SetState(ENEMY_STATE _State) { m_CurState = _State; }
    void SetSpawnDir(SPAWN_DIR _dir);

    ENEMY_STATE GetCurState() { return m_CurState; }
    SPAWN_DIR GetSpawnDir() { return m_CurSpawnDir; }

public:
    virtual void SetCurEnemyState(ENEMY_STATE _State) override;
    virtual void Holding() override;
    virtual void Dead() override;
    virtual void Detected() override;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTurretBodyScript);
public:
    CTurretBodyScript();
    ~CTurretBodyScript();
};

