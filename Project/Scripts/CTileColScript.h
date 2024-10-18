#pragma once

#include <Engine/CScript.h>

class CTileColScript :
    public CScript
{
private:
    Tile_TYPE m_CurType;
    OverlapDir m_CurOverlapDir;

private:
    

public:
    void SetTileType(Tile_TYPE _type) { m_CurType = _type; }
    Tile_TYPE GetTileType() { return m_CurType; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual OverlapDir CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTileColScript);
public:
    CTileColScript();
    ~CTileColScript();
};

