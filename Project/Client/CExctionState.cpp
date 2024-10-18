#include "pch.h"
#include "CExctionState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>
#include <Scripts/CPlayerEffectScript.h>

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>


CExctionState::CExctionState()
	: m_fPoundingTime (2.5f)
	, m_fStartTime(1.5f)
	, m_fAccTime (0.f)
	, m_bExction(false)
	, m_bExctionStart(false)
{
}

CExctionState::~CExctionState()
{
}

void CExctionState::finaltick()
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	

	if (m_fAccTime > m_fStartTime && !m_bExctionStart)
	{
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_Execution);
		m_bExctionStart = true;
	}
	if (m_fAccTime > m_fStartTime + 0.05f && !m_bExction)
	{
		pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.05f, 0.1f);
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"Effect");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CPlayerEffectScript);

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		pObj->GetScript<CPlayerEffectScript>()->SetEffectType(PlayerEffect_TYPE::ENEMYATTACK);

		pObj->Transform()->SetRelativePos(Vec3(pSelf->Transform()->GetRelativePos().x - 25.f, 135.f, pSelf->Transform()->GetRelativePos().z));

		pObj->Transform()->SetRelativeScale(Vec3(640.f, 640.f, 1.f));

		GamePlayStatic::SpawnGameObject(pObj, 5);

		GamePlayStatic::Play2DSound(L"sound\\Boss\\Exection.wav", 1, 0.1f);

		pMainCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 4.9f, 3.f, CAMERA_SHAKE_TYPE::FOURDIR_TOP);
		pMainCamera->GetScript<CCameraScript>()->FadeIn(3.5f, Vec3(1.f, 1.f, 1.f));

		m_bExction = true;
	}
	if (m_fAccTime > m_fPoundingTime + m_fStartTime + 3.5f)
	{
		ChangeState(L"AfterExectionState");
	}

	m_fAccTime += DT;
}

void CExctionState::Enter()
{
}

void CExctionState::Exit()
{
	m_fAccTime = 0.f;
	m_bExction = false;
	m_bExctionStart = false;
}


