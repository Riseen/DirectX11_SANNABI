#pragma once
#include <Engine/CScript.h>
#include "CPlayerScript.h"
#include "CAfterImageManagerScript.h"

class CArmScript :
    public CScript
{
private:
    CGameObject* m_SearchObj;
    CGameObject* m_ChainObj;
    CGameObject* m_CurEnemyObj;
    Vec3 m_vSearchBarScale;
    Vec3 m_vSearch;
    Vec3 m_vDestPos;
    Vec3 m_vBeforeHoldingPos;

    AFTERIMAGE_TYPE m_CurState;

    float m_fRadian;
    float m_fCosTheta;
    float m_fNotShootDE;

    bool  m_bHolding;
    bool  m_bEnemyAttack;

private:
    void RotateReset(CGameObject* _pGrab);
    void ShootGrab(CGameObject* _pGrab);
    void ShootGrabAndReturn(CGameObject* _pGrab);
    void GrabAction(CGameObject* _pGrab);
    void PlayerStateSet(float _fDegree);
    void CreateGrabTail(Vec3 _vStartPos, Vec3 _vDestPos);

public:
    void SetHolding(bool _bHolding) { m_bHolding = _bHolding; }
    void SetAttack(bool _bAtk) { m_bEnemyAttack = _bAtk; }

    bool IsHolding() { return m_bHolding; }
    Vec3 GetDestPos() { return m_vDestPos; }
    Vec3 GetBeforeHodlingPos() { return m_vBeforeHoldingPos; }
    AFTERIMAGE_TYPE GetCurShotState() { return m_CurState; }
 
public:
    void ChangeARMState(PLAYER_STATE _curPlayerState, PLAYER_STATE _prevPlayerState, bool _bLp);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CArmScript);
public:
    CArmScript();
    ~CArmScript();
};

