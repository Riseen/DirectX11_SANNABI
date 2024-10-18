#include "pch.h"
#include "CMenuUIScript.h"
#include "CBackgroundScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CMenuUIScript::CMenuUIScript()
	: CScript(MENUUISCRIPT)
	, m_fAlpha(0.f)
{
}

CMenuUIScript::~CMenuUIScript()
{
}

void CMenuUIScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();
}

void CMenuUIScript::tick()
{
	CGameObject* pBackGround = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Background");
	if (!pBackGround->GetScript<CBackgroundScript>()->IsMainReady())
		return;

	if (m_fAlpha >= 1.f)
	{
		MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"OutLineMtrl"));
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Spr_Logo_Kor.png", L"texture\\UI\\Spr_Logo_Kor.png"));
		return;
	}

	m_fAlpha += DT * 0.5f;

	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	if (nullptr != pMtrl)
	{
		pMtrl->SetScalarParam<float>(SCALAR_PARAM::FLOAT_0, m_fAlpha);
	}
}

void CMenuUIScript::SaveToFile(FILE* _File)
{
}

void CMenuUIScript::LoadFromFile(FILE* _File)
{
}



