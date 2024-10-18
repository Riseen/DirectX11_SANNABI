#pragma once
#include <Engine/CScript.h>

class CAimmingRayScript :
    public CScript
{
private:
    float m_fSpeed;
    float m_fMaxDist;

    bool  m_bActive;

    Vec3  m_vDir;
    Vec3  m_vStartPos;
    Vec3  m_vDestPos;

public:
    Vec3  GetDir() {return m_vDir;}
    Vec3  GetStart() {return m_vStartPos;}
    Vec3  GetDestPos() {return m_vDestPos;}

    void SetDir(Vec3 _vDir) { m_vDir = _vDir; }
    void SetStartPos(Vec3 _vStartPos) { m_vStartPos = _vStartPos; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CAimmingRayScript);
public:
    CAimmingRayScript();
    ~CAimmingRayScript();
};

