#include "pch.h"
#include "C2ndPoundingState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CQTEScript.h>
#include <Scripts/CCameraScript.h>
#include <Scripts/CPlayerEffectScript.h>

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

C2ndPoundingState::C2ndPoundingState()
	: m_QTEUI(nullptr)
	, m_fPoundingTime(1.5f)
	, m_fAccTime (0.f)
	, m_iQTECount(10)
	, m_iPrevQTECount(10)
{
}

C2ndPoundingState::~C2ndPoundingState()
{
}

void C2ndPoundingState::finaltick()
{
	if (m_fAccTime > m_fPoundingTime)
	{
		CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_2ndPoundingReady);

		if (m_QTEUI == nullptr)
		{
			m_QTEUI = new CGameObject;
			m_QTEUI->SetName(L"QTEUI");

			m_QTEUI->AddComponent(new CTransform);
			m_QTEUI->AddComponent(new CMeshRender);
			m_QTEUI->AddComponent(new CAnimator2D);
			m_QTEUI->AddComponent(new CQTEScript);

			Vec3 vPos = GetFSM()->GetStateMachine()->GetOwner()->Transform()->GetWorldPos();

			m_QTEUI->Transform()->SetRelativePos(Vec3(vPos.x - 250.f, vPos.y + 50.f, vPos.z));
			m_QTEUI->Transform()->SetRelativeScale(Vec3(473.f, 868.f, 1.f));

			m_QTEUI->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			m_QTEUI->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

			m_QTEUI->GetScript<CQTEScript>()->SetQTEType(QTE_TYPE::PRESS);

			GamePlayStatic::SpawnGameObject(m_QTEUI, 1);
		}

		if (KEY_TAP(KEY::LBTN))
			m_iQTECount--;


		if (m_iQTECount != m_iPrevQTECount)
		{
			if (m_iQTECount == 5)
			{
				pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_2ndPoundingReady_Two);
				pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.05f, 0.1f);
			}
			else if (m_iQTECount <= 0)
			{
				ChangeState(L"3rdBeforePoundingState");
				pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.05f, 0.1f);
			}
		}
	}



	m_iPrevQTECount = m_iQTECount;
	m_fAccTime += DT;
}

void C2ndPoundingState::Enter()
{
}

void C2ndPoundingState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_2ndPounding);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_SNB_ExecuteHit2.wav", 1, 0.1f);

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Effect");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerEffectScript);

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pObj->GetScript<CPlayerEffectScript>()->SetEffectType(PlayerEffect_TYPE::ENEMYATTACK);

	pObj->Transform()->SetRelativePos(Vec3(pSelf->Transform()->GetRelativePos().x - 20.f, 160.f, pSelf->Transform()->GetRelativePos().z));

	pObj->Transform()->SetRelativeScale(Vec3(640.f, 640.f, 1.f));

	GamePlayStatic::SpawnGameObject(pObj, 5);

	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pMainCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.1f, 0.1f);

	GamePlayStatic::DestroyGameObject(m_QTEUI);
}


