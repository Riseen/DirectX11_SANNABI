#pragma once
#include <Engine/CScript.h>

class CBombCargoScript :
    public CScript
{
private:
    Vec3 m_vStartPos;
    Vec3 m_vEndPos;

    float m_fCurDist;
    float m_fMaxDist;
    float m_fSpeed;
    float m_fAccTime;
    float m_fStopTime;

private:
    void Move();


public:
    void SetStartPos(Vec3 _vPos) { m_vStartPos = _vPos; }
    void SetEndPos(Vec3 _vPos) { m_vEndPos = _vPos; }

    Vec3 GetStartPos() { return m_vStartPos; }
    Vec3 GetEndPos() { return m_vEndPos; }
      
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBombCargoScript);
public:
    CBombCargoScript();
    ~CBombCargoScript();

};

