#include "pch.h"
#include "LevelOptUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

LevelOptUI::LevelOptUI()
	: UI("LevelOptUI", "##LevelOptUI")
	, m_LayerName {}
{
	Deactivate();
	SetModal(false);
}

LevelOptUI::~LevelOptUI()
{
}

void LevelOptUI::render_update()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	static char buffer[50] = {};

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_LayerName[i] = ToString(pCurLevel->GetLayer(i)->GetName());
	}

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		//ImGui::InputText(m_LayerName[i].c_str(), buffer, 50);
	}

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		pCurLevel->GetLayer(i)->SetName(ToWString(m_LayerName[i]));
	}
}

void LevelOptUI::Deactivate()
{
	UI::Deactivate();
	ImGui::SetWindowFocus(nullptr);
}


