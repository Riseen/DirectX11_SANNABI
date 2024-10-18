#pragma once
#include "UI.h"
#include <Engine/Ptr.h>
#include <Engine/CTexture.h>

enum class TILEEDITORSTATE
{
    NONE,
    INSERT_TILE,
    DELETE_TILE,
    FILL
};

struct EditorTileInfo
{
    ImVec2 vTilePos;
    int iTileImageIndex;
    bool bColliderOn;

    // update Level�ÿ�
    // �ش���ġ�� �ش� �ε����� ���� imageindex���̸� �ݶ��̴��� Ÿ���ݶ��̴���ũ��Ʈ�� ���� �ڽ��� �߰�
    // �̹� �ݶ��̴��� ������ �߰������ʰ�
    // �� �ε����� �ƴѵ� �ݶ��̴��� ������ (���� �ݶ��̴��� �־���ߴ� Ÿ�ϵ�) �� �ڽ��� ã�� ��������

    // ã�Ⱑ ������.. �̸��� collider + index��ȣ�� �������� �װɷ� ã�� ����� ����������? �ͱ���
    // ��ǻ� editorui���� �ϴ� �����ϴ°��̱��ϴ�.
};

struct TileImageBtn
{
    ImVec2 vImageButtonLtUV;
    ImVec2 vImageButtonRbUV;
};

class CGameObject;

class TileMapEditorUI :
    public UI
{
private:
    Ptr<CTexture> m_Texture;
    Ptr<CTexture> m_PrevTexture;

    vector <vector<EditorTileInfo>> m_vTile;
    vector<TileImageBtn> m_vTImageBtns;
    TILEEDITORSTATE m_CurEditorState;


    ImVec2 m_vGridSize;
    ImVec2 m_vScrolling;
    ImVec2 m_vRenderSize;
    ImVec2 m_vPrevRenderSize;

    int m_Face[2];
    int m_PrevFace[2];
    int m_iCurTileImageIndex;
    int m_iCurGridTile[2];
    int m_iCurLTTile[2];
    int m_iCurRBTile[2];

    int m_PlusFace;

    int m_iNormalTileIndex[28];
    int m_iSpecialTileIndex[32];
    int m_iDamageTileIndex[32];


    float m_fCurMouseWheel;
    float m_fPrevMouseWheel;

    bool  m_bShowDebugRect;
    bool  m_bUpdateLevelTileMap;


private:
    void TileMapOnGrid(ImGuiIO& _io, CGameObject* _TargetObject);
    void TileMapTool(CGameObject* _TargetObject);
    void TileInfoChange(CGameObject* _TargetObject);

    void SetMouseWheel(ImGuiIO& _io);

    void FindLTRBTile(int _LT[], int _RB[], ImVec2 _vGridLT);

    bool isMouseInTile(int _index_One, int _index_Two);
    bool isMouseInTile(int _index_One, int _index_Two, int _anotherindex_One, int _anotherindex_Two);
    bool isObjectInGrid(ImVec2 _vGridLT, ImVec2 _vPos);
    bool isObjectInGrid(ImVec2 _vGridLT, ImVec2 _vPosLT, ImVec2 _vPosRB);
    bool isTileInfoChange();
    bool isMouseWheelChange();

    void SetTileInfo(CGameObject* _TargetObject);

    void Fill(int _index_One, int _index_Two);
    void EditorMode(CGameObject* _TargetObject);

    Tile_TYPE CheckTileType(int _iImageIndex);
    void ColliderUpdate(CGameObject* _TargetObject);

    void SaveTileMap();
    void LoadTileMap();

private:
    virtual void render_update() override;
    virtual void Deactivate() override;

public:
    TileMapEditorUI();
    ~TileMapEditorUI();
};

