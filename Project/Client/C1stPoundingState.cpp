#include "pch.h"
#include "C1stPoundingState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CQTEScript.h>
#include <Scripts/CCameraScript.h>
#include <Scripts/CPlayerEffectScript.h>

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

C1stPoundingState::C1stPoundingState()
	: m_QTEUI(nullptr)
	, m_fPoundingTime (1.5f)
	, m_fAccTime (0.f)
	, m_iQTECount (10)
{
}

C1stPoundingState::~C1stPoundingState()
{
}


void C1stPoundingState::finaltick()
{
	if (m_fAccTime > m_fPoundingTime)
	{
		if (m_QTEUI == nullptr)
		{
			m_QTEUI = new CGameObject;
			m_QTEUI->SetName(L"QTEUI");

			m_QTEUI->AddComponent(new CTransform);
			m_QTEUI->AddComponent(new CMeshRender);
			m_QTEUI->AddComponent(new CAnimator2D);
			m_QTEUI->AddComponent(new CQTEScript);

			CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
			Vec3 vPos = pSelf->Transform()->GetRelativePos();

			m_QTEUI->Transform()->SetRelativePos(Vec3(vPos.x - 250.f, vPos.y + 100.f, vPos.z));
			m_QTEUI->Transform()->SetRelativeScale(Vec3(473.f, 868.f, 1.f));

			m_QTEUI->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			m_QTEUI->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

			m_QTEUI->GetScript<CQTEScript>()->SetQTEType(QTE_TYPE::PRESS);

			GamePlayStatic::SpawnGameObject(m_QTEUI, 1);
		}

		if (KEY_TAP(KEY::LBTN))
			m_iQTECount--;


		if (m_iQTECount <= 0)
		{
			CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
			pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.1f, 0.1f);

			CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
			Vec3 vPos = pSelf->Transform()->GetRelativePos();
			CGameObject* pObj = new CGameObject;
			pObj->SetName(L"Effect");

			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->AddComponent(new CAnimator2D);
			pObj->AddComponent(new CPlayerEffectScript);

			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

			pObj->GetScript<CPlayerEffectScript>()->SetEffectType(PlayerEffect_TYPE::ENEMYATTACK);

			pObj->Transform()->SetRelativePos(Vec3(vPos.x - 20.f, 180.f, vPos.z));

			pObj->Transform()->SetRelativeScale(Vec3(640.f, 640.f, 1.f));

			GamePlayStatic::SpawnGameObject(pObj, 5);

			ChangeState(L"2ndPoundingState");
		}

	}


	m_fAccTime += DT;
}

void C1stPoundingState::Enter()
{
}

void C1stPoundingState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_1stPounding);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_SNB_ExecuteHit1.wav", 1, 0.1f);

	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pMainCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.1f, 0.1f);

	GamePlayStatic::DestroyGameObject(m_QTEUI);
}

