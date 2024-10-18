#pragma once
#include <Engine/CScript.h>
#include "CTurretBodyScript.h"


enum class ENEMY_TYPE
{
    DEFENDER,
    TURRET,
};

struct SpawnEnemy
{
    ENEMY_TYPE m_Type;
    SPAWN_DIR  m_Dir;
    Vec3       m_vSpawnPos;
};

class CEventColScript :
    public CScript
{
private:
    vector<SpawnEnemy> m_SpawnEnemy;

    bool m_bSpawn;
    

private:
    void Spawn();


public:
    void SetSpawnInfo(Vec3 _vSpawnPos, SPAWN_DIR _Dir, ENEMY_TYPE _type);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CEventColScript);
public:
    CEventColScript();
    ~CEventColScript();
};

