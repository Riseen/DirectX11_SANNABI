#include "pch.h"
#include "CFontMgr.h"

#include "CDevice.h"

CFontMgr::CFontMgr()
	: m_pFW1Factory(nullptr)
	, m_pFontWrapper(nullptr)
	, m_wFont ()
	, m_Color {255,0,255,255}
	, m_fFontSize (50.f)
	, m_vFontPos {}
{
}

CFontMgr::~CFontMgr()
{
	if (nullptr != m_pFW1Factory)
		m_pFW1Factory->Release();

	if (nullptr != m_pFontWrapper)
		m_pFontWrapper->Release();
}

void CFontMgr::init()
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &m_pFW1Factory)))
	{
		assert(NULL);
	}

	if (FAILED(m_pFW1Factory->CreateFontWrapper(DEVICE, L"Noto Sans Bold", &m_pFontWrapper)))
	{
		assert(NULL);
	}
}

void CFontMgr::DrawFont(const wchar_t* _pStr, float _fPosX, float _fPosY, float _fFontSize, UINT _Color)
{
	m_pFontWrapper->DrawString(
		CONTEXT,
		_pStr, // String
		_fFontSize,// Font size
		_fPosX,// X position	À©µµ¿ìÁÂÇ¥
		_fPosY,// Y position
		_Color,// Text color, 0xAaBbGgRr
		FW1_RESTORESTATE      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
	);
}

void CFontMgr::render()
{
	DrawFont(m_wFont, m_vFontPos.x, m_vFontPos.y, m_fFontSize, FONT_RGBA(m_Color.r, m_Color.g, m_Color.b, m_Color.a));
}

void CFontMgr::SetFont(const wchar_t* _wcFont, Vec2 _vFontPos, float _fFontSize, tPixel _Color)
{
	for (int i = 0; i < 256; ++i)
	{
		m_wFont[i] = _wcFont[i];
	}
	m_vFontPos = _vFontPos;
	m_fFontSize = _fFontSize;
	m_Color = _Color;
}

void CFontMgr::ClearFont()
{
	wchar_t wc[256] = {};
	for (int i = 0; i < 256; ++i)
	{
		m_wFont[i] = wc[i];
	}
	m_vFontPos = Vec2{};
	m_fFontSize = 0.f;
	m_Color = { 0,0,0,0 };
}

