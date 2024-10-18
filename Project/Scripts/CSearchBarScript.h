#pragma once
#include <Engine/CScript.h>
#include "CGrabScript.h"

enum class SEARCH_PRIORITY
{
    ENEMY,
    SWINGHOOK,
    CARGO,
    ENABLED,
    NOTHING
};


class CSearchBarScript :
    public CScript
{
private:
    SEARCH_PRIORITY m_CurSearchPri;
    SEARCH_PRIORITY m_PrevSearchPri;

    Vec3 m_vSearchObjPos;
    CGameObject* m_vSearchObj;

    Vec3 m_vDir;
    float m_fMaxDist;

    GRAB_DIR m_CurGrabDir;

    bool  m_bSearchActive;

private:
    void SearchRay(bool _bActive);
    void SetPosToLine(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    bool IsRatioX(float _x, float _xStart, float _y, float _yStart);
    

public:
    SEARCH_PRIORITY GetCurPriority() { return m_CurSearchPri; }
    Vec3 GetSearchObjPos() { return m_vSearchObjPos;}
    CGameObject* GetSearchObj() { return m_vSearchObj;}
    GRAB_DIR GetGrabDir() { return m_CurGrabDir; }
    bool GetSearchAct() { return m_bSearchActive; }

    void SetDir(Vec3 _vDir) { m_vDir = _vDir; }
    void SetSearchAct(bool _bAct);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CSearchBarScript);
public:
    CSearchBarScript();
    ~CSearchBarScript();
};

