#pragma once
#include "singleton.h"

#include <FontEngine/FW1FontWrapper.h>
#include <FontEngine/FW1CompileSettings.h>

#ifdef _DEBUG
#pragma comment(lib, "FontEngine/FW1FontWrapper_debug")
#else
#pragma comment(lib, "FontEngine/FW1FontWrapper"))
#endif


#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)



class CFontMgr :
    public CSingleton<CFontMgr>
{
    SINGLE(CFontMgr);
private:
    IFW1Factory*        m_pFW1Factory;
    IFW1FontWrapper*    m_pFontWrapper;

    wchar_t m_wFont[256];
    tPixel  m_Color;
    Vec2    m_vFontPos;
    float   m_fFontSize;

public:
    void init();
    void DrawFont(const wchar_t* _pStr, float _fPosX, float _fPosY, float _fFontSize, UINT _Color);

    void render();

   

public:
    void SetFont(const wchar_t* _wcFont, Vec2 _vFontPos, float _fFontSize, tPixel _Color);
    void ClearFont();
};

