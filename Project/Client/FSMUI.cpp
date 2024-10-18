#include "pch.h"
#include "FSMUI.h"

#include <Engine/CFSM.h>

FSMUI::FSMUI()
	: AssetUI("FSM", "##FSM", ASSET_TYPE::FSM)
{
}

FSMUI::~FSMUI()
{
}

void FSMUI::render_update()
{
	AssetUI::render_update();

	Ptr<CFSM> pFSM = (CFSM*)GetAsset().Get();

	map<wstring, CState*> States = pFSM->GetStates();

	map<wstring, CState*>::iterator iter; 
	for (iter = States.begin(); iter != States.end(); ++iter)
	{
		ImGui::Text("State : ");
		ImGui::SameLine();
		string sName = ToString(iter->first);
		ImGui::Text(sName.c_str());
	}
	//return iter->second;
}