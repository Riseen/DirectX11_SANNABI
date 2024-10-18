#pragma once
#include <Engine/CScript.h>

enum class BUTTON_STATE
{
    NOT,
    SELECTED,
};

class CButtonScript :
    public CScript
{
private:
    BUTTON_STATE m_CurState;

    float m_fAccTime;
    float m_fFadeTime;

    bool  m_bLevelChange;

private:


public:


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CButtonScript);
public:
    CButtonScript();
    ~CButtonScript();
};

