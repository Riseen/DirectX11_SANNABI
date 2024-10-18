#include "pch.h"
#include "TileMapUI.h"
#include "TileMapEditorUI.h"

#include <Engine/CTileMap.h>
#include <Engine/CKeyMgr.h>


TileMapUI::TileMapUI()
	: ComponentUI("TileMapUI", "##TileMapUI", COMPONENT_TYPE::TILEMAP)
{
	SetSize(ImVec2(0.f, 0.f));
	SetComopnentTitle("TileMapUI");
}

TileMapUI::~TileMapUI()
{

}




void TileMapUI::render_update()
{
	ImGui::Separator();

	Vec2 vTileRenderSize = GetTargetObject()->TileMap()->GetTileRenderSize();


	ImGui::Text("RenderSize");
	ImGui::SameLine();
	ImGui::DragFloat2("##RenderSize", &vTileRenderSize.x);

	if (ImGui::Button("Edit##TileMapEditor_Btn", ImVec2(40.f, 20.f)))
	{
		TileMapEditorUI* pTileMapEditor = (TileMapEditorUI*)CImGuiMgr::GetInst()->FindUI("##TileMapEditorUI");
		pTileMapEditor->Activate();
	}


	GetTargetObject()->TileMap()->SetTileRenderSize(vTileRenderSize);



}


