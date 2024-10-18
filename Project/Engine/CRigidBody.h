#pragma once
#include "CComponent.h"

enum class RIGIDBODY_STATE
{
    DEFAULT,
    SWING,
    SWINGJUMP,
};

enum class RIGIDBODY_UPDOWNSTATE
{
    GROUND,
    JUMPING,
    FALLING,
};

class CRigidBody :
    public CComponent
{
private:
    Vec2	 m_vForce;	        // 크기, 방향
    Vec2	 m_vAccel;	        // 가속도
    Vec2	 m_vAccelA;	        // 추가 가속도
    Vec2	 m_vVelocity;	    // 속도 (크기 : 속력, 방향)
    Vec2     m_vPrevVelocity;   // 이전 속도 
    Vec2     m_vSwingVelcity;   // 이전 속도 (swing용)
    Vec2	 m_vMaxVelocity;	// 최대 속도

    Vec3     m_vGrabPos;        // 그랩 위치
    Vec3     m_vSwingStartPos;
    Vec3     m_vSwingEndPos;
    Vec3     m_vSwingDir;


    RIGIDBODY_STATE m_CurState;
    RIGIDBODY_STATE m_PrevState;

    float	 m_fMass;	        // 질량
    float    m_fFricCoeff;      // 마찰력
    float    m_fCurAngle;       // 현재 각도
    float    m_fMaxAngle;
    float    m_fLowGravityAcc;  

    bool     m_bHolding;        // Holding


    RIGIDBODY_UPDOWNSTATE m_CurUpDownState;
    RIGIDBODY_UPDOWNSTATE m_PrevUpDownState;

public:
    Vec2 GetForce() { return m_vForce; }
    Vec2 GetAccel() { return m_vAccel; }
    Vec2 GetAccelAlpha() { return m_vAccelA; }
    Vec2 GetVelocity() { return m_vVelocity; }
    Vec2 GetMaxVelocity() { return m_vMaxVelocity; }
    Vec3 GetStartPos() { return m_vSwingStartPos; }
    Vec3 GetEndPos() { return m_vSwingEndPos; }

    RIGIDBODY_STATE GetCurRigidBodyState() { return m_CurState; }
    float GetMass() { return m_fMass; }
    float GetFricCoeff() { return m_fFricCoeff; }
    float GetSpeed() { return m_vVelocity.Length(); }
    float GetCurAngle() { return XMConvertToDegrees(m_fCurAngle); }
    RIGIDBODY_UPDOWNSTATE GetCurUpDownState() { return m_CurUpDownState; }


    void SetForce(Vec2 _vForce) { m_vForce = _vForce; }
    void SetAccel(Vec2 _vAccel) { m_vAccel = _vAccel; }
    void SetAccelAlpha(Vec2 _vAccel_A) { m_vAccelA = _vAccel_A; }
    void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
    void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
    void SetGrabPos(Vec3 _vPos) { m_vGrabPos = _vPos; }
    void SetCurRigidBodyState(RIGIDBODY_STATE _state) { m_CurState = _state; }
    void SetHolding(bool _bHolding) { m_bHolding = _bHolding; }

    void SetSwingStartPos(Vec3 _vPos) { m_vSwingStartPos = _vPos; }
    void SetSwingEndPos(Vec3 _vPos) { m_vSwingEndPos = _vPos; }

    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
    void SetMass(float _fMass) { m_fMass = _fMass; }
    void SetFricCoeff(float _fFricCoeff) { m_fFricCoeff = _fFricCoeff; }
   
    void SwingDir();

private:
    

private:
    void Move();

public:
    virtual void begin() override;
    virtual void finaltick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CRigidBody);
    CRigidBody();
    ~CRigidBody();
};

