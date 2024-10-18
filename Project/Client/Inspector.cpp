#include "pch.h"
#include "Inspector.h"

#include "Outliner.h"

#include <Engine/CTransform.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "ScriptUI.h"

#include "AssetUI.h"


Inspector::Inspector()
	: UI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	// 자식 UI 생성
	CreateChildUI();
}

Inspector::~Inspector()
{

}

void Inspector::tick()
{
}

void Inspector::render_update()
{
	if (nullptr == m_TargetObject)
		return;

	if (nullptr != m_TargetObject)
	{
		string strName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());

		static char ObjName[50];
		static string PrevName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
		static CGameObject* prevObject = m_TargetObject;
		strcpy_s(ObjName, strName.c_str());

		ImGui::InputText("##ObjectName", ObjName, 50);


		string SettingName(ObjName);
		if (SettingName != PrevName && prevObject == m_TargetObject)
		{
			m_TargetObject->SetName(ToWString(SettingName));

			Outliner* pOutliner = (Outliner*)CImGuiMgr::GetInst()->FindUI("##Outliner");
			pOutliner->ResetCurrentLevel();
		}

		static int  LayerIndex = m_TargetObject->GetLayerIdx();
		static bool childMove = true;

		ImGui::Text("Cur Layer Index : ");
		ImGui::SameLine();
		ImGui::Text("%d",m_TargetObject->GetLayerIdx());

		ImGui::Separator();
		ImGui::Text("Layer Index");
		ImGui::SameLine();
		ImGui::InputInt("##InputLayerIndex", &LayerIndex);

		ImGui::Text("ChildMove");
		ImGui::SameLine();
		ImGui::Checkbox("##ChildMove", &childMove);
		ImGui::SameLine();
		if (ImGui::Button("Add Object", ImVec2(100.f, 20.f)))
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(m_TargetObject, LayerIndex, childMove);
		}
		

		PrevName = SettingName;
		prevObject = m_TargetObject;
	}
	
	
}

void Inspector::SetTargetObject(CGameObject* _Object)
{
	// Target 오브젝트 설정
	m_TargetObject = _Object;

	// 해당 오브젝트가 보유하고 있는 컴포넌트에 대응하는 컴포넌트UI 활성화
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrComUI[i])
		{
			m_arrComUI[i]->SetTargetObject(_Object);
		}
	}

	// 해당 오브젝트가 보유하고 있는 Script 에 맞추어서 ScriptUI 를 활성화 시킨다.
	if (nullptr == _Object)
	{
		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->Deactivate();
		}
	}
	else
	{
		if (m_vecScriptUI.size() < _Object->GetScripts().size())
		{
			ResizeScriptUI(_Object->GetScripts().size());
		}

		const vector<CScript*>& vecScripts = _Object->GetScripts();
		if (vecScripts.size() <= 0)
		{
			for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
			{
				m_vecScriptUI[i]->Deactivate();
			}
		}

		for (size_t i = 0; i < vecScripts.size(); ++i)
		{
			m_vecScriptUI[i]->SetScript(vecScripts[i]);			
		}
	}


	// AssetUI 비활성화
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> _Asset)
{
	SetTargetObject(nullptr);

	m_TargetAsset = _Asset;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
		
	if(nullptr != m_TargetAsset)
	{
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->Activate();
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->SetAsset(_Asset);
	}	
}
