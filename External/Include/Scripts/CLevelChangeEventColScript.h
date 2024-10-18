#pragma once
#include <Engine/CScript.h>



class CLevelChangeEventColScript :
    public CScript
{
private:
    float m_fChangeTime;
    float m_fAccTime;

    bool m_bChangeStart;

public:

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CLevelChangeEventColScript);
public:
    CLevelChangeEventColScript();
    ~CLevelChangeEventColScript();
};

