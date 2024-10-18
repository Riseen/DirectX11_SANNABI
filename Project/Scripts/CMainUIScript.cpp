#include "pch.h"
#include "CMainUIScript.h"
#include "CBackgroundScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMainUIScript::CMainUIScript()
	: CScript(MAINUISCRIPT)
	, m_fAlpha(0.f)
{
}

CMainUIScript::~CMainUIScript()
{
}

void CMainUIScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();
}

void CMainUIScript::tick()
{
	CGameObject* pBackGround = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Background");
	if (!pBackGround->GetScript<CBackgroundScript>()->IsMainReady())
		return;

	if (m_fAlpha >= 0.5f)
		return;

	m_fAlpha += DT * 0.5f;

	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\UI_MainScene_BG.png", L"texture\\UI\\UI_MainScene_BG.png"));
}

void CMainUIScript::SaveToFile(FILE* _File)
{
}

void CMainUIScript::LoadFromFile(FILE* _File)
{
}


