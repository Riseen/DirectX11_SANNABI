#pragma once
#include "UI.h"
#include <Engine/CTexture.h>
#include <queue>

struct tAnim
{
    ImVec2  vLeftTop;       // 좌상단
    ImVec2  vSlice;         // Slice. 
    ImVec2  vOffset;        // 오프셋
    ImVec2  vPrevOffset;    // 이전 오프셋값

    ImVec2  vImageSize;
    ImVec2  vImageLtUV;
    ImVec2  vImageRbUV;
    ImVec2    vBackground;    // 모든 벡터에서 동일해야함 가진 이미지중에 가장커야한다.
    float   fDuration;        // 한프레임당 소요시간 
};


enum class MOUSE_STATE
{
    KEY_TAP,
    KEY_PRESSED,
    KEY_RELEASE,
    KEY_NONE,
};


enum class MOUSE_CURSOR_STATE
{
    ARROW,
    RESIZE_LEFT,
    RESIZE_RIGHT,
    RESIZE_UP,
    RESIZE_DOWN,
    RESIZE_LEFTTOP,
    RESIZE_LEFTBOTTOM,
    RESIZE_RIGHTTOP,
    RESIZE_RIGHTBOTTOM,
    SELECT,
    MOVE,
};

enum class EDITOR_MODE
{
    NONE,
    SLICE,
    SMART_SLICE,
    TRIM_SLICE,
    SLICE_RECT_EDIT,
};

class AnimatorEditorUI :
    public UI
{
private:
    CTexture* m_Texture;

    vector<tAnim> m_Anim;
    vector<ImVec4> m_vSliceRect;
    vector<wstring> m_FileName;

    ImVec2 m_vTextureSize;
    ImVec2 m_vTextureOriginSize;
    ImVec2 m_vStartMousePos;
    ImVec2 m_vGridLeftTop;
    ImVec2 m_vCurMousePos;
    ImVec2 m_vPrevMousePos;
    ImVec2 m_vEndMousePos;
    ImVec2 m_vGridSize;
    ImVec2 m_vAnimPanelSize;
    ImVec2 m_vAnimPanlePos;

    ImVec2 m_vScrolling;

    ImVec2 m_vAnimationZoom;

    string	m_strName;


    bool m_bSliceRectReset;
    bool m_bPlay;
    bool m_bLoop;

    float m_fAccTime;
    float m_fCurMouseWheel;
    float m_fPrevMouseWheel;

    int m_iCurrent_Select_Image;
    int m_iFPS;
    int m_iCurSliceRect;

    MOUSE_STATE m_CurMouseState;
    MOUSE_STATE m_prevMouseState;

    MOUSE_CURSOR_STATE m_CurMouseCursor;

    EDITOR_MODE m_EditorMode;
private:
    void AnimationEditBtns();
    void AnimationSpriteEditBtns();
    void AnimationFrame();
    void AnimationFrameEditBtns();
    void AnimationPreview();
    void AltasImageOnGrid(ImGuiIO& _io);
    void SliceRectrender(ImDrawList* _drawlist);
    void EditorStatus();
    void AnimationSaveLoadBtns();

    void ApplyOffset();
    void OpenFileDialog(vector<wstring>& _FilesName);
    ImVec2 LoadMeta(const wstring& _strMetaRelativePath);
    void LoadTexture();
    void LoadAnimation();
    void SaveAnimation(const wstring& _strRelativePath);
    void SaveFile();
    //void FScanf(char* _pOutBuff, FILE* _pFile);

    void SliceTexture();
    void SmartSliceTexture();
    void TrimSliceTexture();
    void PixelTraverse(vector<ImVec2>& _vPixel, vector<bool>& _vCheck, ImVec2 _vPixelPos, tPixel* _pPixel);
    void PlayAnimation();

    void ResetAnimation();
    void SetTextureSize(ImGuiIO& _io);
    void AddToSprite(vector<tAnim>& _Anim);

    void SliceRectEdit();
    void SliceRectSelect(int& _CurSliceRect, const ImVec2 _CurMousePos);
    void SliceRectMove(int& _CurSliceRect, const ImVec2 _CurMousePos, const ImVec2 _PrevMousePos);

    void ChangeMouseCursor(MOUSE_CURSOR_STATE _CurMouseCursor);
    void SetMouseCursorState(MOUSE_CURSOR_STATE& _CurMouseCursor, int& _CurSliceRect, const ImVec2 _CurMousePos);
    void SetMouseState(MOUSE_STATE& CurMouseState, MOUSE_CURSOR_STATE& _CurMouseCursor);

    void SetEditorMode(EDITOR_MODE _EditorMode) { m_EditorMode = _EditorMode; }
    void SetCurMouseState(MOUSE_STATE _MouseState) { m_CurMouseState = _MouseState; }
    void SetMouseCursor(MOUSE_CURSOR_STATE _MouseCursorState) { m_CurMouseCursor = _MouseCursorState; }
public:
    virtual void render_update() override;
    virtual void Deactivate() override;

    bool isImageLoad()
    {
        if (m_Texture)
            return true;
        else
            return false;
    }
    bool isAnim()
    {
        if (m_Anim.size() <= 0)
            return false;
        else
            return true;
    }
    CTexture* GetTexture() { return m_Texture; }
    const ImVec2 GetTextureSize() { return m_vTextureSize; }
    const int GetCImage() { return m_iCurrent_Select_Image; }
    const tAnim GetCurAnim() { return m_Anim[m_iCurrent_Select_Image]; }


public:
    AnimatorEditorUI();
    ~AnimatorEditorUI();

};

