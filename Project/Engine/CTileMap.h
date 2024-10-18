#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

struct tTileInfo
{
    Vec2 vLeftTopUV;    
    int  bRender;
    int  padding;
};


class CTileMap :
    public CRenderComponent
{
private:
    UINT                m_FaceX;            // 가로 타일 개수
    UINT                m_FaceY;            // 세로 타일 개수
    Vec2                m_vTileRenderSize;  // 타일 1칸 사이즈

    Ptr<CTexture>       m_TileAtlas;
    Vec2                m_vTilePixelSize;
    Vec2                m_vSliceSizeUV;

    UINT                m_MaxCol;
    UINT                m_MaxRow;

    vector<tTileInfo>   m_vecTileInfo;
    CStructuredBuffer*  m_TileInfoBuffer;

public:
    void SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize);
    Ptr<CTexture> GetTileAtlas() { return m_TileAtlas; }

    void SetFace(UINT _FaceX, UINT _FaceY);
    UINT GetFaceX() { return m_FaceX; }
    UINT GetFaceY() { return m_FaceY; }

    void SetTileRenderSize(Vec2 _TileRenderSize) { m_vTileRenderSize = _TileRenderSize; }
    Vec2 GetTileRenderSize() { return m_vTileRenderSize; }

    UINT GetMaxCol() { return m_MaxCol; }
    UINT GetMaxRow() { return m_MaxRow; }
    Vec2 GetTilePixelSize() { return m_vTilePixelSize; }

    Vec2 GetSliceSizeUV() { return m_vSliceSizeUV; }
    vector<tTileInfo> GetTileInfo() { return m_vecTileInfo; }

    void SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx, bool _bRender);


public:
    virtual void finaltick() override;
    virtual void UpdateData() override;
    virtual void render() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTileMap);
public:
    CTileMap();
    CTileMap(const CTileMap& _OriginTileMap);
    ~CTileMap();
};

