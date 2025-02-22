#pragma once
#include <Engine/CScript.h>

class CBossWaveScript :
    public CScript
{
private:
    float m_fAccTime;
    float m_fAliveTime;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBossWaveScript);
public:
    CBossWaveScript();
    ~CBossWaveScript();
};

