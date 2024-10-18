#include "pch.h"
#include "Outliner.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/CKeyMgr.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

#include <Engine/CTaskMgr.h>
#include <Engine/CPrefab.h>

Outliner::Outliner()
	: UI("Outliner", "##Outliner")
	, m_bPopup(false)
{
	m_Tree = new TreeUI("OutlinerTree");
	m_Tree->ShowRootNode(false);
	m_Tree->UseDragDrop(true);

	AddChildUI(m_Tree);

	// 트리에 클릭 이벤트 등록
	m_Tree->AddSelectDelegate(this, (Delegate_1)&Outliner::SelectObject);
	m_Tree->AddDragDropDelegate(this, (Delegate_2)&Outliner::DragDropObject);

	// 트리 내용을 현재 레벨의 물체들로 구성
	ResetCurrentLevel();
}

Outliner::~Outliner()
{
}

void Outliner::render_update()
{
	if (CTaskMgr::GetInst()->GetObjectEvent())
	{
		ResetCurrentLevel();
	}

	if (KEY_TAP(KEY::DEL))
	{
		TreeNode* pNode = m_Tree->GetSelectedNode();
		if (nullptr != pNode)
		{
			CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
			GamePlayStatic::DestroyGameObject(pSelectObj);
		}
	}

	//if (KEY_TAP(KEY::RBTN) && m_Tree->GetSelectedNode() != nullptr)
	//{
	//	m_bPopup = true;
	//}
	if (m_bPopup)
	{
		ImGui::OpenPopup("my_select_popup");

		if (ImGui::BeginPopup("my_select_popup"))
		{
			
			ImGui::TextColored(ImVec4(.0f, .9f, .0f, 1.0f), m_Tree->GetSelectedNode()->GetName().c_str());
			ImGui::SameLine();
			if (ImGui::Selectable("X##x"))
			{
				m_bPopup = false;
			}
			if (ImGui::Selectable("Create Prefab##Create Prefab"))
			{
				TreeNode* pNode = m_Tree->GetSelectedNode();
				CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
				
				Ptr<CPrefab> pPrefab = new CPrefab(pSelectObj, false);
				string s = "prefab\\";
				string sExt = ".pref";
				string sName = s + m_Tree->GetSelectedNode()->GetName() + sExt;
				wstring PrefabName = ToWString(sName);
				CAssetMgr::GetInst()->AddAsset<CPrefab>(PrefabName, pPrefab.Get());
				pPrefab->Save(PrefabName);

				m_bPopup = false;
			}
			
			ImGui::EndPopup();
		}
	}
}

void Outliner::ResetCurrentLevel()
{
	// 트리 내용을 삭제
	m_Tree->ClearNode();

	// 현재 레벨을 가져온다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	// 트리에 루트 추가
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot", 0);

	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			AddObjectToTree(pRootNode, vecParent[i]);
		}
	}
}

void Outliner::SetNodeName(string _sName)
{
	if (m_Tree->GetSelectedNode())
	{
		TreeNode* pNode = m_Tree->GetSelectedNode();
		CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
		pSelectObj->SetName(ToWString(_sName));

		//m_Tree->GetSelectedNode()->SetName(_sName);
		//m_Tree->GetSelectedNode()
	}
}



void Outliner::AddObjectToTree(TreeNode* _Node, CGameObject* _Object)
{
	TreeNode* pNode = m_Tree->AddTreeNode(_Node, string(_Object->GetName().begin(), _Object->GetName().end()), (DWORD_PTR)_Object);

	const vector<CGameObject*>& vecChild = _Object->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddObjectToTree(pNode, vecChild[i]);
	}
}

void Outliner::SelectObject(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (nullptr == pObject)
		return;

	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pObject);	
}

void Outliner::DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source)
{
	TreeNode* pDestNode = (TreeNode*)_Dest;
	TreeNode* pSourceNode = (TreeNode*)_Source;

	CGameObject* pDestObj = nullptr;
	if(nullptr != pDestNode)
		pDestObj = (CGameObject*)pDestNode->GetData();

	CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();

	// 부모 오브젝트가 자신의 자식오브젝트의 자식으로 들어가려는 경우는 방지
	if (pDestObj != nullptr && pDestObj->IsAncestor(pSourceObj))
		return;

	if (nullptr == pDestNode)
	{
		int LayerIdx = pSourceObj->DisconnectWithParent();

		// 원래 부모가 없었다
		if (LayerIdx == -1)
			return;

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pSourceObj, LayerIdx, false);
	}
	else
	{		
		pDestObj->AddChild(pSourceObj);
	}

	ResetCurrentLevel();
}
