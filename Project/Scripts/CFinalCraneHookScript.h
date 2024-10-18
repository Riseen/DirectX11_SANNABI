#pragma once
#include <Engine/CScript.h>

class CFinalCraneHookScript :
    public CScript
{
private:
    Vec3  m_StartPos;
    float m_fMaxDist;
    float m_fCurDist;
    float m_fCurAngle;
    float m_fCurMove;

private:
    void HookMoveInit();

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CFinalCraneHookScript);
public:
    CFinalCraneHookScript();
    ~CFinalCraneHookScript();

};

