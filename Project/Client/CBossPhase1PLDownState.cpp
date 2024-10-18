#include "pch.h"
#include "CBossPhase1PLDownState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

CBossPhase1PLDownState::CBossPhase1PLDownState()
	: m_fDownTime(0.5f)
	, m_fAccTime(0.f)
{
}

CBossPhase1PLDownState::~CBossPhase1PLDownState()
{
}

void CBossPhase1PLDownState::finaltick()
{
	if (m_fAccTime > m_fDownTime)
	{
		ChangeState(L"BossPhase1PLAlertState");
	}

	m_fAccTime += DT;
}

void CBossPhase1PLDownState::Enter()
{
}

void CBossPhase1PLDownState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_PatternLast_ALERT);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_PatternLast_ALERT);
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
}


