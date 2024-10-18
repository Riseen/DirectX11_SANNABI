#include "pch.h"
#include "AnimatorEditorUI.h"
#include "AnimatorFullGridUI.h"


#include "imgui_internal.h"
#include <shobjidl_core.h>
#include <iostream>

#include <Engine/CEngine.h>
#include <Engine/CPathMgr.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CMeshRender.h>
#include <Engine/CTransform.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CDevice.h>
#include <Engine/CTimeMgr.h>

#include <Engine/CKeyMgr.h>



#define SCL m_vScrolling
#define WSZ ImGui::GetWindowPos()
#define SWSZ m_vScrolling + ImGui::GetWindowPos()



AnimatorEditorUI::AnimatorEditorUI()
	: UI("AnimatorEditorUI", "##AnimatorEditorUI")
	, m_Texture(nullptr)
	, m_vTextureSize{}
	, m_vTextureOriginSize{}
	, m_vStartMousePos{}
	, m_vGridLeftTop{}
	, m_vCurMousePos{}
	, m_vPrevMousePos{}
	, m_vEndMousePos{}
	, m_vGridSize{ 800.f, 600.f }
	, m_vAnimPanelSize{ 300.f, 300.f }
	, m_vAnimPanlePos{ 1150.f, 500.f }
	, m_vScrolling{}
	, m_vAnimationZoom{ 1.f, 1.f, }

	, m_strName{ "DefaultName" }

	, m_bSliceRectReset(false)
	, m_bPlay(false)
	, m_bLoop(true)

	, m_fAccTime(0.f)

	, m_iCurrent_Select_Image(0)
	, m_iFPS(10)
	, m_iCurSliceRect(0)

	, m_CurMouseState(MOUSE_STATE::KEY_NONE)
	, m_prevMouseState(MOUSE_STATE::KEY_NONE)
	, m_CurMouseCursor(MOUSE_CURSOR_STATE::MOVE)
	, m_EditorMode(EDITOR_MODE::NONE)
{
	Deactivate();
	SetModal(false);
}

AnimatorEditorUI::~AnimatorEditorUI()
{
}



void AnimatorEditorUI::render_update()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Checkbox("Move Title Bar Only##bool", &io.ConfigWindowsMoveFromTitleBarOnly);// ImGui::SameLine();

	m_vCurMousePos = ImGui::GetMousePos();

	AnimationSpriteEditBtns();

	AnimationSaveLoadBtns();

	EditorStatus();

	AnimationFrameEditBtns();


	AltasImageOnGrid(io);

	AnimationPreview();

	AnimationFrame();

	AnimationEditBtns();




	switch (m_EditorMode)
	{
	case EDITOR_MODE::NONE:
		break;
	case EDITOR_MODE::SLICE:
		SliceTexture();
		break;
	case EDITOR_MODE::SMART_SLICE:
		SmartSliceTexture();
		break;
	case EDITOR_MODE::TRIM_SLICE:
		TrimSliceTexture();
		break;
	case EDITOR_MODE::SLICE_RECT_EDIT:
		SliceRectEdit();
		break;
	default:
		break;
	}

	if (m_EditorMode == EDITOR_MODE::NONE)
		SliceRectSelect(m_iCurSliceRect, m_vCurMousePos);


	// SliceRect Edit (Select, Move, Edit)
	if (m_EditorMode == EDITOR_MODE::NONE && KEY_PRESSED(KEY::LCTRL))
	{
		SetEditorMode(EDITOR_MODE::SLICE_RECT_EDIT);
	}
	else if (m_EditorMode == EDITOR_MODE::SLICE_RECT_EDIT && KEY_RELEASED(KEY::LCTRL))
	{
		SetEditorMode(EDITOR_MODE::NONE);
		SetCurMouseState(MOUSE_STATE::KEY_NONE);
	}
	else if (m_EditorMode == EDITOR_MODE::NONE && KEY_PRESSED(KEY::LSHIFT))
	{
		SliceRectMove(m_iCurSliceRect, m_vCurMousePos, m_vPrevMousePos);
	}



	if (!m_Anim.size() <= 0 && m_bPlay)
	{
		PlayAnimation();
	}

	m_vPrevMousePos = ImGui::GetMousePos();
}

void AnimatorEditorUI::Deactivate()
{
	UI::Deactivate();
	ImGui::SetWindowFocus(nullptr);

	m_vScrolling = ImVec2(0.f, 0.f);
}




void AnimatorEditorUI::SliceTexture()
{
	if (KEY_TAP(KEY::LBTN))
	{
		if (m_vGridLeftTop.x <= m_vCurMousePos.x &&
			m_vGridLeftTop.y <= m_vCurMousePos.y &&
			m_vGridLeftTop.x + m_vGridSize.x >= m_vCurMousePos.x &&
			m_vGridLeftTop.y + m_vGridSize.y >= m_vCurMousePos.y)
		{
			SetCurMouseState(MOUSE_STATE::KEY_TAP);
		}
	}

	if (KEY_PRESSED(KEY::LBTN))
	{
		if (m_vGridLeftTop.x <= m_vCurMousePos.x &&
			m_vGridLeftTop.y <= m_vCurMousePos.y &&
			m_vGridLeftTop.x + m_vGridSize.x >= m_vCurMousePos.x &&
			m_vGridLeftTop.y + m_vGridSize.y >= m_vCurMousePos.y &&
			m_prevMouseState == MOUSE_STATE::KEY_TAP)
		{
			SetCurMouseState(MOUSE_STATE::KEY_PRESSED);
		}
	}
	if (KEY_RELEASED(KEY::LBTN))
	{
		if (m_vGridLeftTop.x <= m_vCurMousePos.x &&
			m_vGridLeftTop.y <= m_vCurMousePos.y &&
			m_vGridLeftTop.x + m_vGridSize.x >= m_vCurMousePos.x &&
			m_vGridLeftTop.y + m_vGridSize.y >= m_vCurMousePos.y)
		{
			SetCurMouseState(MOUSE_STATE::KEY_RELEASE);
		}
	}

	switch (m_CurMouseState)
	{
	case MOUSE_STATE::KEY_TAP:
	{
		m_vStartMousePos = ImVec2(0.f, 0.f);
		m_vStartMousePos = ImGui::GetMousePos();

		break;
	}
	case MOUSE_STATE::KEY_PRESSED:
	{
		m_vEndMousePos = ImGui::GetMousePos();

		ImDrawList* draw_list = ImGui::GetWindowDrawList(); //ImGui::GetWindowDrawList();
		draw_list->AddRect(m_vStartMousePos, m_vEndMousePos, ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));   // Border
		break;
	}
	case MOUSE_STATE::KEY_RELEASE:
	{
		m_vSliceRect.push_back(ImVec4(m_vStartMousePos.x - WSZ.x - SCL.x, m_vStartMousePos.y - WSZ.y - SCL.y,
			m_vEndMousePos.x - WSZ.x - SCL.x, m_vEndMousePos.y - WSZ.y - SCL.y));
		SetEditorMode(EDITOR_MODE::NONE);
		SetCurMouseState(MOUSE_STATE::KEY_NONE);
		m_iCurSliceRect = m_vSliceRect.size() - 1;
		break;
	}
	case MOUSE_STATE::KEY_NONE:
		break;
	default:
		break;
	}

	m_prevMouseState = m_CurMouseState;
}

void AnimatorEditorUI::SmartSliceTexture()
{
	if (KEY_TAP(KEY::LBTN))
	{
		if (m_vGridLeftTop.x <= m_vCurMousePos.x &&
			m_vGridLeftTop.y <= m_vCurMousePos.y &&
			m_vGridLeftTop.x + m_vGridSize.x >= m_vCurMousePos.x &&
			m_vGridLeftTop.y + m_vGridSize.y >= m_vCurMousePos.y)
		{
			tPixel* pPixel = m_Texture->GetPixels();
			tPixel pixel = { 0,0,0,0 };

			ImVec2 vPixelPos = ImVec2(m_vCurMousePos.x - m_vScrolling.x - ImGui::GetWindowPos().x,
				m_vCurMousePos.y - m_vScrolling.y - ImGui::GetWindowPos().y);

			pixel = pPixel[(m_Texture->GetWidth() * (UINT)vPixelPos.y) + (UINT)vPixelPos.x];


			vector<bool> vCheckPixels;
			vCheckPixels.resize((UINT)(m_Texture->GetWidth() * m_Texture->GetHeight()));
			vector<ImVec2> vTotalPixels;
			PixelTraverse(vTotalPixels, vCheckPixels, vPixelPos, pPixel);


			ImVec4 vNewSliceRect = { vTotalPixels[0].x, vTotalPixels[0].y,
									 vTotalPixels[0].x, vTotalPixels[0].y };
			vector<ImVec2>::iterator iter = vTotalPixels.begin();

			for (; iter != vTotalPixels.end(); ++iter)
			{
				if (vNewSliceRect.x > iter->x)
				{
					vNewSliceRect.x = iter->x;
				}
				if (vNewSliceRect.y > iter->y)
				{
					vNewSliceRect.y = iter->y;
				}
				if (vNewSliceRect.z < iter->x)
				{
					vNewSliceRect.z = iter->x;
				}
				if (vNewSliceRect.w < iter->y)
				{
					vNewSliceRect.w = iter->y;
				}
			}

			m_vSliceRect.push_back(vNewSliceRect);


			SetEditorMode(EDITOR_MODE::NONE);
		}
	}
}

void AnimatorEditorUI::TrimSliceTexture()
{
	// texture 전체 Pixel 얻어오기
	tPixel* pPixel = m_Texture->GetPixels();
	tPixel pixel = {0,0,0,0};
	UINT TextureWidth = m_Texture->GetWidth();

	ImVec4 vNewSliceRect = {};

	// 현재 선택 SliceRect 좌상단, 우하단 좌표 넣기
	ImVec4 vPixelPos = ImVec4(m_vSliceRect[m_iCurSliceRect].x,
		m_vSliceRect[m_iCurSliceRect].y,
		m_vSliceRect[m_iCurSliceRect].z,
		m_vSliceRect[m_iCurSliceRect].w);

	if (vPixelPos.x < 0.f)
		vPixelPos.x = 0.f;
	if (vPixelPos.y < 0.f)
		vPixelPos.y = 0.f;
	if (vPixelPos.z > m_Texture->GetWidth())
		vPixelPos.z = m_Texture->GetWidth() - 1;
	if (vPixelPos.w > m_Texture->GetHeight())
		vPixelPos.w = m_Texture->GetHeight() - 1;

	// 텍스쳐 좌상단부터 세로로 한줄씩
	for (UINT i = (UINT)vPixelPos.y; i <= (UINT)vPixelPos.w; i++)
	{
		// 텍스쳐 세로부터 가로 전체 탐색
		for (UINT j = (UINT)vPixelPos.x; j <= (UINT)vPixelPos.z; j++)
		{
			// 현재 픽셀 = (너비 * 높이) + 가로
			pixel = pPixel[(TextureWidth * i) + j];

			// 검사 픽셀이 없을경우 (알파가 0 -> 색이없음)
			if (pixel.a == 0)
				continue;
			// 처음 찾은 픽셀 기록
			else if (!vNewSliceRect.x)
			{
				vNewSliceRect.x = j;
				vNewSliceRect.y = i;
				vNewSliceRect.z = j;
				vNewSliceRect.w = i;
			}

			// LEFT 보다 작은 픽셀좌표 발견시 기록
			if (vNewSliceRect.x > j)
			{
				vNewSliceRect.x = j;
			}
			// UP보다 작은 픽셀 발견시 기록
			if (vNewSliceRect.y > i)
			{
				vNewSliceRect.y = i;
			}
			// RIGHT보다 큰 픽셀 발견시 기록
			if (vNewSliceRect.z < j)
			{
				vNewSliceRect.z = j;
			}
			// DOWN보다 큰 픽셀 발견시 기록
			if (vNewSliceRect.w < i)
			{
				vNewSliceRect.w = i;
			}
		}
	}

	m_vSliceRect[m_iCurSliceRect] = vNewSliceRect;

	SetEditorMode(EDITOR_MODE::NONE);
}

void AnimatorEditorUI::PixelTraverse(vector<ImVec2>& _vPixel, vector<bool>& _vCheck, ImVec2 _vPixelPos, tPixel* _pPixel)
{
	// 들어온 픽셀 push back
	_vPixel.push_back(_vPixelPos);

	// 현재 체크 픽셀 벡터도 true
	_vCheck[((m_Texture->GetWidth() * (UINT)_vPixelPos.y)) + (UINT)_vPixelPos.x] = true;

	int up = (m_Texture->GetWidth() * ((int)_vPixelPos.y - 1)) + (int)_vPixelPos.x;
	int down = (m_Texture->GetWidth() * ((int)_vPixelPos.y + 1)) + (int)_vPixelPos.x;
	int right = (m_Texture->GetWidth() * (int)_vPixelPos.y) + ((int)_vPixelPos.x + 1);
	int left = (m_Texture->GetWidth() * (int)_vPixelPos.y) + ((int)_vPixelPos.x - 1);


	if (!((int)_vPixelPos.y - 1 < 0) &&
		_pPixel[up].a != 0 &&
		_vCheck[up] == false)
	{
		PixelTraverse(_vPixel, _vCheck, ImVec2(_vPixelPos.x, _vPixelPos.y - 1.f), _pPixel);
	}
	if (!((int)_vPixelPos.x - 1 < 0) &&
		_pPixel[left].a != 0 &&
		_vCheck[left] == false)
	{
		PixelTraverse(_vPixel, _vCheck, ImVec2(_vPixelPos.x - 1.f, _vPixelPos.y), _pPixel);
	}
	if (!((int)_vPixelPos.y + 1 >= m_Texture->GetHeight()) &&
		_pPixel[down].a != 0 &&
		_vCheck[down] == false)
	{
		PixelTraverse(_vPixel, _vCheck, ImVec2(_vPixelPos.x, _vPixelPos.y + 1.f), _pPixel);
	}
	if (!((int)_vPixelPos.x + 1 >= m_Texture->GetWidth()) &&
		_pPixel[right].a != 0 &&
		_vCheck[right] == false)
	{
		PixelTraverse(_vPixel, _vCheck, ImVec2(_vPixelPos.x + 1.f, _vPixelPos.y), _pPixel);
	}


	return;
}




void AnimatorEditorUI::AnimationEditBtns()
{
	// Animation Editor Btn
	if (m_Anim.size() <= 0)
		return;

	//ImGui::NewLine();
	ImGui::SameLine(820);
	ImGui::PushID("##Animation Editor Btns");
	ImGuiStyle& style = ImGui::GetStyle();


	ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (false ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
	ImGuiID editor_Btns_ID = 2;
	bool child_is_visible = ImGui::BeginChild(editor_Btns_ID, ImVec2(300.f, 220.f), ImGuiChildFlags_Border, child_flags);

	{
		ImGui::Text("Offset X : ");
		ImGui::SameLine();

		if (ImGui::InputFloat("##Offset X", &m_Anim[m_iCurrent_Select_Image].vOffset.x, 1.f, 0.f, "%.5f"))
		{
			/*m_Anim[m_iCurrent_Select_Image].vLeftTop = ImVec2(m_Anim[m_iCurrent_Select_Image].vLeftTop.x + m_Anim[m_iCurrent_Select_Image].vOffset.x - m_Anim[m_iCurrent_Select_Image].vPrevOffset.x, m_Anim[m_iCurrent_Select_Image].vLeftTop.y);
			m_Anim[m_iCurrent_Select_Image].vSlice = ImVec2(m_Anim[m_iCurrent_Select_Image].vSlice.x + m_Anim[m_iCurrent_Select_Image].vOffset.x - m_Anim[m_iCurrent_Select_Image].vPrevOffset.x, m_Anim[m_iCurrent_Select_Image].vSlice.y);

			m_Anim[m_iCurrent_Select_Image].vImageLtUV = ImVec2(m_Anim[m_iCurrent_Select_Image].vLeftTop.x / m_vTextureSize.x, m_Anim[m_iCurrent_Select_Image].vLeftTop.y / m_vTextureSize.y);
			m_Anim[m_iCurrent_Select_Image].vImageRbUV = ImVec2(m_Anim[m_iCurrent_Select_Image].vSlice.x / m_vTextureSize.x, m_Anim[m_iCurrent_Select_Image].vSlice.y / m_vTextureSize.y);*/

		}

		ImGui::Text("Offset Y : ");
		ImGui::SameLine();
		if (ImGui::InputFloat("##Offset Y", &m_Anim[m_iCurrent_Select_Image].vOffset.y, 1.f, 1.f, "%.5f"))
		{
			/*m_Anim[m_iCurrent_Select_Image].vLeftTop = ImVec2(m_Anim[m_iCurrent_Select_Image].vLeftTop.x, m_Anim[m_iCurrent_Select_Image].vLeftTop.y + m_Anim[m_iCurrent_Select_Image].vOffset.y - m_Anim[m_iCurrent_Select_Image].vPrevOffset.y);
			m_Anim[m_iCurrent_Select_Image].vSlice = ImVec2(m_Anim[m_iCurrent_Select_Image].vSlice.x, m_Anim[m_iCurrent_Select_Image].vSlice.y + m_Anim[m_iCurrent_Select_Image].vOffset.y - m_Anim[m_iCurrent_Select_Image].vPrevOffset.y);


			m_Anim[m_iCurrent_Select_Image].vImageLtUV = ImVec2(m_Anim[m_iCurrent_Select_Image].vLeftTop.x / m_vTextureSize.x, m_Anim[m_iCurrent_Select_Image].vLeftTop.y / m_vTextureSize.y);
			m_Anim[m_iCurrent_Select_Image].vImageRbUV = ImVec2(m_Anim[m_iCurrent_Select_Image].vSlice.x / m_vTextureSize.x, m_Anim[m_iCurrent_Select_Image].vSlice.y / m_vTextureSize.y);*/
		}
		m_Anim[m_iCurrent_Select_Image].vPrevOffset = m_Anim[m_iCurrent_Select_Image].vOffset;

	}

	ImGui::Separator();


	ImGui::Text("Current Frame");
	ImGui::SliderInt("##Current Frame", &m_iCurrent_Select_Image, 0, (int)m_Anim.size() - 1);

	ImGui::SameLine();
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##left", ImGuiDir_Left))
	{
		if (m_iCurrent_Select_Image > 0)
			m_iCurrent_Select_Image--;
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
		if (m_iCurrent_Select_Image < (int)m_Anim.size() - 1)
			m_iCurrent_Select_Image++;
	}
	ImGui::PopButtonRepeat();


	ImGui::Checkbox("Loop##Loop Checkbox", &m_bLoop);

	ImGui::Separator();

	ImGui::Text("     FPS ");
	ImGui::SameLine();
	m_Anim[m_iCurrent_Select_Image].fDuration = 1.f / m_iFPS;
	ImGui::InputInt("##FPS", &m_iFPS, 1, 1);

	ImGui::Text("Duration ");
	ImGui::SameLine();
	ImGui::InputFloat("##Duartion", &m_Anim[m_iCurrent_Select_Image].fDuration, 1, 1, "%.5f");

	ImGui::Separator();
	ImGui::Text("Animation Name");

	char AnimationNameBufferbuf[256] = "";
	strcpy_s(AnimationNameBufferbuf, m_strName.c_str());
	if (ImGui::InputText("##AnimationNameInput", AnimationNameBufferbuf, 256))
	{
		string str(AnimationNameBufferbuf);
		m_strName = AnimationNameBufferbuf;
	}

	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::PopID();




	ImGui::SameLine();
	ImGui::Text("                                                 ");
	ImGui::SameLine();
	ImGui::BeginGroup();

	for (int i = 0; i < 9; ++i)
		ImGui::Text(" ");

	if (ImGui::Button("Play##Play Btn", ImVec2(50, 20)))
	{
		m_bPlay = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause##Pause Btn", ImVec2(50, 20)))
	{
		m_bPlay = false;
	}

	ImGui::BeginChild(3, ImVec2(200.f, 70.f));
	static int Zoom = 0;
	ImGui::SliderInt(" Zoom ##Animation Zoom In Out", &Zoom, -100, 100);
	ImGui::EndChild();


	ImGui::EndGroup();

}

void AnimatorEditorUI::AnimationSpriteEditBtns()
{
	if (ImGui::Button("Load Texture##Load Texture Btn##Load Texture##Load Texture Btn", ImVec2(100, 20)))
	{
		LoadTexture();
	}
	ImGui::SameLine();
	if (ImGui::Button("Slice Texture##Slice Texture Btn##Slice Texture##Slice Texture Btn", ImVec2(100, 20)))
	{
		SetEditorMode(EDITOR_MODE::SLICE);
		m_bSliceRectReset = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Add to Sprite Animation##Add to Sprite Animation Btn", ImVec2(180, 20)))
	{
		AddToSprite(m_Anim);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset Slice Rect##Reset Slice Rect Btn", ImVec2(130, 20)))
	{
		m_bSliceRectReset = true;
		m_vSliceRect.clear();
		m_iCurSliceRect = 0;
	}
	ImGui::SameLine();
	if (ImGui::Button("Smart Slice##Smart Slice Btn", ImVec2(130, 20)))
	{
		SetEditorMode(EDITOR_MODE::SMART_SLICE);
	}
	ImGui::SameLine();
	if (ImGui::Button("Trim Slice##Trim Slice Btn", ImVec2(130, 20)))
	{
		SetEditorMode(EDITOR_MODE::TRIM_SLICE);
	}
}

void AnimatorEditorUI::AnimationFrame()
{
	ImGui::SameLine();
	ImGui::PushID("##HorizontalScrolling");
	ImGuiStyle& style = ImGui::GetStyle();

	float child_height = ImGui::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
	ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (false ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
	ImGuiID Animation_Frame_ID = 1;
	bool child_is_visible = ImGui::BeginChild(Animation_Frame_ID, ImVec2(0.f, 490.f), ImGuiChildFlags_Border, child_flags);

	if (child_is_visible)
	{
		if (m_Texture)
		{
			ImVec4 bg_col = ImVec4(.196f, .196f, .196f, 1.0f);
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


			for (int i = 0; i < m_Anim.size(); i++)
			{
				ImGui::PushID(i);
				if (m_bPlay && i == m_iCurrent_Select_Image)
				{
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05882f, 0.52941f, 0.98039f, 1.0f));
				}

				if (ImGui::ImageButton((void*)(m_Texture->GetSRV().Get()), m_Anim[i].vImageSize,
					m_Anim[i].vImageLtUV, m_Anim[i].vImageRbUV, -1, bg_col, tint_col))
				{
					m_iCurrent_Select_Image = i;
				}

				if (m_bPlay && i == m_iCurrent_Select_Image)
					ImGui::PopStyleColor(1);

				ImGui::PopID();
				ImGui::SameLine();
			}
		}
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::PopID();

	if (ImGui::Button("Texture Grid FullScreen##Texture Grid FullScreen Btns", ImVec2(200, 20)))
	{
		AnimatorFullGridUI* pAnimFullGrid = (AnimatorFullGridUI*)CImGuiMgr::GetInst()->FindUI("##AnimatorFullGridUI");
		pAnimFullGrid->Activate();
	}
	ImGui::SameLine();
}

void AnimatorEditorUI::AnimationFrameEditBtns()
{
	ImGui::SameLine();
	ImGui::Text("                                                                                              ");
	ImGui::SameLine();
	ImGui::Text("Current Select Image : %d ", m_iCurrent_Select_Image);
	ImGui::SameLine();
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##sequenceleft", ImGuiDir_Left) && m_iCurrent_Select_Image > 0)
	{
		std::swap(m_Anim[m_iCurrent_Select_Image], m_Anim[m_iCurrent_Select_Image - 1]);
		m_iCurrent_Select_Image--;
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##sequenceright", ImGuiDir_Right) && m_iCurrent_Select_Image < m_Anim.size() - 1)
	{
		std::swap(m_Anim[m_iCurrent_Select_Image], m_Anim[m_iCurrent_Select_Image + 1]);
		m_iCurrent_Select_Image++;
	}
	ImGui::PopButtonRepeat();




	ImGui::SameLine();
	if (ImGui::Button("Delete Frame##Delete Frame Btns", ImVec2(130.f, 20.f)))
	{
		m_Anim.erase(m_Anim.begin() + m_iCurrent_Select_Image);
	}

}

void AnimatorEditorUI::AnimationPreview()
{
	ImVec2 m_vAnimPanelLT = m_vGridLeftTop + m_vAnimPanlePos;

	ImVec2 m_vAnimPanleRB = ImVec2(m_vAnimPanelLT.x + m_vAnimPanelSize.x, m_vAnimPanelLT.y + m_vAnimPanelSize.y);

	// 테두리와 배경색을 그립니다.
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	// 배경색
	draw_list->AddRectFilled(m_vAnimPanelLT, m_vAnimPanleRB, IM_COL32(50, 50, 50, 255));
	// 테두리
	draw_list->AddRect(m_vAnimPanelLT - ImVec2(1.f, 1.f), m_vAnimPanleRB + ImVec2(1.f, 1.f), IM_COL32(255, 255, 255, 255));

	// 캔버스에 그리드 + 모든 선을 그립니다
	draw_list->PushClipRect(m_vAnimPanelLT, m_vAnimPanleRB, true);


	if (m_Texture && !m_Anim.size() <= 0)
	{

		ImVec2 vMaxSize = ImVec2(m_Anim[m_iCurrent_Select_Image].vSlice.x - m_Anim[m_iCurrent_Select_Image].vLeftTop.x, m_Anim[m_iCurrent_Select_Image].vSlice.y - m_Anim[m_iCurrent_Select_Image].vLeftTop.y);

		//frm.vOffset = Vec2(_vOffset.x / (float)_Atlas->GetWidth(), _vOffset.y / (float)_Atlas->GetHeight());
		ImVec2 OffsetUV = ImVec2(m_Anim[m_iCurrent_Select_Image].vOffset.x / m_Texture->GetWidth(), m_Anim[m_iCurrent_Select_Image].vOffset.y / m_Texture->GetHeight());
		ImVec2 Offset = ImVec2(m_Anim[m_iCurrent_Select_Image].vOffset.x , m_Anim[m_iCurrent_Select_Image].vOffset.y);

		ImVec2 vPanelLT = ImVec2(((m_vAnimPanelSize.x) / 2.f) - ((m_Anim[m_iCurrent_Select_Image].vSlice.x - m_Anim[m_iCurrent_Select_Image].vLeftTop.x + Offset.x) / 2.f),
			(m_vAnimPanelSize.y / 2.f) - ((m_Anim[m_iCurrent_Select_Image].vSlice.y - m_Anim[m_iCurrent_Select_Image].vLeftTop.y + Offset.y) / 2.f));


		draw_list->AddImage((void*)(m_Texture->GetSRV().Get()), m_vAnimPanelLT + vPanelLT, vMaxSize + m_vAnimPanelLT + vPanelLT, m_Anim[m_iCurrent_Select_Image].vImageLtUV, m_Anim[m_iCurrent_Select_Image].vImageRbUV);
	}

	// GRID 라인 그리기
	const float GRID_STEP = m_vAnimPanelSize.x / 2.f;
	for (float x = GRID_STEP; x < m_vAnimPanelSize.x; x += GRID_STEP)
		draw_list->AddLine(ImVec2(m_vAnimPanelLT.x + x, m_vAnimPanelLT.y), ImVec2(m_vAnimPanelLT.x + x, m_vAnimPanleRB.y), IM_COL32(0, 255, 0, 255));
	for (float y = GRID_STEP; y < m_vAnimPanelSize.y; y += GRID_STEP)
		draw_list->AddLine(ImVec2(m_vAnimPanelLT.x, m_vAnimPanelLT.y + y), ImVec2(m_vAnimPanleRB.x, m_vAnimPanelLT.y + y), IM_COL32(0, 255, 0, 255));


	draw_list->PopClipRect();
}

void AnimatorEditorUI::AltasImageOnGrid(ImGuiIO& _io)
{
	m_vGridLeftTop = ImGui::GetCursorScreenPos();
	ImVec2 canvas_p1 = ImVec2(m_vGridLeftTop.x + m_vGridSize.x, m_vGridLeftTop.y + m_vGridSize.y);

	// 테두리와 배경색을 그립니다.
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	// 배경색
	draw_list->AddRectFilled(m_vGridLeftTop, canvas_p1, IM_COL32(50, 50, 50, 255));
	// 테두리
	draw_list->AddRect(m_vGridLeftTop - ImVec2(1.f, 1.f), canvas_p1 + ImVec2(1.f, 1.f), IM_COL32(255, 255, 255, 255));

	// 이것은 우리의 상호작용을 포착할 것입니다
	ImGui::InvisibleButton("GridinvisibleButton##GridinvisibleButton", m_vGridSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_active = ImGui::IsItemActive();

	// MouseWheel에 따른 Texture Size 조정
	//SetTextureSize(_io);

	// 마우스 우클릭 드래그에 따라 Grid 이동
	if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		m_vScrolling.x += _io.MouseDelta.x;
		m_vScrolling.y += _io.MouseDelta.y;
	}

	// 캔버스에 그리드 + 모든 선을 그립니다
	draw_list->PushClipRect(m_vGridLeftTop, canvas_p1, true);

	// GRID 라인 그리기

	float GRID_STEP = 32.f;
	if (m_fCurMouseWheel > 0)
	{
		GRID_STEP = (32.f * ((10.f + m_fCurMouseWheel) / 10.f));
	}
	else if (m_fCurMouseWheel < 0)
	{
		GRID_STEP = (32.f / ((10.f + abs(m_fCurMouseWheel)) / 10.f));
	}
	for (float x = fmodf(m_vScrolling.x, GRID_STEP); x < m_vGridSize.x; x += GRID_STEP)
		draw_list->AddLine(ImVec2(m_vGridLeftTop.x + x, m_vGridLeftTop.y), ImVec2(m_vGridLeftTop.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
	for (float y = fmodf(m_vScrolling.y, GRID_STEP); y < m_vGridSize.y; y += GRID_STEP)
		draw_list->AddLine(ImVec2(m_vGridLeftTop.x, m_vGridLeftTop.y + y), ImVec2(canvas_p1.x, m_vGridLeftTop.y + y), IM_COL32(200, 200, 200, 40));



	if (m_Texture)
	{
		draw_list->AddImage((void*)(m_Texture->GetSRV().Get()),
			ImVec2(ImGui::GetWindowPos().x + m_vScrolling.x, ImGui::GetWindowPos().y + m_vScrolling.y),
			ImVec2(ImGui::GetWindowPos().x + m_vTextureSize.x + m_vScrolling.x, ImGui::GetWindowPos().y + m_vTextureSize.y + m_vScrolling.y));

		draw_list->AddRect(ImVec2(ImGui::GetWindowPos().x + m_vScrolling.x, ImGui::GetWindowPos().y + m_vScrolling.y),
			ImVec2(ImGui::GetWindowPos().x + m_vTextureSize.x + m_vScrolling.x, ImGui::GetWindowPos().y + m_vTextureSize.y + m_vScrolling.y), IM_COL32(255, 255, 255, 255));


	}

	SliceRectrender(draw_list);

	draw_list->PopClipRect();
}

void AnimatorEditorUI::SliceRectrender(ImDrawList* _drawlist)
{
	if (m_bSliceRectReset)
		return;

	for (int i = 0; i < m_vSliceRect.size(); ++i)
	{
		ImVec4 vSelectColor = { 255.f ,255.f , 0.f , 255.f };

		// Rect 선택시 색상 변경
		if (i == m_iCurSliceRect)
		{
			_drawlist->AddRect(ImVec2(m_vSliceRect[i].x + WSZ.x + SCL.x, m_vSliceRect[i].y + WSZ.y + SCL.y),
				ImVec2(m_vSliceRect[i].z + WSZ.x + SCL.x, m_vSliceRect[i].w + WSZ.y + SCL.y),
				ImGui::GetColorU32(vSelectColor));   // Border
		}
		else
		{
			_drawlist->AddRect(ImVec2(m_vSliceRect[i].x + WSZ.x + SCL.x, m_vSliceRect[i].y + WSZ.y + SCL.y),
				ImVec2(m_vSliceRect[i].z + WSZ.x + SCL.x, m_vSliceRect[i].w + WSZ.y + SCL.y),
				ImGui::GetColorU32(IM_COL32(0, 255, 0, 255)));   // Border
		}
	}

}

void AnimatorEditorUI::EditorStatus()
{
	ImGui::Text("StartPos (%f , %f)", m_vStartMousePos.x, m_vStartMousePos.y);
	//ImGui::SameLine();
	//ImGui::Text("uv0 = (%f, %f)", m_vAnimLtUV.x, m_vAnimLtUV.y);
	ImGui::SameLine();
	ImGui::Text("scrolling = (%f, %f)", m_vScrolling.x, m_vScrolling.y);
	ImGui::SameLine();
	ImGui::Text("TextureSize = (%f, %f)", m_vTextureSize.x, m_vTextureSize.y);
	ImGui::SameLine();
	ImGui::Text("m_vCurMousePos = (%f, %f)", m_vCurMousePos.x, m_vCurMousePos.y);
	ImGui::SameLine();
	if (m_vSliceRect.size() > 0)
		ImGui::Text("SliceRect = (%f, %f, %f, %f)", m_vSliceRect[m_iCurSliceRect].x + SCL.x + WSZ.x,
			m_vSliceRect[m_iCurSliceRect].y + SCL.y + WSZ.y,
			m_vSliceRect[m_iCurSliceRect].z + SCL.x + WSZ.x,
			m_vSliceRect[m_iCurSliceRect].w + SCL.y + WSZ.y);

	ImGui::SameLine();
	ImGui::Text("m_EditorMode = (%d)", (int)m_EditorMode);

	ImGui::Text("EndPos (%f , %f)", m_vEndMousePos.x, m_vEndMousePos.y);
}

void AnimatorEditorUI::AnimationSaveLoadBtns()
{
	ImGui::SameLine();
	ImGui::Text("                                                ");
	ImGui::SameLine();
	if (ImGui::Button("Reset Animation##Reset Animation Btn", ImVec2(130, 20)))
	{
		ResetAnimation();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Animation##Load Animation Btn", ImVec2(130, 20)))
	{
		LoadAnimation();
	}
	ImGui::SameLine();
	if (ImGui::Button("Save Animation##Save Animation Btn", ImVec2(130, 20)))
	{
		SaveFile();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load META##Load META", ImVec2(130, 20)))
	{
		ApplyOffset();
	}
}

void AnimatorEditorUI::ApplyOffset()
{
	OpenFileDialog(m_FileName);

	for (int i = 0; i < m_FileName.size(); ++i)
	{
		
		m_Anim[i].vOffset = LoadMeta(m_FileName[i]);
	}
	m_FileName.clear();
}

void AnimatorEditorUI::OpenFileDialog(vector<wstring>& _FilesName)
{
	IFileOpenDialog* pFileDialog;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileDialog));
	if (FAILED(hr))
	{
		std::cerr << "Failed to create FileOpenDialog instance" << std::endl;
		return;
	}

	// 다중 선택 가능 설정
	DWORD dwOptions;
	hr = pFileDialog->GetOptions(&dwOptions);
	if (SUCCEEDED(hr))
	{
		hr = pFileDialog->SetOptions(dwOptions | FOS_ALLOWMULTISELECT);
	}

	if (SUCCEEDED(hr))
	{
		// 원하는 초기 디렉토리 경로를 여기에 설정
		wstring MetaPath = CPathMgr::GetContentPath();
		MetaPath += L"meta";

		PWSTR initialDir = (PWSTR)(MetaPath.c_str());

		IShellItem* pInitialDirItem;

		hr = SHCreateItemFromParsingName(initialDir, NULL, IID_IShellItem, reinterpret_cast<void**>(&pInitialDirItem));

		// 파일 대화 상자 인터페이스에 초기 디렉토리 설정
		hr = pFileDialog->SetFolder(pInitialDirItem);
	}

	// 파일 필터 설정
	COMDLG_FILTERSPEC fileTypes[] = { {L"All Files", L"*.*"}, {L"Text Files", L"*.txt"}, {L"FBX Files", L"*.fbx"} };
	hr = pFileDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
	if (FAILED(hr))
	{
		std::cerr << "Failed to set file types" << std::endl;
		pFileDialog->Release();
		return;
	}

	// 대화 상자 열기
	hr = pFileDialog->Show(NULL);
	if (FAILED(hr))
	{
		std::cerr << "Failed to open FileOpenDialog" << std::endl;
		pFileDialog->Release();
		return;
	}

	// 선택된 파일 목록 가져오기
	IShellItemArray* pItems;
	hr = pFileDialog->GetResults(&pItems);
	if (FAILED(hr))
	{
		std::cerr << "Failed to get selected items" << std::endl;
		pFileDialog->Release();
		return;
	}

	// 선택된 파일들의 경로 가져오기
	DWORD itemCount;
	hr = pItems->GetCount(&itemCount);
	if (SUCCEEDED(hr))
	{
		for (DWORD i = 0; i < itemCount; ++i)
		{
			IShellItem* pItem;
			hr = pItems->GetItemAt(i, &pItem);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
				if (SUCCEEDED(hr))
				{
					_FilesName.push_back(pszFilePath);
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
	}
	pItems->Release();
	pFileDialog->Release();
	
}

ImVec2 AnimatorEditorUI::LoadMeta(const wstring& _strMetaRelativePath)
{
	ImVec2 retVec = { -1, -1 };
	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, (_strMetaRelativePath).c_str(), L"r");
	
	if (nullptr == pFile)
	{
		MessageBoxA(nullptr, "Meta 파일이 존재하지 않습니다.", "Meta File No Exist!", MB_OK);
		return {};
	}
	
	// Animation 이름 로드
	
	while (true)
	{
		wchar_t szRead[256] = {};
		float tmpfloat = -1.f;
	
		if (EOF == fwscanf_s(pFile, L"%s", szRead, 256))
		{
			break;
		}
	
		if (!wcscmp(szRead, L"m_Offset:"))
		{
			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);
	
				if (!wcscmp(szRead, L"{x:"))
				{
					fwscanf_s(pFile, L"%f", &retVec.x);
					retVec.x *= -1;
				}
				if (!wcscmp(szRead, L"y:"))
				{
					fwscanf_s(pFile, L"%s", szRead, 256);
	
					int length = (int)wcslen(szRead);
	
					// 끝에 한글자 잘라야됨 1.24} 라고 되어있음
					if (length > 0)
					{
						szRead[length - 1] = '\0';
					}
	
					wchar_t* end;
					float tmp = wcstof(szRead, &end);
	
					if (*end == L'\0')
					{
						retVec.y = tmp;
					}
	
					return retVec;
				}
	
				// 탈출 조건
				if (!wcscmp(szRead, L"m_Border:"))
				{
					break;
				}
			}
		}
		// 탈출 조건
		if (!wcscmp(szRead, L"m_Border:"))
			break;
	}
	
	fclose(pFile);
	
	return retVec;
	
}

void AnimatorEditorUI::LoadTexture()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};



	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetMainWind();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	//ofn.lpstrFilter = L"anim\0*. *\0Tile\0*.tile\0";	// 고쳐야함
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;



	wstring strTextureFolder = CPathMgr::GetContentPath();
	strTextureFolder += L"texture";


	ofn.lpstrInitialDir = strTextureFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 파일 열기
	if (GetOpenFileName(&ofn))
	{
		// LoadTile은 다른 Scene에서도 사용하기에 기본 함수는 상대경로를 사용하게한다.
		wstring strRelativePath = CPathMgr::GetRelativePath(szName);
		Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(strRelativePath, strRelativePath);

		m_Texture = pTex.Get();
		m_vTextureSize.x = pTex->GetWidth();
		m_vTextureSize.y = pTex->GetHeight();
		m_vTextureOriginSize.x = pTex->GetWidth();
		m_vTextureOriginSize.y = pTex->GetHeight();
	}
}

void AnimatorEditorUI::LoadAnimation()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetMainWind();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"anim\0*";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();
	//strAnimationFolder += L"animation";


	ofn.lpstrInitialDir = strAnimationFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;



	// 파일 열기
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetRelativePath(szName);
		strAnimationFolder += strRelativePath;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, strAnimationFolder.c_str(), L"rb");
		assert(pFile);



		// Animation의 이름을 읽어온다.
		string str;
		char szBuff[256] = {};

		// Animation Name이 읽힘
		FScanf(szBuff, pFile);
		// 경로 정보가 읽힌다.
		FScanf(szBuff, pFile);
		str = szBuff;

		m_strName = string(str.begin(), str.end());


		// 참조하는 텍스쳐 이름 및 경로
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);

		str = szBuff;
		wstring strTexKey = wstring(str.begin(), str.end());


		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);

		str = szBuff;
		wstring strTexPath = wstring(str.begin(), str.end());


		Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(strTexKey, strTexPath);
		m_Texture = pTex.Get();
		m_vTextureSize.x = pTex->GetWidth();
		m_vTextureSize.y = pTex->GetHeight();
		m_vTextureOriginSize.x = pTex->GetWidth();
		m_vTextureOriginSize.y = pTex->GetHeight();

		// 프레임 개수
		FScanf(szBuff, pFile);
		int iFrameCount = 0;
		fscanf_s(pFile, "%d", &iFrameCount);

		// 모든 프레임 정보
		tAnim frm = {};
		for (int i = 0; i < iFrameCount; ++i)
		{
			POINT pt = {};

			while (true)
			{
				FScanf(szBuff, pFile);


				if (!strcmp("[Frame Index]", szBuff))
				{
					fscanf_s(pFile, "%d", &pt.x);
				}
				else if (!strcmp("[Left Top]", szBuff))
				{
					fscanf_s(pFile, "%d", &pt.x);
					fscanf_s(pFile, "%d", &pt.y);

					frm.vLeftTop = ImVec2(pt.x, pt.y);
				}
				else if (!strcmp("[Slice Top]", szBuff))
				{
					fscanf_s(pFile, "%d", &pt.x);
					fscanf_s(pFile, "%d", &pt.y);

					frm.vSlice = ImVec2(pt.x + frm.vLeftTop.x, pt.y + frm.vLeftTop.y);
				}
				else if (!strcmp("[Offset]", szBuff))
				{
					fscanf_s(pFile, "%d", &pt.x);
					fscanf_s(pFile, "%d", &pt.y);

					frm.vOffset = ImVec2(pt.x, pt.y);
				}
				else if (!strcmp("[fDruation]", szBuff))
				{
					fscanf_s(pFile, "%f", &frm.fDuration);
				}
				else if (!strcmp("[Background]", szBuff))
				{
					fscanf_s(pFile, "%d", &pt.x);
					fscanf_s(pFile, "%d", &pt.y);

					frm.vBackground = ImVec2(pt.x, pt.y);
				}
				else if (!strcmp("[PrevOffset]", szBuff))
				{
					fscanf_s(pFile, "%f", &frm.vPrevOffset.x);
					fscanf_s(pFile, "%f", &frm.vPrevOffset.y);
				}
				else if (!strcmp("[vImageSize]", szBuff))
				{
					fscanf_s(pFile, "%f", &frm.vImageSize.x);
					fscanf_s(pFile, "%f", &frm.vImageSize.y);
				}
				else if (!strcmp("[vImageLtUV]", szBuff))
				{
					fscanf_s(pFile, "%f", &frm.vImageLtUV.x);
					fscanf_s(pFile, "%f", &frm.vImageLtUV.y);
				}
				else if (!strcmp("[vImageRbUV]", szBuff))
				{
					fscanf_s(pFile, "%f", &frm.vImageRbUV.x);
					fscanf_s(pFile, "%f", &frm.vImageRbUV.y);
					break;
				}
			}

			m_Anim.push_back(frm);
		}

		fclose(pFile);

	}
}



void AnimatorEditorUI::SaveAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = _strRelativePath; // = CPathMgr::GetContentPath();


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	// 나중에 저장한 이름 = key값이 되게 바꿔야함
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");


	// Animation 이 사용하는 텍스쳐
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_Texture->GetKey().begin(), m_Texture->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_Texture->GetRelativePath().begin(), m_Texture->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");


	// 프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_Anim.size());

	ImVec2 vMaxImageSize = {};
	for (size_t i = 0; i < m_Anim.size(); ++i)
	{
		if (vMaxImageSize.x < m_Anim[i].vImageSize.x)
			vMaxImageSize.x = m_Anim[i].vImageSize.x;
		if (vMaxImageSize.y < m_Anim[i].vImageSize.y)
			vMaxImageSize.y = m_Anim[i].vImageSize.y;
	}

	for (size_t i = 0; i < m_Anim.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_Anim[i].vLeftTop.x, (int)m_Anim[i].vLeftTop.y);

		fprintf(pFile, "[Slice Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_Anim[i].vSlice.x - (int)m_Anim[i].vLeftTop.x, (int)m_Anim[i].vSlice.y - (int)m_Anim[i].vLeftTop.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_Anim[i].vOffset.x, (int)m_Anim[i].vOffset.y);

		fprintf(pFile, "[fDruation]\n");
		fprintf(pFile, "%f\n", m_Anim[i].fDuration);

		fprintf(pFile, "[Background]\n");
		m_Anim[i].vBackground = ImVec2(vMaxImageSize.x + 200.f, vMaxImageSize.y + 200.f);
		fprintf(pFile, "%d %d\n", (int)m_Anim[i].vBackground.x, (int)m_Anim[i].vBackground.y);

		fprintf(pFile, "[Tool Only information]\n\n");

		fprintf(pFile, "[PrevOffset]\n");
		fprintf(pFile, "%d %d\n", (int)m_Anim[i].vPrevOffset.x, (int)m_Anim[i].vPrevOffset.y);

		fprintf(pFile, "[vImageSize]\n");
		fprintf(pFile, "%f %f\n", m_Anim[i].vImageSize.x, m_Anim[i].vImageSize.y);

		fprintf(pFile, "[vImageLtUV]\n");
		fprintf(pFile, "%f %f\n", m_Anim[i].vImageLtUV.x, m_Anim[i].vImageLtUV.y);

		fprintf(pFile, "[vImageRbUV]\n");
		fprintf(pFile, "%f %f\n", m_Anim[i].vImageRbUV.x, m_Anim[i].vImageRbUV.y);

		fprintf(pFile, "\n\n");
	}

	// 모든 프레임 정보
	fwrite(m_Anim.data(), sizeof(m_Anim), 1, pFile);

	fclose(pFile);
}



void AnimatorEditorUI::SaveFile()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	// 구조체 사이즈
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetMainWind();
	// 저장될 경로
	ofn.lpstrFile = szName;
	// 배열의 크기
	ofn.nMaxFile = sizeof(szName);
	// 문자열 필터
	ofn.lpstrFilter = L"anim\0*";
	// 초기 필터
	ofn.nFilterIndex = 0;
	// 타이틀
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();
	strAnimationFolder += L"animation";

	// 초기 경로
	ofn.lpstrInitialDir = strAnimationFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal 방식
	// 반환값으로 저장시 true, 취소시 false반환
	if (GetSaveFileName(&ofn))
	{
		SaveAnimation(szName);
	}

}



void AnimatorEditorUI::PlayAnimation()
{
	m_fAccTime += DT_ENGINE;

	if (m_Anim[m_iCurrent_Select_Image].fDuration < m_fAccTime)
	{
		++m_iCurrent_Select_Image;
		if (m_Anim.size() <= m_iCurrent_Select_Image)
		{
			if (m_bLoop)
			{
				m_iCurrent_Select_Image = 0;
			}
			else
			{
				m_bPlay = false;
				return;
			}
		}
		m_fAccTime = 0.f;
	}
}

void AnimatorEditorUI::ResetAnimation()
{
	m_Texture = nullptr;
	m_vTextureSize = ImVec2(0.f, 0.f);
	m_vTextureOriginSize = ImVec2(0.f, 0.f);
	m_vStartMousePos = ImVec2(0.f, 0.f);
	m_vGridLeftTop = ImVec2(0.f, 0.f);
	m_vEndMousePos = ImVec2(0.f, 0.f);
	m_vScrolling = ImVec2(0.f, 0.f);

	m_strName = { "DefaultName" };

	SetEditorMode(EDITOR_MODE::NONE);
	m_bSliceRectReset = false;
	m_bPlay = false;
	m_bLoop = true;

	m_fAccTime = 0.f;
	m_fCurMouseWheel = 0.f;
	m_fPrevMouseWheel = 0.f;

	m_Anim.clear();
	m_iCurrent_Select_Image = 0;
	m_iFPS = 10;
}

void AnimatorEditorUI::SetTextureSize(ImGuiIO& _io)
{
	// 기본 0.f로 wheel설정되어있음
	// wheel 최대 ~ 최소값 100 ~ -100 (보정으로 90 ~ -90)
	if (m_fCurMouseWheel <= 90.f && m_fCurMouseWheel >= -90.f)
	{
		m_fCurMouseWheel += _io.MouseWheel;

		if (m_fCurMouseWheel > 90.f)
			m_fCurMouseWheel = 90.f;
		else if (m_fCurMouseWheel < -90.f)
			m_fCurMouseWheel = -90.f;
	}



	if (m_fCurMouseWheel != m_fPrevMouseWheel)
	{
		// Texture size는 -10.0배 ~ 10.0배까지 조정가능하게할것
		if (m_fCurMouseWheel > 0)
		{
			m_vTextureSize = (m_vTextureOriginSize * ((10.f + m_fCurMouseWheel) / 10.f));
		}
		else if (m_fCurMouseWheel < 0)
		{
			m_vTextureSize = (m_vTextureOriginSize / ((10.f + abs(m_fCurMouseWheel)) / 10.f));
		}
	}

	m_fPrevMouseWheel = m_fCurMouseWheel;
}

void AnimatorEditorUI::AddToSprite(vector<tAnim>& _Anim)
{
	tAnim _tAnim;

	{
		_tAnim.vLeftTop = ImVec2(m_vSliceRect[m_iCurSliceRect].x, m_vSliceRect[m_iCurSliceRect].y);
		_tAnim.vSlice = ImVec2(m_vSliceRect[m_iCurSliceRect].z, m_vSliceRect[m_iCurSliceRect].w);
		_tAnim.vOffset = ImVec2(0.f, 0.f);

		_tAnim.vImageSize = ImVec2(_tAnim.vSlice.x - _tAnim.vLeftTop.x, _tAnim.vSlice.y - _tAnim.vLeftTop.y);
		_tAnim.vImageLtUV = ImVec2(_tAnim.vLeftTop.x / m_vTextureSize.x, _tAnim.vLeftTop.y / m_vTextureSize.y);
		_tAnim.vImageRbUV = ImVec2(_tAnim.vSlice.x / m_vTextureSize.x, _tAnim.vSlice.y / m_vTextureSize.y);
		_tAnim.fDuration = 1.f;
	}




	_Anim.push_back(_tAnim);
}

void AnimatorEditorUI::SliceRectEdit()
{
	if (m_vSliceRect.size() <= 0)
		return;


	SetMouseCursorState(m_CurMouseCursor, m_iCurSliceRect, m_vCurMousePos);

	if (KEY_PRESSED(KEY::LBTN))
		SetMouseState(m_CurMouseState, m_CurMouseCursor);
	else if (KEY_RELEASED(KEY::LBTN))
		SetCurMouseState(MOUSE_STATE::KEY_RELEASE);


	switch (m_CurMouseState)
	{
	case MOUSE_STATE::KEY_PRESSED:
	{
		switch (m_CurMouseCursor)
		{
		case MOUSE_CURSOR_STATE::ARROW:
			break;
		case MOUSE_CURSOR_STATE::RESIZE_LEFT:
			m_vSliceRect[m_iCurSliceRect].x += (m_vCurMousePos.x - m_vPrevMousePos.x);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_RIGHT:
			m_vSliceRect[m_iCurSliceRect].z += (m_vCurMousePos.x - m_vPrevMousePos.x);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_UP:
			m_vSliceRect[m_iCurSliceRect].y += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_DOWN:
			m_vSliceRect[m_iCurSliceRect].w += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_LEFTTOP:
			m_vSliceRect[m_iCurSliceRect].x += (m_vCurMousePos.x - m_vPrevMousePos.x);
			m_vSliceRect[m_iCurSliceRect].y += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_LEFTBOTTOM:
			m_vSliceRect[m_iCurSliceRect].x += (m_vCurMousePos.x - m_vPrevMousePos.x);
			m_vSliceRect[m_iCurSliceRect].w += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_RIGHTTOP:
			m_vSliceRect[m_iCurSliceRect].z += (m_vCurMousePos.x - m_vPrevMousePos.x);
			m_vSliceRect[m_iCurSliceRect].y += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		case MOUSE_CURSOR_STATE::RESIZE_RIGHTBOTTOM:
			m_vSliceRect[m_iCurSliceRect].z += (m_vCurMousePos.x - m_vPrevMousePos.x);
			m_vSliceRect[m_iCurSliceRect].w += (m_vCurMousePos.y - m_vPrevMousePos.y);
			break;
		default:
			break;
		}
		break;
	}
	case MOUSE_STATE::KEY_RELEASE:
	{
		break;
	}
	case MOUSE_STATE::KEY_NONE:
		break;
	default:
		break;
	}

	m_prevMouseState = m_CurMouseState;
}

void AnimatorEditorUI::SliceRectSelect(int& _CurSliceRect, const ImVec2 _CurMousePos)
{
	if (!(_CurMousePos.x > m_vGridLeftTop.x &&
		_CurMousePos.y > m_vGridLeftTop.y &&
		_CurMousePos.x < m_vGridLeftTop.x + m_vGridSize.x &&
		_CurMousePos.y < m_vGridLeftTop.y + m_vGridSize.y))
	{
		return;
	}

	for (int i = 0; i < m_vSliceRect.size(); ++i)
	{
		if (m_vSliceRect[i].x + SCL.x + WSZ.x <= _CurMousePos.x &&
			m_vSliceRect[i].y + SCL.y + WSZ.y <= _CurMousePos.y &&
			m_vSliceRect[i].z + SCL.x + WSZ.x >= _CurMousePos.x &&
			m_vSliceRect[i].w + SCL.y + WSZ.y >= _CurMousePos.y)
		{
			if (i != _CurSliceRect)
				ChangeMouseCursor(MOUSE_CURSOR_STATE::SELECT);

			if (KEY_TAP(KEY::LBTN))
			{
				_CurSliceRect = i;
			}
		}
	}
}

void AnimatorEditorUI::SliceRectMove(int& _CurSliceRect, const ImVec2 _CurMousePos, const ImVec2 _PrevMousePos)
{
	if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y >= _CurMousePos.y)
	{
		ChangeMouseCursor(MOUSE_CURSOR_STATE::MOVE);

		if (KEY_PRESSED(KEY::LBTN))
		{
			m_vSliceRect[_CurSliceRect].x += (_CurMousePos.x - _PrevMousePos.x);
			m_vSliceRect[_CurSliceRect].y += (_CurMousePos.y - _PrevMousePos.y);
			m_vSliceRect[_CurSliceRect].z += (_CurMousePos.x - _PrevMousePos.x);
			m_vSliceRect[_CurSliceRect].w += (_CurMousePos.y - _PrevMousePos.y);
		}
	}
}

void AnimatorEditorUI::SetMouseCursorState(MOUSE_CURSOR_STATE& _CurMouseCursor, int& _CurSliceRect, const ImVec2 _CurMousePos)
{
	if (m_prevMouseState == MOUSE_STATE::KEY_PRESSED)
		return;

	if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_LEFTTOP;
	}
	else if (m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_RIGHTBOTTOM;
	}
	else if (m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_RIGHTTOP;
	}
	else if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_LEFTBOTTOM;
	}
	else if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_LEFT;
	}
	else if (m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x - 3.f <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x + 3.f >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_RIGHT;
	}
	else if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].y + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_UP;
	}
	else if (m_vSliceRect[_CurSliceRect].x + SCL.x + WSZ.x <= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y - 3.f <= _CurMousePos.y &&
		m_vSliceRect[_CurSliceRect].z + SCL.x + WSZ.x >= _CurMousePos.x &&
		m_vSliceRect[_CurSliceRect].w + SCL.y + WSZ.y + 3.f >= _CurMousePos.y)
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::RESIZE_DOWN;
	}
	else
	{
		_CurMouseCursor = MOUSE_CURSOR_STATE::ARROW;
	}

	ChangeMouseCursor(_CurMouseCursor);
}

void AnimatorEditorUI::SetMouseState(MOUSE_STATE& CurMouseState, MOUSE_CURSOR_STATE& _CurMouseCursor)
{
	switch (_CurMouseCursor)
	{
	case MOUSE_CURSOR_STATE::ARROW:
	{
		CurMouseState = MOUSE_STATE::KEY_NONE;
		break;
	}
	case MOUSE_CURSOR_STATE::RESIZE_LEFT:
	case MOUSE_CURSOR_STATE::RESIZE_RIGHT:
	case MOUSE_CURSOR_STATE::RESIZE_UP:
	case MOUSE_CURSOR_STATE::RESIZE_DOWN:
	case MOUSE_CURSOR_STATE::RESIZE_LEFTTOP:
	case MOUSE_CURSOR_STATE::RESIZE_LEFTBOTTOM:
	case MOUSE_CURSOR_STATE::RESIZE_RIGHTTOP:
	case MOUSE_CURSOR_STATE::RESIZE_RIGHTBOTTOM:
	{
		CurMouseState = MOUSE_STATE::KEY_PRESSED;
		break;
	}
	default:
		break;
	}

}

void AnimatorEditorUI::ChangeMouseCursor(MOUSE_CURSOR_STATE _CurMouseCursor)
{
	switch (_CurMouseCursor)
	{
	case MOUSE_CURSOR_STATE::ARROW:
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		break;
	case MOUSE_CURSOR_STATE::RESIZE_LEFT:
	case MOUSE_CURSOR_STATE::RESIZE_RIGHT:
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
		break;
	case MOUSE_CURSOR_STATE::RESIZE_UP:
	case MOUSE_CURSOR_STATE::RESIZE_DOWN:
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
		break;
	case MOUSE_CURSOR_STATE::RESIZE_RIGHTTOP:
	case MOUSE_CURSOR_STATE::RESIZE_LEFTBOTTOM:
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
		break;
	case MOUSE_CURSOR_STATE::RESIZE_LEFTTOP:
	case MOUSE_CURSOR_STATE::RESIZE_RIGHTBOTTOM:
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
		break;
	case MOUSE_CURSOR_STATE::SELECT:
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		break;
	case MOUSE_CURSOR_STATE::MOVE:
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
		break;
	default:
		break;
	}
}



