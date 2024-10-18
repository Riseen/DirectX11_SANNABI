#pragma once
#include <Engine/CScript.h>
#include "CPlayerEffectScript.h"


enum class PLAYER_STATE
{
    IDLE,
    JUMPING,
    DAMAGE,
    DASH,
    DASHENDGROUND,
    FALLING,
    ROLLING,
    RUN,
    SHOT_DOWN,
    SHOT_FRONT,
    SHOT_UP,
    SHOT_AIR_DOWN,
    SHOT_AIR_FRONT,
    SHOT_AIR_UP,
    SWING,
    SWINGJUMP,
    SWINGJUMP_ROLLING,
    ROPE_SLIDE,
    CLIMB_UP,
    CLIMB,
    SLIDE,
    HOLDING,
    POUNDING,
    DEATH,
};

class CPlayerScript :
    public CScript
{
private:
    float           m_fSpeed;
    float           m_fDashTime;
    float           m_fGodTime;
    float           m_fDeathTime;
    float           m_fAccTime;

    int             m_iHP;

    PLAYER_STATE    m_CurState;
    PLAYER_STATE    m_PrevState;

    bool            m_bCurLP;
    bool            m_bPrevLP;
    bool            m_bCanJump;
    bool            m_bCanRopeDash;
    bool            m_bRopeDash;
    bool            m_bGod;
    bool            m_bFade;

private:
    void ChangeAnimation();
    void DamageDash();
    void Dash2Idle();
    void GodTime();
    bool IsClimb();
    void Dead();

public:
    void CreateEffect(PlayerEffect_TYPE _Type);
    void SetPlayerState(PLAYER_STATE _State) {  m_CurState = _State; }
    void SetGod(bool _bGod) { m_bGod = _bGod; }
    void SetCurLP(bool _bLp) { m_bCurLP = _bLp; }
    bool GetCurLP() { return m_bCurLP; }
    bool IsGod() { return m_bGod; }
    bool IsShot();

    void SetHP(int _iHP) { m_iHP = _iHP; }

    PLAYER_STATE GetCurPlayerState() { return m_CurState; }
    PLAYER_STATE GetPrevPlayerState() { return m_PrevState; }

    void Damage(Vec3 _DamageObjPos);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

