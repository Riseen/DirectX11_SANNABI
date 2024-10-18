#pragma once
#include <Engine/CScript.h>

class CBulletScript :
    public CScript
{
private:
    float m_fSpeed;
    Vec3  m_vDir;

    float m_fDeadTime;
    float m_fAccTime;

public:
    void SetDir(Vec3 _Dir) { m_vDir = _Dir; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBulletScript);
public:
    CBulletScript();
    ~CBulletScript();
};

