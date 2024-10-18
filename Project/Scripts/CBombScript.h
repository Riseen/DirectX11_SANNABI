#pragma once
#include <Engine/CScript.h>

class CBombScript :
    public CScript
{
private:
    DefenderBOMB_STATE m_CurState;
    DefenderBOMB_STATE m_PrevState;
    float m_fAppearTime;
    float m_fAccTime;

    int m_iDir;

    bool m_bDead;

private:
    void ChangeState();

public:
    void SetBombState(DefenderBOMB_STATE _State) { m_CurState = _State; }
    DefenderBOMB_STATE GetBombState() { return m_CurState; }

    void SetDead(bool _bDead) { m_bDead = _bDead; }
    bool IsDead() { return m_bDead; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBombScript);
public:
    CBombScript();
    ~CBombScript();
};

