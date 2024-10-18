#pragma once

#include <Engine/CScript.h>

enum class GRAB_DIR
{
    RIGHT,
    LEFT,
    DOWN,
    UP
};

enum class GRAB_STATE
{
    NOT,
    FLYING,
    GRABING,
    GRABRETURN
};

class CGrabScript :
    public CScript
{
private:
    float m_fSpeed;
    float m_fCurDist;

    bool  m_bLp;
    bool  m_bNone;

    Vec3  m_vStartPos;
    Vec3  m_vDir;
    Vec3  m_vArriObjDir;
    Vec3  m_vArriPos;

    GRAB_DIR m_GrabDir;
    GRAB_STATE m_CurState;
    GRAB_STATE m_PrevState;
private:
    void ChangeState();


public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetNoneGrab(bool _bNone) { m_bNone = _bNone; }

    void SetGrabDirection(GRAB_DIR _dir) { m_GrabDir = _dir; }

    GRAB_DIR GetGrabDirection() { return m_GrabDir; }
    Vec3 GetCurDir() { return m_vDir; }
    Vec3 GetStartPos() { return m_vStartPos; }
    Vec3 GetArriPos() { return m_vArriPos; }
    void SetStartPos(Vec3 _vPos) { m_vStartPos = _vPos; }
    void SetArriPos(Vec3 _vPos) { m_vArriPos = _vPos; }

    void SetGrabState(GRAB_STATE _state) { m_CurState = _state; }
    GRAB_STATE GetGrabState() { return m_CurState; }
    GRAB_STATE GetPrevGrabState() { return m_PrevState; }

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CGrabScript);
public:
    CGrabScript();
    ~CGrabScript();
};

