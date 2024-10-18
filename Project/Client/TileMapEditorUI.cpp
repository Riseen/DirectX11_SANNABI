#include "pch.h"
#include "TileMapEditorUI.h"
#include "TileMapUI.h"
#include "Inspector.h"

#include <Engine/CEngine.h>
#include <Engine/CGameObject.h>
#include <Engine/CTileMap.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CTransform.h>
#include <Engine/CCollider2D.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

#include <Scripts/CTileColScript.h>


// TileMap

// 16 * 16 픽셀로 이루어질예정
// 가로 세로값 원하는만큼 늘어나기							o
// 픽셀 가로 세로값 (RenderSize)도 원하는 만큼 늘어나기		o 

// 이미지 버튼으로 이루어진 타일이미지 선택해서
// Combo박스에서 모드선택후 타일클릭시 타일이 그이미지로 바뀜		o
// 타일 삭제	, 지우개 타일도 있음									o

// 고민 많이 해봐야할 기술 
// 가로 세로값 늘리기할때 본래의 타일 그대로 유지				o
// 확대 & 축소												o
// 충돌체 추가	- 물리테스트후 추가예정
// 타일 채우기												o
// 렌더링 최적화 -											o
// 되돌리기
// 전체삭제 - 이건실수할수있으니 생각해보고 넣음

// 이것들이 Level에 있는 실제 타일객체와 그대로 연동되야함      o


// 현재 설정
// Grid Tile 그리기 (그리기, 이미지 있으면 그리기등) 
// -> ImageButton Tile 그리기 (옵션조정버튼, 이미지버튼)
// -> 변경점있으면 변경점 타일에 세팅
// -> 실제 타일이랑연동
// -> 타일 조작

// 주의점
// 0번 타일은 지우개타일임 나중에 0번타일은 지우개모양으로 넣던가하는게좋을듯





TileMapEditorUI::TileMapEditorUI()
	: UI("TileMapEditorUI", "##TileMapEditorUI")
	, m_Texture(nullptr)
	, m_PrevTexture(nullptr)
	, m_CurEditorState(TILEEDITORSTATE::NONE)
	, m_vGridSize{ 900.f, 700.f }
	, m_vScrolling{}
	, m_vRenderSize{}
	, m_vPrevRenderSize{}
	, m_Face{}
	, m_PrevFace{}
	, m_iCurTileImageIndex()
	, m_iCurGridTile{ -1,-1 }
	, m_iCurLTTile{}
	, m_iCurRBTile{}
	, m_PlusFace()
	, m_fCurMouseWheel(1.f)
	, m_fPrevMouseWheel(1.f)
	, m_bShowDebugRect(true)
	, m_bUpdateLevelTileMap(true)
	, m_iNormalTileIndex{13,14,15,16,17,18,
				     23, 24,            29, 30,
					 34,                    41,
					 45,                    52,
					 56,					63,
					 67,					74,
					 78, 79,		    84, 85,
						 90,91,92,93,94,95}

	, m_iSpecialTileIndex{112,113,114,115,116,117,118,
					 122, 123,					  129, 130,
					 133,							   141,
					 144,							   152,
					 155,							   163,
					 166,							   174,
					 177,							   185,
					 188, 189,					  195, 196,
						  200,201,202,203,204,205,206 }

	, m_iDamageTileIndex{ 222,223,224,225,226,227,228,
					 232, 233,					  239, 240,
					 243,							   251,
					 254,							   262,
					 265,							   273,
					 276,							   284,
					 287,							   295,
					 298, 299,					  305, 306,
						  310,311,312,313,314,315,316 }
{
	Deactivate();
	SetModal(false);
}

TileMapEditorUI::~TileMapEditorUI()
{


}



void TileMapEditorUI::render_update()
{
	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	CGameObject* TargetObject = pInspector->GetTargetObject();

	// 현재 선택된 Object에 TileMap이 없으면 창닫고 return
	if (!TargetObject->TileMap())
	{
		Deactivate();
		return;
	}

	//CheckTileType(1);

	if (m_Texture == nullptr)
		m_Texture = TargetObject->TileMap()->GetTileAtlas();

	ImGuiIO& io = ImGui::GetIO();


	TileMapOnGrid(io, TargetObject);

	ImGui::SameLine();
	TileMapTool(TargetObject);

	ImGui::Text("CurToolTile = %d", m_iCurTileImageIndex);
	ImGui::Text("CurGridTile = %d %d", m_iCurGridTile[0], m_iCurGridTile[1]);
	ImGui::Text("CurMouseWheel = %f", m_fCurMouseWheel);
	ImGui::Text("Scroll = %f %f", m_vScrolling.x, m_vScrolling.y);
	ImGui::Text("CurLTTile = %d %d", m_iCurLTTile[0], m_iCurLTTile[1]);
	ImGui::Text("CurRBTile = %d %d", m_iCurRBTile[0], m_iCurRBTile[1]);




	// LSHIFT를 누르면 Tile이미지 변하게
	if (KEY_PRESSED(KEY::LBTN))
	{
		EditorMode(TargetObject);
	}
}

void TileMapEditorUI::Deactivate()
{
	UI::Deactivate();
	ImGui::SetWindowFocus(nullptr);
}


void TileMapEditorUI::TileMapOnGrid(ImGuiIO& _io, CGameObject* _TargetObject)
{
	ImVec2 vGridLeftTop = ImGui::GetCursorScreenPos();
	ImVec2 canvas_p1 = ImVec2(vGridLeftTop.x + m_vGridSize.x, vGridLeftTop.y + m_vGridSize.y);

	// 테두리와 배경색을 그립니다.
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	// 배경색
	draw_list->AddRectFilled(vGridLeftTop, canvas_p1, IM_COL32(50, 50, 50, 255));
	// 테두리
	draw_list->AddRect(vGridLeftTop - ImVec2(1.f, 1.f), canvas_p1 + ImVec2(1.f, 1.f), IM_COL32(255, 255, 255, 255));

	// 상호작용 포착
	ImGui::InvisibleButton("GridinvisibleButton##GridinvisibleButton", m_vGridSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_active = ImGui::IsItemActive();

	// MouseWheel에 따른 Texture Size 조정
	if (isObjectInGrid(vGridLeftTop, ImGui::GetMousePos()))
		SetMouseWheel(_io);

	// 마우스 우클릭 드래그에 따라 Grid 이동
	if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		m_vScrolling.x += _io.MouseDelta.x;
		m_vScrolling.y += _io.MouseDelta.y;
	}

	FindLTRBTile(m_iCurLTTile, m_iCurRBTile, vGridLeftTop);

	if (m_iCurRBTile[0] <= 0 || m_iCurRBTile[1] <= 0)
		return;

	// 캔버스에 그리드 + 모든 선을 그립니다
	draw_list->PushClipRect(vGridLeftTop, canvas_p1, true);

	// GRID 라인 그리기
	float GRID_STEP = 32.f;
	for (float x = fmodf(m_vScrolling.x, GRID_STEP); x < m_vGridSize.x; x += GRID_STEP)
		draw_list->AddLine(ImVec2(vGridLeftTop.x + x, vGridLeftTop.y), ImVec2(vGridLeftTop.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
	for (float y = fmodf(m_vScrolling.y, GRID_STEP); y < m_vGridSize.y; y += GRID_STEP)
		draw_list->AddLine(ImVec2(vGridLeftTop.x, vGridLeftTop.y + y), ImVec2(canvas_p1.x, vGridLeftTop.y + y), IM_COL32(200, 200, 200, 40));


	if (m_bShowDebugRect)
	{
		for (int i = m_iCurLTTile[1]; i < m_iCurRBTile[1]; ++i)
		{
			for (int j = m_iCurLTTile[0]; j < m_iCurRBTile[0]; ++j)
			{
				if (m_iCurGridTile[0] == i && m_iCurGridTile[1] == j)
				{
					draw_list->AddRect(ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x, m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y),
						ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x + (m_vRenderSize.x * m_fCurMouseWheel), m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y + (m_vRenderSize.y * m_fCurMouseWheel)),
						ImGui::GetColorU32(IM_COL32(255, 0, 0, 255)));
				}
				else
				{
					draw_list->AddRect(ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x, m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y),
						ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x + (m_vRenderSize.x * m_fCurMouseWheel), m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y + (m_vRenderSize.y * m_fCurMouseWheel)),
						ImGui::GetColorU32(IM_COL32(255, 255, 255, 255)));
				}
			}
		}
	}



	// 현재 선택된 Tile알려주기
	for (int i = m_iCurLTTile[1]; i < m_iCurRBTile[1]; ++i)
	{
		for (int j = m_iCurLTTile[0]; j < m_iCurRBTile[0]; ++j)
		{
			if (isMouseInTile(i, j))
			{
				m_iCurGridTile[0] = i;
				m_iCurGridTile[1] = j;
			}
		}
	}

	// 마우스가 Grid를 벗어나거나 전체타일사이즈에서 벗어날경우 선택한 타일이 없게 (-1로)
	if (!(isObjectInGrid(vGridLeftTop, ImGui::GetMousePos())) || !(isMouseInTile(0, 0, m_iCurRBTile[1] - 1, m_iCurRBTile[0] - 1)))
	{
		m_iCurGridTile[0] = -1;
		m_iCurGridTile[1] = -1;
	}

	// Tile에 이미지그리기
	for (int i = m_iCurLTTile[1]; i < m_iCurRBTile[1]; ++i)
	{
		for (int j = m_iCurLTTile[0]; j < m_iCurRBTile[0]; ++j)
		{
			if (m_vTile[i][j].iTileImageIndex == 0)
				continue;

			draw_list->AddImage((void*)m_Texture->GetSRV().Get(), ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x, m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y),
				ImVec2(m_vTile[i][j].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x + (m_vRenderSize.x * m_fCurMouseWheel), m_vTile[i][j].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y + (m_vRenderSize.y * m_fCurMouseWheel)),
				ImVec2(m_vTImageBtns[m_vTile[i][j].iTileImageIndex].vImageButtonLtUV.x, m_vTImageBtns[m_vTile[i][j].iTileImageIndex].vImageButtonLtUV.y), ImVec2(m_vTImageBtns[m_vTile[i][j].iTileImageIndex].vImageButtonRbUV.x, m_vTImageBtns[m_vTile[i][j].iTileImageIndex].vImageButtonRbUV.y));
		}
	}

	draw_list->PopClipRect();
}

void TileMapEditorUI::TileMapTool(CGameObject* _TargetObject)
{
	ImVec2 TilePixelSize = ImVec2(_TargetObject->TileMap()->GetTilePixelSize().x, _TargetObject->TileMap()->GetTilePixelSize().y);


	// TileMap Tool 
	ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (false ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
	bool child_is_visible = ImGui::BeginChild(1, ImVec2(500.f, 520.f), ImGuiChildFlags_Border, child_flags);
	{
		m_vRenderSize = ImVec2(_TargetObject->TileMap()->GetTileRenderSize().x, _TargetObject->TileMap()->GetTileRenderSize().y);
		m_Face[0] = _TargetObject->TileMap()->GetFaceX();
		m_Face[1] = _TargetObject->TileMap()->GetFaceY();

		if(ImGui::Button("Save Tile##SaveTile", ImVec2(120.f, 20.f)))
		{
			SaveTileMap();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Tile##LoadTile", ImVec2(120.f, 20.f)))
		{
			LoadTileMap();
		}


		ImGui::Text("Face");
		ImGui::SameLine();
		ImGui::InputInt("##Face_editor1", &m_Face[0]);
		ImGui::Text("    ");
		ImGui::SameLine();
		ImGui::InputInt("##Face_editor2", &m_Face[1]);

		ImGui::Text("RenderSize");
		ImGui::SameLine();
		ImGui::InputFloat2("##RenderSize_editor", &m_vRenderSize.x);

		ImGui::Separator();



		const char* EdtiorMode_Conta[] = { "NONE", "INSERT_TILE", "DELETE_TILE", "FILL" };
		const char* combo_preview_value = EdtiorMode_Conta[(int)m_CurEditorState];
		ImGui::Text("EditorMode"); ImGui::SameLine();
		if (ImGui::BeginCombo("##TileEditorMode", combo_preview_value, 0))
		{
			for (int i = 0; i < IM_ARRAYSIZE(EdtiorMode_Conta); i++)
			{
				const bool is_selected = ((int)m_CurEditorState == i);
				if (ImGui::Selectable(EdtiorMode_Conta[i], is_selected))
					m_CurEditorState = (TILEEDITORSTATE)i;


				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::Text("Show Debug Rect");
		ImGui::SameLine();
		ImGui::Checkbox("##Show Debug Rect", &m_bShowDebugRect);
		//ImGui::Text("Update Level TileMap");
		//ImGui::SameLine();
		if (ImGui::Button("Update Level TileMap##Update Level TileMap Btn"))
		{
			m_bUpdateLevelTileMap = true;
		}
		ImGui::Separator();

		TileInfoChange(_TargetObject);


		// Tile Image Button
		for (int i = 0; i < m_vTImageBtns.size(); ++i)
		{
			if (i % _TargetObject->TileMap()->GetMaxCol() == 0 && i != 0)
				//if (i % 8 == 0 && i != 0)
				ImGui::NewLine();

			ImGui::PushID(i);

			if (i == m_iCurTileImageIndex)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05882f, 0.52941f, 0.98039f, 1.0f));

				if (ImGui::ImageButton((void*)m_Texture->GetSRV().Get(), TilePixelSize * 2.f,
					m_vTImageBtns[i].vImageButtonLtUV,
					m_vTImageBtns[i].vImageButtonRbUV, -1))
				{
					m_iCurTileImageIndex = i;
				}
				ImGui::PopStyleColor(1);

				ImGui::PopID();
				ImGui::SameLine();
				continue;
			}
			else if (ImGui::ImageButton((void*)m_Texture->GetSRV().Get(), TilePixelSize * 2.f,
				m_vTImageBtns[i].vImageButtonLtUV,
				m_vTImageBtns[i].vImageButtonRbUV, -1))
			{
				m_iCurTileImageIndex = i;
			}



			ImGui::PopID();
			ImGui::SameLine();
		}


	}


	ImGui::EndChild();

}

void TileMapEditorUI::TileInfoChange(CGameObject* _TargetObject)
{
	// 변경사항없으면 따로 변경하지않음
	// 처음엔 prev값이 세팅되있지않아 통과된다.
	if (!(isTileInfoChange() || m_bUpdateLevelTileMap))
		return;

	ImVec2 TilePixelSize = ImVec2(_TargetObject->TileMap()->GetTilePixelSize().x, _TargetObject->TileMap()->GetTilePixelSize().y);

	// Image Button 갱신
	m_vTImageBtns.resize(_TargetObject->TileMap()->GetMaxRow() * _TargetObject->TileMap()->GetMaxCol());
	for (int i = 0; i < m_vTImageBtns.size(); ++i)
	{
		UINT iRow = i / _TargetObject->TileMap()->GetMaxCol();
		UINT iCol = i % _TargetObject->TileMap()->GetMaxCol();

		ImVec2 vLTUV = ImVec2((iCol * TilePixelSize.x) / m_Texture->GetWidth()
			, (iRow * TilePixelSize.y) / m_Texture->GetHeight());
		ImVec2 vRbUV = {};
		vRbUV = ImVec2(vLTUV.x + _TargetObject->TileMap()->GetSliceSizeUV().x, vLTUV.y + _TargetObject->TileMap()->GetSliceSizeUV().y);

		m_vTImageBtns[i].vImageButtonLtUV = vLTUV;
		m_vTImageBtns[i].vImageButtonRbUV = vRbUV;
	}



	vector <vector<EditorTileInfo>> vPrevTile;
	vPrevTile.resize(m_vTile.size());
	vPrevTile = m_vTile;


	_TargetObject->TileMap()->SetFace((UINT)m_Face[0], (UINT)m_Face[1]);
	_TargetObject->TileMap()->SetTileRenderSize(Vec2(m_vRenderSize.x, m_vRenderSize.y));

	// 선택한 가로 세로만큼 Tile새로 만들어주기
	m_vTile.clear();
	for (size_t i = 0; i < m_Face[1]; ++i)
	{
		vector<EditorTileInfo> v;
		v.resize(1);
		v[0].vTilePos = ImVec2(0 * (m_vRenderSize.x * m_fCurMouseWheel), i * (m_vRenderSize.y * m_fCurMouseWheel));
		v[0].iTileImageIndex = 0;
		m_vTile.push_back(v);

		for (size_t j = 1; j < m_Face[0]; ++j)
		{
			EditorTileInfo test;
			test.vTilePos = ImVec2(j * (m_vRenderSize.x * m_fCurMouseWheel), i * (m_vRenderSize.y * m_fCurMouseWheel));
			test.iTileImageIndex = 0;

			m_vTile[i].push_back(test);
		}
	}

	// 타일 기존정보 유지한채로 변경
	if (vPrevTile.size() > 0)
	{
		if (m_vTile.size() * m_vTile[0].size() == vPrevTile.size() * vPrevTile[0].size())
		{
			for (int i = 0; i < m_Face[1]; ++i)
			{
				for (int j = 0; j < m_Face[0]; ++j)
				{
					if (vPrevTile[i][j].iTileImageIndex != 0)
					{
						m_vTile[i][j].iTileImageIndex = vPrevTile[i][j].iTileImageIndex;
					}
				}
			}
		}
		else
		{
			int temp[2] = { m_PrevFace[0], m_PrevFace[1] };
			if (m_PrevFace[0] > m_Face[0])
				temp[0] = m_Face[0];
			if (m_PrevFace[1] > m_Face[1])
				temp[1] = m_Face[1];


			for (int i = 0; i < temp[1]; ++i)
			{
				for (int j = 0; j < temp[0]; ++j)
				{
					if (vPrevTile[i][j].iTileImageIndex != 0)
					{
						m_vTile[i][j].iTileImageIndex = vPrevTile[i][j].iTileImageIndex;
					}
				}
			}
		}
	}

	m_PlusFace = 0;

	isMouseWheelChange();

	if (m_bUpdateLevelTileMap)
	{
		SetTileInfo(_TargetObject);
		ColliderUpdate(_TargetObject);
	}

	m_PrevTexture = m_Texture;
	m_PrevFace[0] = m_Face[0];
	m_PrevFace[1] = m_Face[1];
	m_vPrevRenderSize = m_vRenderSize;
	m_fPrevMouseWheel = m_fCurMouseWheel;
}

bool TileMapEditorUI::isMouseInTile(int _index_One, int _index_Two)
{
	return (m_vTile[_index_One][_index_Two].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x < ImGui::GetMousePos().x &&
		m_vTile[_index_One][_index_Two].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y < ImGui::GetMousePos().y &&
		m_vTile[_index_One][_index_Two].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x + (m_vRenderSize.x * m_fCurMouseWheel) > ImGui::GetMousePos().x &&
		m_vTile[_index_One][_index_Two].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y + (m_vRenderSize.y * m_fCurMouseWheel) > ImGui::GetMousePos().y);
}

bool TileMapEditorUI::isMouseInTile(int _index_One, int _index_Two, int _anotherindex_One, int _anotherindex_Two)
{
	return (m_vTile[_index_One][_index_Two].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x < ImGui::GetMousePos().x &&
		m_vTile[_index_One][_index_Two].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y < ImGui::GetMousePos().y &&
		m_vTile[_anotherindex_One][_anotherindex_Two].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x + (m_vRenderSize.x * m_fCurMouseWheel) > ImGui::GetMousePos().x &&
		m_vTile[_anotherindex_One][_anotherindex_Two].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y + (m_vRenderSize.y * m_fCurMouseWheel) > ImGui::GetMousePos().y);
}

bool TileMapEditorUI::isObjectInGrid(ImVec2 _vGridLT, ImVec2 _vPos)
{
	return (_vGridLT.x < _vPos.x &&
		_vGridLT.y < _vPos.y &&
		_vGridLT.x + m_vGridSize.x > _vPos.x &&
		_vGridLT.y + m_vGridSize.y > _vPos.y);
}

bool TileMapEditorUI::isObjectInGrid(ImVec2 _vGridLT, ImVec2 _vPosLT, ImVec2 _vPosRB)
{
	return (_vGridLT.x < _vPosRB.x &&
		_vGridLT.y < _vPosRB.y &&
		_vGridLT.x + m_vGridSize.x > _vPosLT.x &&
		_vGridLT.y + m_vGridSize.y > _vPosLT.y);
}

bool TileMapEditorUI::isTileInfoChange()
{
	if ((m_Texture != m_PrevTexture) ||
		(m_Face[0] != m_PrevFace[0] || m_Face[1] != m_PrevFace[1]) ||
		(m_vRenderSize != m_vPrevRenderSize) ||
		(m_fCurMouseWheel != m_fPrevMouseWheel))
	{
		m_PlusFace = m_Face[0] - m_PrevFace[0];

		if (m_Face[0] <= 0)
		{
			m_Face[0] = 1;
		}
		if (m_Face[1] <= 0)
		{
			m_Face[1] = 1;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool TileMapEditorUI::isMouseWheelChange()
{
	if (m_fCurMouseWheel != m_fPrevMouseWheel)
	{
		if (m_fPrevMouseWheel - m_fCurMouseWheel > 0)
		{
			m_vScrolling.x += (m_vRenderSize.x * (m_fPrevMouseWheel - m_fCurMouseWheel));
			m_vScrolling.y += (m_vRenderSize.y * (m_fPrevMouseWheel - m_fCurMouseWheel));
		}
		else if (m_fPrevMouseWheel - m_fCurMouseWheel < 0)
		{
			m_vScrolling.x += -(m_vRenderSize.x * (m_fPrevMouseWheel - m_fCurMouseWheel));
			m_vScrolling.y += -(m_vRenderSize.y * (m_fPrevMouseWheel - m_fCurMouseWheel));
		}
		return true;
	}
	else
	{
		return false;
	}
}

void TileMapEditorUI::SetTileInfo(CGameObject* _TargetObject)
{
	// Tile실제 적용 파트
	for (int i = 0; i < m_Face[1]; ++i)
	{
		for (int j = 0; j < m_Face[0]; ++j)
		{
			if (m_vTile[i][j].iTileImageIndex == 0)
				_TargetObject->TileMap()->SetTileIndex(i, j, m_vTile[i][j].iTileImageIndex, false);
			else
				_TargetObject->TileMap()->SetTileIndex(i, j, m_vTile[i][j].iTileImageIndex, true);
		}
	}

	m_bUpdateLevelTileMap = false;
}

void TileMapEditorUI::SetMouseWheel(ImGuiIO& _io)
{
	if (m_fCurMouseWheel <= 10.f && m_fCurMouseWheel >= 0.f)
	{
		m_fCurMouseWheel += _io.MouseWheel / 10.f;


		if (m_fCurMouseWheel > 10.f)
			m_fCurMouseWheel = 10.f;
		else if (m_fCurMouseWheel <= 0.f)
			m_fCurMouseWheel = 0.1f;
	}

}

void TileMapEditorUI::FindLTRBTile(int _LT[], int _RB[], ImVec2 _vGridLT)
{
	static bool bFindLT = false;

	for (int i = 0; i < m_Face[1]; ++i)
	{
		for (int j = 0; j < m_Face[0]; ++j)
		{
			if (isObjectInGrid(_vGridLT, (m_vTile[i][j].vTilePos + m_vScrolling + ImGui::GetWindowPos()),
				(m_vTile[i][j].vTilePos + m_vScrolling + ImGui::GetWindowPos() + (m_vRenderSize * m_fCurMouseWheel))))
			{
				_LT[0] = j;
				_LT[1] = i;

				float width = 1.f;
				float height = 1.f;

				if (m_Face[0] > 1)
					width = (m_vTile[0][1].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x) - (m_vTile[0][0].vTilePos.x + m_vScrolling.x + ImGui::GetWindowPos().x);
				if (m_Face[1] > 1)
					height = (m_vTile[1][0].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y) - (m_vTile[0][0].vTilePos.y + m_vScrolling.y + ImGui::GetWindowPos().y);


				int RbX = m_vGridSize.x / width;
				int RbY = m_vGridSize.y / height;

				_RB[0] = j + RbX + 1;
				_RB[1] = i + RbY + 2;

				if (_RB[0] > m_Face[0])
				{
					_RB[0] = m_Face[0];
				}
				if (_RB[1] > m_Face[1])
				{
					_RB[1] = m_Face[1];
				}
				return;
			}
		}
	}

}

void TileMapEditorUI::Fill(int _index_One, int _index_Two)
{
	m_vTile[_index_One][_index_Two].iTileImageIndex = m_iCurTileImageIndex;

	int iUp[2] = { _index_One, _index_Two + 1 };
	int iDown[2] = { _index_One, _index_Two - 1 };
	int iLeft[2] = { _index_One - 1, _index_Two };
	int iRight[2] = { _index_One + 1, _index_Two };


	if (iUp[1] < m_Face[0] &&
		m_vTile[iUp[0]][iUp[1]].iTileImageIndex == 0)
	{
		Fill(iUp[0], iUp[1]);
	}
	if (iDown[1] >= 0 &&
		m_vTile[iDown[0]][iDown[1]].iTileImageIndex == 0)
	{
		Fill(iDown[0], iDown[1]);
	}
	if (iLeft[0] >= 0 &&
		m_vTile[iLeft[0]][iLeft[1]].iTileImageIndex == 0)
	{
		Fill(iLeft[0], iLeft[1]);
	}
	if (iRight[0] < m_Face[1] &&
		m_vTile[iRight[0]][iRight[1]].iTileImageIndex == 0)
	{
		Fill(iRight[0], iRight[1]);
	}


	return;
}

void TileMapEditorUI::EditorMode(CGameObject* _TargetObject)
{
	if (m_iCurGridTile[0] == -1 || m_iCurGridTile[1] == -1)
		return;

	static int Name = 0;

	switch (m_CurEditorState)
	{
	case TILEEDITORSTATE::NONE:
		break;
	case TILEEDITORSTATE::INSERT_TILE:
		m_vTile[m_iCurGridTile[0]][m_iCurGridTile[1]].iTileImageIndex = m_iCurTileImageIndex;
		break;
	case TILEEDITORSTATE::DELETE_TILE:
		m_vTile[m_iCurGridTile[0]][m_iCurGridTile[1]].iTileImageIndex = 0;
		break;
	case TILEEDITORSTATE::FILL:
		// 클릭한곳에 이미 이미지가 있으면 그냥 리턴
		if (m_vTile[m_iCurGridTile[0]][m_iCurGridTile[1]].iTileImageIndex != 0)
			return;
		else
			Fill(m_iCurGridTile[0], m_iCurGridTile[1]);
		break;
	default:
		break;
	}

}


Tile_TYPE TileMapEditorUI::CheckTileType(int _iImageIndex)
{
	Tile_TYPE Type = Tile_TYPE::NOT;

	for (int i = 0; i < sizeof(m_iNormalTileIndex) / sizeof(int); ++i)
	{
		if (m_iNormalTileIndex[i] == _iImageIndex)
		{
			Type = Tile_TYPE::Default;
		}
	}

	for (int i = 0; i < sizeof(m_iSpecialTileIndex) / sizeof(int); ++i)
	{
		if (m_iSpecialTileIndex[i] == _iImageIndex)
		{
			Type = Tile_TYPE::Special;
		}
	}

	for (int i = 0; i < sizeof(m_iDamageTileIndex) / sizeof(int); ++i)
	{
		if (m_iDamageTileIndex[i] == _iImageIndex)
		{
			Type = Tile_TYPE::Damage;
		}
	}

	return Type;
}

void TileMapEditorUI::ColliderUpdate(CGameObject* _TargetObject)
{
	vector<CGameObject*> Obj;

	Obj = _TargetObject->GetChild();

	for (int i = 0; i < Obj.size(); ++i)
	{
		GamePlayStatic::DestroyGameObject(Obj[i]);
	}


	for (int i = 0; i < m_Face[1]; ++i)
	{
		for (int j = 0; j < m_Face[0]; ++j)
		{
			Tile_TYPE Type = CheckTileType(m_vTile[i][j].iTileImageIndex);
			
			if (Type != Tile_TYPE::NOT)
			{
				CGameObject* pObj = new CGameObject;
				wstring TileColName = L"TileCollider";
				int NameCount = i * m_Face[0] + j;
				wstring Name = std::to_wstring(NameCount);
				pObj->SetName(TileColName + Name);

				pObj->AddComponent(new CTransform);
				pObj->AddComponent(new CCollider2D);
				pObj->AddComponent(new CTileColScript);

				Vec2 vTileMapLTPos = Vec2((-(_TargetObject->Transform()->GetRelativeScale().x / 2.f) + m_vRenderSize.x / 2.f),
					((_TargetObject->Transform()->GetRelativeScale().y / 2.f) - m_vRenderSize.y / 2.f));

				// Relative Pos 더하는건 좀 더 테스트해봐야할듯
				Vec3 vPos = Vec3((vTileMapLTPos.x + (j * m_vRenderSize.x)),
					(vTileMapLTPos.y - (i * m_vRenderSize.y)),
					_TargetObject->Transform()->GetRelativePos().z);

				pObj->Transform()->SetRelativePos(vPos);
				pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));


				pObj->Collider2D()->SetDrawDebugShader(false);
				pObj->Collider2D()->SetOffsetScale(Vec2(m_vRenderSize.x, m_vRenderSize.y));
				pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

				pObj->GetScript<CTileColScript>()->SetTileType(Type);


				CGameObject* pTileMap = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"TileMap");
				CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
				pTileMap->AddChild(pObj);
				//pCurLevel->AddObject(pObj, 23);

				
			}
		}
	}
	int a = 0;
}

void TileMapEditorUI::SaveTileMap()
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
	ofn.lpstrFilter = L"Tile\0*";
	// 초기 필터
	ofn.nFilterIndex = 0;
	// 타이틀
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();
	strAnimationFolder += L"TileMap";

	// 초기 경로
	ofn.lpstrInitialDir = strAnimationFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal 방식
	// 반환값으로 저장시 true, 취소시 false반환
	if (GetSaveFileName(&ofn))
	{
		wstring strFilePath = szName; 


		FILE* pFile = nullptr;
		_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

		assert(pFile);

		// Animation 이 사용하는 텍스쳐
		fprintf(pFile, "[Texture Name]\n");
		string strName = string(m_Texture->GetKey().begin(), m_Texture->GetKey().end());
		fprintf(pFile, strName.c_str());
		fprintf(pFile, "\n");

		fprintf(pFile, "[Texture Path]\n");
		strName = string(m_Texture->GetRelativePath().begin(), m_Texture->GetRelativePath().end());
		fprintf(pFile, strName.c_str());
		fprintf(pFile, "\n");


		// 타일 개수
		fprintf(pFile, "[Tile Count]\n");
		fprintf(pFile, "%d\n", m_Face[1] * m_Face[0]);

		fprintf(pFile, "[Face[1]]\n");
		fprintf(pFile, "%d\n", m_Face[1]);

		fprintf(pFile, "[Face[0]]\n");
		fprintf(pFile, "%d\n", m_Face[0]);


		for (int i = 0; i < m_Face[1]; ++i)
		{
			for (int j = 0; j < m_Face[0]; ++j)
			{
				fprintf(pFile, "[Tile Index]\n");
				fprintf(pFile, "%d\n", (int)i * m_Face[1] + j);

				fprintf(pFile, "[Tile Pos]\n");
				fprintf(pFile, "%f %f\n", (float)m_vTile[i][j].vTilePos.x, (float)m_vTile[i][j].vTilePos.y);

				fprintf(pFile, "[iTileImageIndex]\n");
				fprintf(pFile, "%d\n", (int)m_vTile[i][j].iTileImageIndex);

				fprintf(pFile, "[bColliderOn]\n");
				fprintf(pFile, "%d\n", (int)m_vTile[i][j].bColliderOn);

				fprintf(pFile, "\n\n");
			}

		}

		// 모든 프레임 정보
		fwrite(m_vTile.data(), sizeof(m_vTile), 1, pFile);

		fclose(pFile);
	}
}

void TileMapEditorUI::LoadTileMap()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetMainWind();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"Tile\0*";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();


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

		// 프레임 개수
		FScanf(szBuff, pFile);
		int iFrameCount = 0;
		fscanf_s(pFile, "%d", &iFrameCount);

		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);
		fscanf_s(pFile, "%d", &m_Face[1]);

		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);
		fscanf_s(pFile, "%d", &m_Face[0]);

		// 모든 프레임 정보
		EditorTileInfo frm = {};
		m_vTile.clear();
		for (int i = 0; i < m_Face[1]; ++i)
		{
			float pt[2] = {};
			vector<EditorTileInfo> v;
			v.resize(1);

			while (true)
			{
				FScanf(szBuff, pFile);


				if (!strcmp("[Tile Pos]", szBuff))
				{
					fscanf_s(pFile, "%f", &pt[0]);
					fscanf_s(pFile, "%f", &pt[1]);

					v[0].vTilePos = ImVec2(pt[0], pt[1]);
				}
				else if (!strcmp("[iTileImageIndex]", szBuff))
				{
					fscanf_s(pFile, "%d", &v[0].iTileImageIndex);
				}
				else if (!strcmp("[bColliderOn]", szBuff))
				{
					fscanf_s(pFile, "%d", &v[0].bColliderOn);
					break;
				}
			}
			m_vTile.push_back(v);

			for (int j = 0; j < m_Face[0] - 1; ++j)
			{
				float pt2[2] = {};

				while (true)
				{
					FScanf(szBuff, pFile);

					
					if (!strcmp("[Tile Pos]", szBuff))
					{
						fscanf_s(pFile, "%f", &pt2[0]);
						fscanf_s(pFile, "%f", &pt2[1]);

						frm.vTilePos = ImVec2(pt2[0], pt2[1]);
					}
					else if (!strcmp("[iTileImageIndex]", szBuff))
					{
						fscanf_s(pFile, "%d", &frm.iTileImageIndex);
					}
					else if (!strcmp("[bColliderOn]", szBuff))
					{
						fscanf_s(pFile, "%d", &frm.bColliderOn);
						break;
					}
				}
				m_vTile[i].push_back(frm);
			}
		}
		fclose(pFile);
	}
	int a = 0;
}

