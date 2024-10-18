#include "pch.h"
#include "StateMachineUI.h"

#include <typeinfo>
#include <Engine/CStateMachine.h>
#include <Engine/CFSM.h>
#include <Engine/Ptr.h>

StateMachineUI::StateMachineUI()
	: ComponentUI("StateMachine", "##StateMachine", COMPONENT_TYPE::STATEMACHINE)
{
	SetComopnentTitle("StateMachine");
}

StateMachineUI::~StateMachineUI()
{
}

void StateMachineUI::render_update()
{
	ComponentUI::render_update();

	Ptr<CFSM> CurFSM = GetTargetObject()->StateMachine()->GetFSM();

	string FSNName;
	CState* CurState = nullptr;

	if (nullptr != CurFSM)
	{
		//if (CurFSM->GetFSMKey().size() > 0)
		//{
		//	FSNName = ToString(CurFSM->GetFSMKey()).c_str();
		//	CurState = CurFSM->GetCurState();
		//}
	}

	ImGui::Text("FSM    ");
	ImGui::SameLine();
	ImGui::InputText("##FSMName", (char*)FSNName.c_str(), FSNName.length(), ImGuiInputTextFlags_ReadOnly);

	// Mesh Drop üũ
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::MESH == pAsset->GetType())
			{
				GetTargetObject()->StateMachine()->SetFSM((CFSM*)pAsset);
			}
		}

		ImGui::EndDragDropTarget();
	}

	
	
	ImGui::Text("Cur State");
	ImGui::SameLine();
	if (nullptr != CurState)
	{
		const char* stateName = typeid(CurState).name();
		ImGui::Text(stateName);
	}
	
	//ImGui::InputText("##CurStateName", (char*)stateName.c_str(), stateName.length(), ImGuiInputTextFlags_ReadOnly);
}


