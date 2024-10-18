#include "pch.h"
#include "CAfterExectionState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CAfterExectionState::CAfterExectionState()
	: m_fAccTime(0.f)
	, m_fFadeOutTime(5.f)
	, m_bFadeOut(false)
{
}

CAfterExectionState::~CAfterExectionState()
{
}

void CAfterExectionState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_Execution_After);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::PhaseFinal_Execution_After);
	pMainCamera->GetScript<CCameraScript>()->SetShakeOnOff(false, 0.f, 0.f, CAMERA_SHAKE_TYPE::NO);

	if (m_fAccTime > m_fFadeOutTime && !m_bFadeOut)
	{
		pMainCamera->GetScript<CCameraScript>()->FadeOut(2.f);
		pMainCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.25f, 0.01f);
		m_bFadeOut = true;
	}
	m_fAccTime += DT;
}

void CAfterExectionState::Enter()
{
}

void CAfterExectionState::Exit()
{
}


