#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CPrefab.h>
#include <Engine/CGameObject.h>
#include <Engine/CTransform.h>

PrefabUI::PrefabUI()
	: AssetUI("Prefab", "##Prefab", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}


void PrefabUI::render_update()
{
	AssetUI::render_update();

	Ptr<CPrefab> pPrefab = (CPrefab*)GetAsset().Get();
	static Vec3 vWorldPos = {};
	static int LayerIndex = 0;

	ImGui::Text("Prefab : ");
	ImGui::SameLine();
	ImGui::Text("asd");

	ImGui::Text("World Pos : ");
	ImGui::SameLine();
	ImGui::DragFloat3("##Prefab World Pos", vWorldPos);

	ImGui::Text("LayerIndex : ");
	ImGui::SameLine();
	ImGui::InputInt("##Prefab Layer Index", &LayerIndex);

	if (ImGui::Button("Instantiate##Instantiate", ImVec2(120.f, 20.f)))
	{
		Instantiate(pPrefab, vWorldPos, LayerIndex);
	}
}

void PrefabUI::Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _layerIdx)
{
	if (nullptr == _Prefab)
		return;

	CGameObject* pNewObj = _Prefab->Instantiate();

	pNewObj->Transform()->SetRelativePos(_vWorldPos);

	GamePlayStatic::SpawnGameObject(pNewObj, _layerIdx);
}
