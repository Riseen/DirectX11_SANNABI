#include "pch.h"
#include "CBeforeExctionState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CQTEScript.h>
#include <Scripts/CCameraScript.h>

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CBeforeExctionState::CBeforeExctionState()
	: m_QTEUI(nullptr)
	, m_fQTEValue(0.f)
	, m_fPoundingTime(0.5f)
	, m_fAccTime(0.f)	
{
}

CBeforeExctionState::~CBeforeExctionState()
{
}

void CBeforeExctionState::finaltick()
{
	if (m_fAccTime > m_fPoundingTime)
	{
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_Execution_Ready);

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



		if (KEY_PRESSED(KEY::LBTN))
		{
			m_fQTEValue += 1.f;
		}
		if (KEY_RELEASED(KEY::LBTN))
		{
			if (m_fQTEValue > 0)
				m_fQTEValue -= 1.f;
		}


		if (m_fQTEValue > 100.f)
		{
			CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
			pMainCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.05f, 0.1f);


			ChangeState(L"ExctionState");
		}
	}


	m_fAccTime += DT;
}

void CBeforeExctionState::Enter()
{
}

void CBeforeExctionState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_Execution);

	GamePlayStatic::DestroyGameObject(m_QTEUI);
	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_SNB_FinalExecuteClang.wav", 1, 0.1f);
	GamePlayStatic::Play2DBGM(L"sound\\Boss\\Sfx_SNB_FinalExecuteClang.wav", 0.f);

	m_fAccTime = 0.f;
}


