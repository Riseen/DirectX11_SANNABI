#include "pch.h"
#include "CBossPhase2PLDownState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>
#include <Scripts/CCameraScript.h>

CBossPhase2PLDownState::CBossPhase2PLDownState()
	: m_fDownTime(0.5f)
	, m_fAccTime(0.f)
{
}

CBossPhase2PLDownState::~CBossPhase2PLDownState()
{
}

void CBossPhase2PLDownState::finaltick()
{
	if (m_fAccTime > m_fDownTime)
	{
		ChangeState(L"BossPhase2PLAlertState");
	}

	m_fAccTime += DT;
}

void CBossPhase2PLDownState::Enter()
{
}

void CBossPhase2PLDownState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_PatternLast_ALERT);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_PatternLast_ALERT);
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
}


