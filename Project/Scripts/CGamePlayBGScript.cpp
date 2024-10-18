#include "pch.h"
#include "CGamePlayBGScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CGamePlayBGScript::CGamePlayBGScript()
	: CScript(GAMEPLAYBGSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::INT, "PLAYBG_TYPE", &m_CurPLAYBGType);
}

CGamePlayBGScript::~CGamePlayBGScript()
{
	
}


void CGamePlayBGScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	SetTexture();
}

void CGamePlayBGScript::tick()
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

	Vec3 vPos = Transform()->GetRelativePos();

	Transform()->SetRelativePos(Vec3(pMainCamera->Transform()->GetRelativePos().x, pMainCamera->Transform()->GetRelativePos().y, vPos.z));

}

void CGamePlayBGScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CurPLAYBGType, sizeof(PLAYBG_TYPE), 1, _File);
}

void CGamePlayBGScript::LoadFromFile(FILE* _File)
{
	fread(&m_CurPLAYBGType, sizeof(PLAYBG_TYPE), 1, _File);
}

void CGamePlayBGScript::SetTexture()
{
	switch (m_CurPLAYBGType)
	{
	case PLAYBG_TYPE::NOT:
		break;
	case PLAYBG_TYPE::BOSSROOM_SKY:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_Chap1_Bossroom_Sky.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Sky.png"));
		break;
	case PLAYBG_TYPE::BOSSROOMLOOP_SKY:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_Chap1_BossroomLoop_Sky.png",
			L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Sky.png"));
		break;
	case PLAYBG_TYPE::C1_SKY:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_BG_C1_Sky.png", L"texture\\BackGround\\Spr_BG_C1_Sky.png"));
		break;
	case PLAYBG_TYPE::C1_FBG4:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_BG_C1_FBG4.png", L"texture\\BackGround\\Spr_BG_C1_FBG4.png"));
		break;
	case PLAYBG_TYPE::C1_FBG1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_BG_C1_FBG1 (1).png", L"texture\\BackGround\\Spr_BG_C1_FBG1 (1).png"));
		break;
	default:
		break;
	}
}
