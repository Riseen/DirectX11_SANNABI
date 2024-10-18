#include "pch.h"
#include "CButtonScript.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CFontMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include "CCameraScript.h"
#include "CBackgroundScript.h"

#include "CGameSystemMgrScript.h"

CButtonScript::CButtonScript()
	: CScript(BUTTONSCRIPT)
	, m_CurState(BUTTON_STATE::NOT)
	, m_fAccTime(0.f)
	, m_fFadeTime(1.f)
	, m_bLevelChange(false)
{

}

CButtonScript::~CButtonScript()
{

}


void CButtonScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	
}

void CButtonScript::tick()
{
	CGameObject* pBackGround = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Background");
	if (!pBackGround->GetScript<CBackgroundScript>()->IsMainReady())
		return;

	
	if (m_fAccTime >= m_fFadeTime)
	{
		CLevelMgr::GetInst()->SetLevelType(LEVEL_TYPE::STAGE1);
		CFontMgr::GetInst()->ClearFont();
		CLevelMgr::GetInst()->ChangeLevel(CLevelMgr::GetInst()->LoadLevel(L"level\\Stage1_7.lv"), LEVEL_STATE::PLAY);
		return;
	}

	if (m_bLevelChange)
	{
		m_fAccTime += DT;
	}


	if (m_CurState == BUTTON_STATE::SELECTED)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			m_bLevelChange = true;
			// Fade In
			CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
			pMainCamera->GetScript<CCameraScript>()->FadeIn(m_fFadeTime, Vec3{});
		}
		if (!m_bLevelChange)
		CFontMgr::GetInst()->SetFont(L"게임 시작", Vec2(1300.f, 530.f), 50.f, tPixel(255, 255, 255, 255));
	}
	else if (m_CurState == BUTTON_STATE::NOT)
	{
		if(!m_bLevelChange)
		CFontMgr::GetInst()->SetFont(L"게임 시작", Vec2(1320.f, 530.f), 50.f, tPixel(0, 250, 250, 255));
	}
	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\UI_MainScene_SelectBox.png",
		L"texture\\UI\\UI_MainScene_SelectBox.png"));
}

void CButtonScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CGameObject* pBackGround = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Background");
	if (!pBackGround->GetScript<CBackgroundScript>()->IsMainReady())
		return;

	m_CurState = BUTTON_STATE::SELECTED;

	Vec3 vPos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(vPos.x - 20.f, vPos.y, vPos.z));
}

void CButtonScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CButtonScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CGameObject* pBackGround = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Background");
	if (!pBackGround->GetScript<CBackgroundScript>()->IsMainReady())
		return;

	m_CurState = BUTTON_STATE::NOT;
	
	Vec3 vPos = Transform()->GetRelativePos();
	Transform()->SetRelativePos(Vec3(vPos.x + 20.f, vPos.y, vPos.z));
}

void CButtonScript::SaveToFile(FILE* _File)
{
}

void CButtonScript::LoadFromFile(FILE* _File)
{
}



