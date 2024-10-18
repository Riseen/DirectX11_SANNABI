#include "pch.h"
#include "CLevelChangeEventColScript.h"

#include "CGameSystemMgrScript.h"
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

#include <Scripts/CCameraScript.h>

CLevelChangeEventColScript::CLevelChangeEventColScript()
	: CScript(LEVELCHANGEEVENTCOLSCRIPT)
	, m_fChangeTime(1.f)
	, m_fAccTime(0.f)
	, m_bChangeStart(false)
{
}

CLevelChangeEventColScript::~CLevelChangeEventColScript()
{
}

void CLevelChangeEventColScript::begin()
{
}

void CLevelChangeEventColScript::tick()
{


	if(m_bChangeStart)
	m_fAccTime += DT;
	if (m_fAccTime > m_fChangeTime)
	{
		CLevelMgr::GetInst()->SetLevelType(LEVEL_TYPE::BOSS);
		CLevelMgr::GetInst()->ChangeLevel(CLevelMgr::GetInst()->LoadLevel(L"level\\Boss.lv"), LEVEL_STATE::PLAY);
	}
}

void CLevelChangeEventColScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

	LEVEL_TYPE ltype = CLevelMgr::GetInst()->GetCurLevelType();
	switch (ltype)
	{
	case LEVEL_TYPE::MAIN:
	{
	}
		break;
	case LEVEL_TYPE::STAGE1:
	{
		pMainCamera->GetScript<CCameraScript>()->FadeIn(0.1f, Vec3{});
		m_bChangeStart = true;
	}
		break;
	case LEVEL_TYPE::BOSS:
	{
	}
		break;
	default:
		break;
	}
}

void CLevelChangeEventColScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLevelChangeEventColScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLevelChangeEventColScript::SaveToFile(FILE* _File)
{
}

void CLevelChangeEventColScript::LoadFromFile(FILE* _File)
{
}



